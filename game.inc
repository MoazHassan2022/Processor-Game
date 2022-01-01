
FirstWrite proc near
 push ax
push bx
push cx
push dx
pushf
    mov FirstOneTalk,1400h
    mov dx,FirstOneTalk 
    mov yx,dx
    mov bh,0
    call setCursor

    recive_more_char:
            mov ah,0
            int 16h     
        
            cmp al,8h
            jz Command_back_space
            cmp al,0dh
            jz end_command1
            
            mov dx,FirstOneTalk
            cmp dl,11h                ;if he arrivel to the end of the line
            jz command_arrive_max
            
            ;;;; ptint the char in al
            mov ah,9
            mov bh,0
            mov cx,1
            mov bl,0Fh 
            int 10h
            ;;;;;;;;;;
            mov bx,FirstOneTalk
            mov bh,0
            mov si,bx
            add si,02h
            mov command[si],al                      
            ;;;;;; mov cursr to right
            mov ax,FirstOneTalk
            inc al                    ; mov cursur one right
            mov FirstOneTalk,ax
            mov yx,ax
            mov bh,0
            call setCursor
        

            jmp recive_more_char
            
            
            Command_back_space:
            call CommandbackSpace
            jmp recive_more_char 
            
            command_arrive_max:
            call arrive_max_length
            jmp recive_more_char
             
             
            end_command1:
            call CommandEnter
popf
 pop dx
pop cx
pop bx
pop ax
ret
FirstWrite endp


;/////////////////////
; BACK SPACE

CommandbackSpace proc near
     push ax
push bx
push cx
push dx
    pushf
    
        call CommandinnerMovLeft

        mov al,' '
        mov ah,9
        mov bh,0
        mov cx,1
        mov bl,0Fh 
        int 10h

        mov dx,FirstOneTalk
        mov yx,dx
        mov bh,0
        call setCursor

    popf
     pop dx
pop cx
pop bx
pop ax
    ret
CommandbackSpace endp

;///////////////////////////////////////
; MOVE LEFT
CommandinnerMovLeft proc near
     push ax
push bx
push cx
push dx
    pushf

        mov dx,FirstOneTalk 
        cmp dl,00h
        jz finsh_move_left2
        dec dl 
        mov FirstOneTalk,dx
        mov yx,dx   
        mov bh,0
        call setCursor
          
        finsh_move_left2:
        
    popf
     pop dx
pop cx
pop bx
pop ax
    ret
CommandinnerMovLeft endp

;//////////////////////////////////////////
; PRRESS ENTER

CommandEnter proc near
     push ax
push bx
push cx
push dx
    pushf
    
    mov bx,FirstOneTalk
    mov bh,0
    mov si,bx
    add si,2
    mov command[si],"$"
    
    popf
     pop dx
pop cx
pop bx
pop ax
    ret
CommandEnter endp

;//////////////////////////////////////
; ARRIVE MAX LENGTH  

arrive_max_length proc near
     push ax
push bx
push cx
push dx
    pushf

    lea dx ,arrive_max_message
    mov msg,dx
    mov bh,0

    popf
     pop dx
pop cx
pop bx
pop ax
    ret
arrive_max_length endp  


;/////////////////////////////////////////////////////
;////////////////////////////////////////////////////
;/////////////////////////////////////////////////// 
 
; CHECK ON THE COMMAND


checkCommand proc near
     push ax
push bx
push cx
push dx
    pushf
       call load_Command
   
       ; command search and prepare its code
       call search_instruction 
       cmp pos,-1
       jnz fixFiftyFour
        call invalid_command_with_miuns
        fixFiftyFour:
       mov ax, pos
       mov dl,04h
       Div dl
       MOV command_code , al 
   
       ; op1 search to detect type and prepare its value 
       LEA dx,operand1
       mov OP,dx
       CMP operand1[2],'['
       jz get_op1
       mov al , operand1[2]
       mov first_in_op , al
       call get_type_op
       cmp  detectType,0
       JZ   get_reg 
       jnz  get_num
       
       get_op1:
       call get_memory_num_op1
       mov op1_type,2
       mov ax,memory_num
       mov op1_value_code,ax
       jmp start_op2
       
       get_reg:
       call get_reg_code
       jmp start_op2
       
       get_num:
          call invalid_command_with_miuns
          
       jmp start_op2
       
       start_op2:
       
       
       ;op2_type db ?                  ; type of operand1
       ;op2_value_code dw ?            ; value of operand1

       ; op2 search to detect type and prepare its value 
       LEA dx,operand2
       mov OP,dx
       CMP operand2[2],'['
       jz get_op2
       mov al , operand2[2]
       mov first_in_op , al
       call get_type_op
       cmp  detectType,0
       JZ   get_reg2 
       jnz  get_num2
       
       get_op2:
       call get_memory_num_op2
       mov op2_type,2
       mov ax,memory_num
       mov op2_value_code,ax
       jmp Doneload
       
       get_reg2:
       call get_reg_code2
       jmp Doneload
       
       get_num2:
          ConvertStrHexa operand2, op2_value_code
          mov op2_type,3 
       jmp Doneload
       
    
    
      Doneload:
      
      
      mov ax,0
      or ah, op1_type
      mov cl,2
      shl ah,cl
      or ah, op2_type
      mov cl,4
      shl ah,cl
      or ah, command_code
      mov instruction,ah 
      
      mov ax,op1_value_code
      mov op1, ax
      
      mov ax,op2_value_code
      mov op2, ax
          
       
    popf
     pop dx
pop cx
pop bx
pop ax   
    ret 
checkCommand endp 


;//////////////////////////////////////////////////////////////////////////////////
; LOAD THE COMMAND

load_Command proc near
     push ax
push bx
push cx
push dx
    pushf
    labelGame:
    mov bx, 0
    cmp user, 1
    jnz secondForbidden
    mov cl, forbiddenChar1
    jmp findForb
    secondForbidden:
    mov cl, forbiddenChar2
    findForb:
    cmp command[bx], cl
    jnz dont_call_invalid_command_without_miuns
    call invalid_command_without_miuns 
    dont_call_invalid_command_without_miuns:
    inc bx
    cmp command[bx], '$'
    jnz findForb

    mov si,1h                      ; si will be the pointer to index in command
    
    exclude_space_for_command:
    inc si 
    
    cmp command[si] , '$'           ; if the first non space i face is $ that mean user enter just spaces
    jnz fixFiftyThree 
    labelStop:
    call invalid_command_with_miuns
    fixFiftyThree:
    
    cmp command[si] , ' '             ; if the char is not space then i will return the first non space postion
    jnz Load_instruction
    
    cmp si,11h                          ; compare if we arrive to the end of command
    jle exclude_space_for_command
    
    Load_instruction:    
    mov CX,3h
    mov di,2
    l_inst:
    mov dl,command[si]
    mov  instructionSTR[di],dl
    inc si
    inc di    
    loop l_inst
    
    mov  instructionSTR[di],'$'

    cmp command[si] , ' '         ; after the instruction it should be 1 space at least  
    jz fixFiftyTwo
    call invalid_command_with_miuns
    fixFiftyTwo:

  
    exclude_space_for_operand1:

    cmp command[si] , '$'         ; if the first non space i face is $ that mean user enter just spaces
    jnz fixFiftyOne 
    call invalid_command_with_miuns
    fixFiftyOne:
    
    cmp command[si] , ' '         ; if the char is not space then i will return the first non space postion
    jnz Load_op1
    
    inc si
    
    cmp si,11h                    ; compare if we arrive to the end of command
    jle exclude_space_for_operand1
    
    
    ;///////////////////////////////
    Load_op1:
    mov di,2
            
    l_op1:
        
    cmp command[si] , '$'         ; if the first non space i face is $ that mean user enter just spaces
    jnz fixFifty 
    call invalid_command_with_miuns
    fixFifty:
     
    cmp command[si] , ','         ; if the char is not space then i will return the first non space postion
    jz do_op2
    
    mov dl,command[si] 
    
    mov operand1[di],dl
    
    inc si
    
    inc di 
    
    
    cmp si,13h                    ; compare if we arrive to the end of command
    jle l_op1
    
    ;////////////////////////////////////
    
    do_op2:
    mov operand1[di],'$'
    
    exclude_space_for_operand2_befor:
    cmp command[si] , '$'         ; if the first non space i face is $ that mean user enter just spaces
    jnz fixFourtyNine 
    call invalid_command_with_miuns
    fixFourtyNine:
    
    cmp command[si] , ' '         ; if the char is not space then i will return the first non space postion
    jnz Load_op2
    
    inc si
    
    cmp si,13h                    ; compare if we arrive to the end of command
    jle exclude_space_for_operand2_befor
    
    Load_op2:
    
    cmp command[si],','
    jz fixFourtyEight 
    call invalid_command_with_miuns
    fixFourtyEight:
    inc si
    
    mov di,2
    
    exclude_space_for_operand2_after:
    cmp command[si] , '$'         ; if the first non space i face is $ that mean user enter just spaces
    jnz fixFourtySvn 
    call invalid_command_with_miuns
    fixFourtySvn:
    
    cmp command[si] , ' '         ; if the char is not space then i will return the first non space postion
    jnz l_op2
    
    inc si
    
    cmp si,11h                    ; compare if we arrive to the end of command
    jle exclude_space_for_operand2_after                         
    
            
    l_op2:
        
    cmp command[si] , '$'         ; if the first non space i face is $ that mean user enter just spaces
    jz finished
       
    mov dl,command[si] 
    
    mov operand2[di],dl
    
    inc si
    
    inc di 
    
    cmp si,13h                    ; compare if we arrive to the end of command
    jle l_op2
    
    finished:
    
    mov operand2[di],'$'
    
    popf
     pop dx
pop cx
pop bx
pop ax    
ret
load_Command endp

;//////////////////////////////////////////////////////////////////////////////////////////////////
;SEARCH FOR INSTRUCTION 

search_instruction proc near
     push ax
push bx
push cx
push dx
    pushf
    
    MOV POS,-1
    MOV CL,44h
    MOV CH,0
    lea si, Instructions_array
    lea di,  instructionSTR
    dec si

    FIRST:
    INC POS
    INC SI
    MOV AL,[SI]
    mov bl, [di+2]
    CMP AL,bl
    JE Second
    LOOP FIRST

    jmp NOTEQUAL

    Second:
    INC SI
    MOV AL,[SI]
    CMP AL,[di+3]
    JNE DecthenFirst

    Third:
    INC SI
    MOV AL,[SI]
    CMP AL,[di + 4]
    JNE DoubleDecthenFirst
    JE  EQUAL

    NOTEQUAL:
    MOV POS,-1
    JMP finish_search

    DecthenFirst:
    Dec si
    jmp FIRST

    DoubleDecthenFirst:
    Dec si
    Dec si
    jmp FIRST

    EQUAL:
    finish_search:  

    popf
     pop dx
pop cx
pop bx
pop ax
ret
search_instruction endp

;///////////////////////////////////////////////////////////////////////////
; INVALID COMMAND WITH MINUS

invalid_command_with_miuns proc near
     push ax
push bx
push cx
push dx
    pushf
    call Write_In_Game_Notif
    cmp user, 1
    jne secondMinus
    dec firstScore
    jmp end_invalid_command_with_miuns
    secondMinus:
    dec secondScore
    end_invalid_command_with_miuns:
    popf
     pop dx
pop cx
pop bx
pop ax
    ret
invalid_command_with_miuns endp  
 
 ;///////////////////////////////////////////////////////////////////////////
; INVALID COMMAND WITHOUT MINUS

invalid_command_without_miuns proc near
     push ax
push bx
push cx
push dx
    pushf
    mov yx, 1206h
    mov bh, 0
    call setCursor
    mov msg, offset ForbiddenCharMsg
    call printMsg
    popf
     pop dx
pop cx
pop bx
pop ax
    ret
invalid_command_without_miuns endp  
 

;///////////////////////////////////////////////////////////////////////////////////////
; get the memory number


get_memory_num_op1 proc near
 push ax
push bx
push cx
push dx 
pushf

    mov si,3
    mov di,2   
    call exclude_space_op1             ; start working after delete spaces between [ and first char     
    first_half:   
        cmp operand1[si] , ' '         ; if the char is space so it can be end of operand or end of memory type or error if he contin more char (1)
        jz second_half_start
    
        cmp operand1[si] , ']'         ;thats mean he just write one half and this its end with out spaces
        jz finish
         
        mov dl,operand1[si]
        mov first_half_str[di],dl
    
        inc si   
        inc di 
    cmp si,13h                    ; just trival if the operand is 17 char and its imposible 
    jle first_half


    second_half_start:
        call exclude_space_op1         ; here we do the check of (1)
        cmp operand1[si] , ']'         ; if the end of first half
        jz finish
        cmp operand1[si] , '+'         ; if after this spaces there is a + sign we will continue to load second half
        jz fixFourtySix
        jmp invalid_add                     ; if it wasnt ] or +  that mean he write somthing like mov [ a  x + 5 ] and its error
        fixFourtySix:

        inc si                         ; return di to 2 to load the second half
        mov di,2                       ; increment the si to start with second half
   
    call exclude_space_op1             ; delete the spaces after + to arrive second half

    second_half:   
        cmp operand1[si] , ']'         ; we load all second half and arrive to ] end of operand
        jz finish           
    
        cmp operand1[si] , ' '         ; if the char is space so it can be end of operand or end of memory type or error if he contin (1) 
        jz befor_finish
         
        mov dl,operand1[si]
        mov second_half_str[di],dl      ; just load the char to the second half
       
        inc si    
        inc di 
        cmp si,13h                    ; compare if we arrive to the end of command
        jle second_half


        befor_finish:               
            call exclude_space_op1
            cmp operand1[si] , ']'         ; after delte the spaces we check if the next char is ] else its error
            jz fixFourtyFive
            jmp invalid_add
            fixFourtyFive:
         
        finish:                  ;; bx and si and di  is just allowed
       cmp first_half_str[2],'$'
       jnz fixFourtyFour
       jmp invalid_add
       fixFourtyFour:
       
       
       ; op1 search to detect type and prepare its value 
       mov dl,first_half_str[2]
       mov first_in_op ,dl 
       call get_type_op
       cmp  detectType,0
       JZ   its_reg1 
       jnz  its_num1
       
       its_reg1:
       cmp first_half_str[2] , 'B' 
       jz  add_B 
       cmp first_half_str[2] , 'D' 
       jz  add_D
       cmp first_half_str[2] , 'S' 
       jz  add_I
       jz fixFourtyThree
       jmp invalid_add
       fixFourtyThree:
              
       
       add_B:
       mov al,RegistersArray[2]
       mov ah,RegistersArray[3]
       add memory_num,ax 
       jmp second_h
       
       add_D:
       mov al,RegistersArray[6]
       mov ah,RegistersArray[7]
       add memory_num,ax 
       jmp second_h
       
       
       add_I:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       add memory_num,ax 
       jmp second_h
       
       
       its_num1:
       ConvertStrHexa first_half_str, temp_number
       mov ax,temp_number
       add memory_num,ax
       jmp second_h
       
           
       second_h:
       ; get its value and add it to memory num
       cmp second_half_str[2],'$'
       jnz fixFourtyTwo
       jmp end_op1
       fixFourtyTwo:
       
       mov dl, second_half_str[2]
       mov first_in_op , dl
       call get_type_op
       cmp  detectType,0
       JZ   its_reg2 
       jnz  its_num2
       
       its_reg2:
       cmp second_half_str[2] , 'B' 
       jz  add_B2 
       cmp second_half_str[2] , 'D' 
       jz  add_D2
       cmp second_half_str[2] , 'S' 
       jz  add_I2
       jz fixFourtyOne
       jmp invalid_add
       fixFourtyOne:
       
       add_B2:
       mov al,RegistersArray[2]
       mov ah,RegistersArray[3]
       jmp end_op1
       
       add_D2:
       mov al,RegistersArray[6]
       mov ah,RegistersArray[7]
       add memory_num,ax 
       jmp end_op1
       
       
       add_I2:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       add memory_num,ax 
       jmp end_op1
       
       
       its_num2:
       ConvertStrHexa second_half_str, temp_number
       mov ax,temp_number
       add memory_num,ax
       jmp end_op1
       
       
       jmp end_op1 
   
       ; get its value and add it to memory num
   

       invalid_add:
          call invalid_address
       end_op1:
       popf
        pop dx
pop cx
pop bx
pop ax
       ret        
get_memory_num_op1 endp


;//////////////////////////////////////////////////////////////////////////////////////////////////////
;//////////////////////////////////////////////////////////////////////////////////////////////////////

get_memory_num_op2 proc near
 push ax
push bx
push cx
push dx 
pushf

    mov si,3
    mov di,2   
    call exclude_space_opq             ; start working after delete spaces between [ and first char     
    first_halfq:   
        cmp operand2[si] , ' '         ; if the char is space so it can be end of operand or end of memory type or error if he contin more char (1)
        jz second_half_startq
    
        cmp operand2[si] , ']'         ;thats mean he just write one half and this its end with out spaces
        jz finishq
         
        mov dl,operand2[si]
        mov first_half_str[di],dl
    
        inc si   
        inc di 
    cmp si,13h                    ; just trival if the operand is 17 char and its imposible 
    jle first_halfq


    second_half_startq:
        call exclude_space_opq         ; here we do the check of (1)
        cmp operand2[si] , ']'         ; if the end of first half
        jz finishq
        cmp operand2[si] , '+'         ; if after this spaces there is a + sign we will continue to load second half
        jz fixFourty
        jmp invalid_addq                     ; if it wasnt ] or +  that mean he write somthing like mov [ a  x + 5 ] and its error
        fixFourty:

        inc si                         ; return di to 2 to load the second half
        mov di,2                       ; increment the si to start with second half
   
    call exclude_space_opq             ; delete the spaces after + to arrive second half

    second_halfq:   
        cmp operand2[si] , ']'         ; we load all second half and arrive to ] end of operand
        jz finishq           
    
        cmp operand2[si] , ' '         ; if the char is space so it can be end of operand or end of memory type or error if he contin (1) 
        jz befor_finishq
         
        mov dl,operand2[si]
        mov second_half_str[di],dl      ; just load the char to the second half
       
        inc si    
        inc di 
        cmp si,13h                    ; compare if we arrive to the end of command
        jle second_halfq


        befor_finishq:               
            call exclude_space_opq
            cmp operand2[si] , ']'         ; after delte the spaces we check if the next char is ] else its error
            jz fixThirtyNine
            jmp invalid_addq
            fixThirtyNine:
         
        finishq:                  ;; bx and si and di  is just allowed
       cmp first_half_str[2],'$'
       jnz fixThirtyEight
       jmp invalid_addq
       fixThirtyEight:
       
       
       ; op1 search to detect type and prepare its value 
       mov dl,first_half_str[2]
       mov first_in_op ,dl 
       call get_type_op
       cmp  detectType,0
       JZ   its_regq 
       jnz  its_numq
       
       its_regq:
       cmp first_half_str[2] , 'B' 
       jz  add_Bq 
       cmp first_half_str[2] , 'D' 
       jz  add_Dq
       cmp first_half_str[2] , 'S' 
       jz  add_Iq
       jz fixThirtySvn
       jmp invalid_addq
       fixThirtySvn:
              
       
       add_Bq:
       mov al,RegistersArray[2]
       mov ah,RegistersArray[3]
       add memory_num,ax 
       jmp second_hq
       
       add_Dq:
       mov al,RegistersArray[6]
       mov ah,RegistersArray[7]
       add memory_num,ax 
       jmp second_hq
       
       
       add_Iq:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       add memory_num,ax 
       jmp second_hq
       
       
       its_numq:
       Num_Input first_half_str, temp_number
       mov ax,temp_number
       add memory_num,ax
       jmp second_hq
       
           
       second_hq:
       ; get its value and add it to memory num
       cmp second_half_str[2],'$'
       jnz fixThirtySix
       jmp end_op1q
       fixThirtySix:
       
       mov dl, second_half_str[2]
       mov first_in_op , dl
       call get_type_op
       cmp  detectType,0
       JZ   its_reg2q 
       jnz  its_num2q
       
       its_reg2q:
       cmp second_half_str[2] , 'B' 
       jz  add_B2q 
       cmp second_half_str[2] , 'D' 
       jz  add_D2q
       cmp second_half_str[2] , 'S' 
       jz  add_I2q
       jz fixThirtFive
       jmp invalid_addq
       fixThirtFive:
       
       add_B2q:
       mov al,RegistersArray[2]
       mov ah,RegistersArray[3]
       jmp end_op1q
       
       add_D2q:
       mov al,RegistersArray[6]
       mov ah,RegistersArray[7]
       add memory_num,ax 
       jmp end_op1q
       
       
       add_I2q:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       add memory_num,ax 
       jmp end_op1q
       
       
       its_num2q:
       Num_Input second_half_str, temp_number
       mov ax,temp_number
       add memory_num,ax
       jmp end_op1q
       
       
       jmp end_op1q 
   
       ; get its value and add it to memory num
   

       invalid_addq:
          call invalid_address
       end_op1q:
       popf
        pop dx
pop cx
pop bx
pop ax
       ret        
get_memory_num_op2 endp




  
;///////////////////////////////////////////////////
; invalids
  
invalid_address proc near
    push ax
push bx
push cx
push dx
   pushf 
        mov memory_num , -1 
        call invalid_command_with_miuns
   popf
    pop dx
pop cx
pop bx
pop ax
   ret 
invalid_address endp

;////////////////////////////////////////////////////////////
; exclude spaces

exclude_space_op1 proc near
    exclude_space1:
        cmp operand1[si],' '             ; if the char is not space then i will return the first non space postion
        jnz end_ex
        inc si
        cmp si,7h                          ; compare if we arrive to the end of command
    jle exclude_space1
    end_ex:
ret
exclude_space_op1 endp

;///////////////////////////////
;//////////////////

exclude_space_opq proc near
    exclude_space2:
        cmp operand2[si],' '             ; if the char is not space then i will return the first non space postion
        jnz end_ex2
        inc si
        cmp si,7h                          ; compare if we arrive to the end of command
    jle exclude_space2
    end_ex2:
ret
exclude_space_opq endp

;/////////////////////////////////////////////
; get the number code

get_num_code proc near
     push ax
push bx
push cx
push dx
    pushf
        ;;; some code    
    popf
     pop dx
pop cx
pop bx
pop ax
ret    
get_num_code endp     

;///////////////////////////
; get code reg

get_reg_code proc near
 push ax
push bx
push cx
push dx
pushf
  
   call search_general_reg
   cmp pos,-1
   jz Not_general
   
   mov op1_type , 0   
   mov ax, pos
   mov dl,03h
   Div dl
   mov ah,00
   MOV op1_value_code ,ax
   
   jmp finish_reg
   
   Not_general:
   call search_other_reg
   cmp pos,-1
   jz invalid_reg 
   mov op1_type , 1
   mov ax, pos
   mov dl,03h
   Div dl
   mov ah,00
   MOV op1_value_code ,ax
   
   invalid_reg:
     call invalid_command_with_miuns
   finish_reg:    
popf     
 pop dx
pop cx
pop bx
pop ax
ret    
get_reg_code endp


;//////////////////////////////////

get_reg_code2 proc near
 push ax
push bx
push cx
push dx
pushf
  
   call search_general_reg
   cmp pos,-1
   jz Not_general2
   
   mov op2_type , 0   
   mov ax, pos
   mov dl,03h
   Div dl
   mov ah,00
   MOV op2_value_code ,ax
   
   jmp finish_reg2
   
   Not_general2:
   call search_other_reg
   cmp pos,-1
   jz invalid_reg2 
   mov op2_type , 1
   mov ax, pos
   mov dl,03h
   Div dl
   mov ah,00
   MOV op2_value_code ,ax
   
   invalid_reg2:
     call invalid_command_with_miuns
   finish_reg2:    
popf     
 pop dx
pop cx
pop bx
pop ax
ret    
get_reg_code2 endp

;///////////////////////////////////////
; get type of operand

get_type_op proc near
     push ax
push bx
push cx
push dx
    pushf
    
    cmp first_in_op,30h  ; compare bl with ascii value of 01
    jge mayNum          ; if greater or equal jump to label may number

    mayNum:       ; label print
    cmp first_in_op, 39h  ; compare bl with ascii value of 09
    jle its_num    ; if less or equal jump to label its number
    jg itschar       ; if greater or equal jump to label print
    its_num:
    mov detectType, 1   
    itschar:  
    popf
     pop dx
pop cx
pop bx
pop ax
    ret
get_type_op endp  

;/////////////////////////////////////////////////////////////
; search in general registers

search_general_reg proc near
     push ax
push bx
push cx
push dx
    pushf

    MOV POS,-1
    MOV CL,21h
    MOV CH,0
    lea si, general_reg_array
    mov di, OP
    dec si

    general_reg_FIRST:
    INC POS
    INC SI
    MOV AL,[SI]
    CMP AL, [di + 2]
    JE general_reg_Second
    LOOP general_reg_FIRST

    jmp general_reg_NOTEQUAL

    general_reg_Second:
    INC SI
    MOV AL,[SI]
    CMP AL,[di+3]
    JNE general_reg_DecthenFirst
    JE  general_reg_EQUAL

    general_reg_NOTEQUAL:
    MOV POS,-1
    JMP general_reg_finish_search

    general_reg_DecthenFirst:
    Dec si
    jmp general_reg_FIRST

    general_reg_DoubleDecthenFirst:
    Dec si
    Dec si
    jmp general_reg_FIRST

    general_reg_EQUAL:
    general_reg_finish_search:

    popf
     pop dx
pop cx
pop bx
pop ax

    ret
search_general_reg endp

;////////////////////////////////////////////////////////////////
 ; sreach of other reg
search_other_reg proc near
     push ax
push bx
push cx
push dx
    pushf

        MOV POS,-1
        MOV CL,9h
        MOV CH,0
        lea si, other_reg_array
        mov di, OP
        dec si
    
        other_reg_FIRST:
        INC POS
        INC SI
        MOV AL,[SI]
        CMP AL, [di + 2]
        JE other_reg_Second
        LOOP other_reg_FIRST
    
        jmp other_reg_NOTEQUAL
    
        other_reg_Second:
        INC SI
        MOV AL,[SI]
        CMP AL, [di + 3]
        
        JNE other_reg_DecthenFirst
        JE  other_reg_EQUAL
    
        other_reg_NOTEQUAL:
        MOV POS,-1
        JMP other_reg_finish_search
    
        other_reg_DecthenFirst:
        Dec si
        jmp other_reg_FIRST
    
        other_reg_DoubleDecthenFirst:
        Dec si
        Dec si
        jmp other_reg_FIRST
    
        other_reg_EQUAL:
        other_reg_finish_search: 
    
    popf
     pop dx
pop cx
pop bx
pop ax
    ret
search_other_reg endp

Write_In_Game_Notif proc near
push ax
push BX
push CX
push DX
pushf
mov yx, 1206h
mov bh, 0
call setCursor
mov msg, offset WrongCommandMsg
call printMsg
popf
pop dx
pop cx
pop bx
pop ax
ret
Write_In_Game_Notif endp


receiveInstruction proc near

    mov yx, 1400h
    mov bh, 0
    call setCursor
    mov ah,0
	int 16h             ; get the power up option in al
	
	cmp user,1
	jnz second_power_up

    mov powerUp1,al      ; first user turn
    jmp pre_power
     
    second_power_up:      ; second user turn
    mov powerUp2,al
    
    pre_power: 

	cmp al,'0'
	jz rec_com
    jnz rec_pow 
     
    rec_com: 
      call recive_command
    jmp endReceive
        
    rec_pow:
          call recive_power_up
    jmp endReceive  
    
    endReceive:
ret
receiveInstruction endp


recive_power_up proc near 
; write in not area the comment
        
    cmp al,'3'
    jz reciveforbidden_char

    call recive_command
    
    jmp end_recive_power_up
    
    reciveforbidden_char:
    mov ah,0
    int 16h
    
    cmp user,1
	jnz new_forbidden1

    mov forbiddenChar2,al      ; first user turn
    jmp end_recive_power_up
     
    new_forbidden1:      ; second user turn
    mov forbiddenChar1,al
     
    end_recive_power_up:
    ret    
recive_power_up endp



recive_command proc near
    call FirstWrite   
    call checkCommand   
   
   ret
recive_command endp

toogle_user proc near  
  xor user, 00000011b         
ret
toogle_user endp
