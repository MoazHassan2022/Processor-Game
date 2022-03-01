
FirstWrite proc near
 push ax
push bx
push cx
push dx
pushf
    mov msg, offset enterCommand
    call Write_In_Game_Notif
    call deleteCommand
    cmp whichUser, 1
    jnz secondCursor
    mov FirstOneTalk,1400h
    jmp firstCursor
    secondCursor:
    mov FirstOneTalk, 1414h
    firstCursor:
    mov dx,FirstOneTalk 
    mov yx,dx
    mov bh,0
    call setCursor
    

    recive_more_char:
        call getKeyMainScreen 
        cmp al, 0
        jz recive_more_char

            cmp ah, 3eh     
            jz fix_cont_recive_more_char_dont
            jmp cont_recive_more_char_dont
            fix_cont_recive_more_char_dont:
            mov bl, 7
            call sendOneByte
            mov al, 1
            EndGame firstUsername, firstScore  ; abborted suddenly
            cont_recive_more_char_dont:


            cmp ah, 0FH
            jnz notinline
            call inlinechat
            push FirstOneTalk
            pop yx 
            mov bh,0
            call setCursor
            jmp recive_more_char
            notinline:
            cmp al,8h
            jz Command_back_space
            cmp al,0dh
            jz end_command1
            
            mov dx,FirstOneTalk
            cmp whichUser, 1
            jnz toggleArriveMax
            cmp dl,11h
            jmp dontToggleArrive
            toggleArriveMax:
            cmp dl,25h                ;if he arrivel to the end of the line
            dontToggleArrive:
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
            cmp whichUser, 2
            jnz dontSub1
            sub bl, 14h
            dontSub1:
            mov si,bx
            add si, 2
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
        cmp whichUser, 1
    jnz toggleSecondInnerLeft
    cmp dl,00h
    jmp toggleInnerLeft
    toggleSecondInnerLeft:
    cmp dl,14h
    toggleInnerLeft: 
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
    mov dx,FirstOneTalk
    cmp whichUser, 2
    jnz dontSub
    sub bl, 14h
    dontSub:
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
    call Write_In_Game_Notif

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
       labelHoba45:
       cmp isCommandValid, 0
       jne fixEndCheckCommand
       jmp endCheckCommand
       fixEndCheckCommand:
       cmp instructionSTR[2], 'N'
       jne fixEndCheckCommand10
       mov instruction, 0
       jmp endCheckCommand
       fixEndCheckCommand10:
       

       ; command search and prepare its code
       call search_instruction 
       cmp pos,-1
       jnz fixFiftyFour
        jmp InvalidCheckCommand
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
       mov al , operand1[3]
       mov first_in_op , al
       call get_type_op
       cmp  detectType,0
       JZ   get_reg 
       jmp  InvalidCheckCommand
       
       get_op1:
       call get_memory_num_op1
       cmp isCommandValid, 0
       jne fixEndCheckCommand1
       jmp endCheckCommand
       fixEndCheckCommand1:
       cmp memory_num, 0fh
       jbe fixInvalidCheckCommand
       jmp InvalidCheckCommand
       fixInvalidCheckCommand:
       mov op1_type,2
       mov ax,memory_num
       mov op1_value_code,ax
       jmp start_op2
       
       get_reg:
       call get_reg_code
       cmp isCommandValid, 0
       jne fixEndCheckCommand2
       jmp endCheckCommand
       fixEndCheckCommand2:
       jmp start_op2
       
       start_op2:
       
       
       ;op2_type db ?                  ; type of operand1
       ;op2_value_code dw ?            ; value of operand1

       ; op2 search to detect type and prepare its value 
       LEA dx,operand2
       mov OP,dx
       CMP operand2[2],'['
       jz get_op2
       mov al , operand2[3]
       mov first_in_op , al
       call get_type_op
       cmp  detectType,0
       JZ   get_reg2 
       jnz  get_num2
       
       get_op2:
       call get_memory_num_op2
       cmp isCommandValid, 0
       jne fixEndCheckCommand3
       jmp endCheckCommand
       fixEndCheckCommand3:
       cmp memory_num, 0fh
       jbe fixInvalidCheckCommand1
       jmp InvalidCheckCommand
       fixInvalidCheckCommand1:
       mov op2_type,2
       mov ax,memory_num
       mov op2_value_code,ax
       jmp Doneload
       
       get_reg2:
       call get_reg_code2
       cmp isCommandValid, 0
       jne fixEndCheckCommand4
       jmp endCheckCommand
       fixEndCheckCommand4:
       jmp Doneload
       
       get_num2:
          ConvertStrHexa operand2, op2_value_code
          mov op2_type,3 
       jmp Doneload
       

    
      Doneload:
      cmp isCommandValid, 0
      je endCheckCommand
      mov isCommandValid, 1 ; command is valid
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
      jmp endCheckCommand

     InvalidCheckCommand:  
     call invalid_command_with_miuns
     endCheckCommand:  
       
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
    labelMoza:
    mov bx, 2
    cmp whichUser, 1
    jnz secondForbidden
    mov cl, forbiddenChar1
    jmp findForb
    secondForbidden:
    mov cl, forbiddenChar2
    findForb:
    cmp command[bx], cl
    jnz dont_call_invalid_command_without_miuns
    jmp InvalidWithoutMinusload_Command 
    dont_call_invalid_command_without_miuns:
    inc bx
    cmp command[bx], '$'
    jnz findForb

    mov si,1h                      ; si will be the pointer to index in command
    
    exclude_space_for_command:
    inc si 
    
    cmp command[si] , '$'           ; if the first non space i face is $ that mean user enter just spaces
    jnz fixFiftyThree 
    jmp Invalidload_Command
    fixFiftyThree:
    
    cmp command[si] , ' '             ; if the char is not space then i will return the first non space postion
    jnz Load_instruction
    
    cmp si,11h                          ; compare if we arrive to the end of command
    jle exclude_space_for_command
    
    Load_instruction:    
    cmp command[si],"O"
    jnz isnt_or
    mov Cx,2h
    mov instructionSTR[si + 2], ' '
    jmp start_loading
    isnt_or:    
    mov CX,3h
    start_loading:
    mov di,2
    l_inst:
    mov dl,command[si]
    mov  instructionSTR[di],dl
    inc si
    inc di    
    loop l_inst
    
    cmp instructionSTR[2], 'N'
    je itsNOP
    jmp continueInstructionSTR
    itsNOP:
    call validateNOP
    cmp isCommandValid, 0
    jmp endload_Command
    continueInstructionSTR:

    cmp instructionSTR[2], 'O'
    jz contOrNoDollar
    mov instructionSTR[di],'$'
    contOrNoDollar:
    cmp command[si] , ' '         ; after the instruction it should be 1 space at least  
    jz fixFiftyTwo
    jmp Invalidload_Command
    fixFiftyTwo:

  
    exclude_space_for_operand1:

    cmp command[si] , '$'         ; if the first non space i face is $ that means user enter just spaces
    jnz fixFiftyOne 
    jmp Invalidload_Command
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
    jmp Invalidload_Command
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
    jmp Invalidload_Command
    fixFourtyNine:
    
    cmp command[si] , ' '         ; if the char is not space then i will return the first non space postion
    jnz Load_op2
    
    inc si
    
    cmp si,13h                    ; compare if we arrive to the end of command
    jle exclude_space_for_operand2_befor
    
    Load_op2:
    
    cmp command[si],','
    jz fixFourtyEight 
    jmp Invalidload_Command
    fixFourtyEight:
    inc si
    
    mov di,2
    
    exclude_space_for_operand2_after:
    cmp command[si] , '$'         ; if the first non space i face is $ that mean user enter just spaces
    jnz fixFourtySvn 
    jmp Invalidload_Command
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
    jmp endload_Command

    Invalidload_Command:
    call invalid_command_with_miuns
    jmp endload_Command

    InvalidWithoutMinusload_Command:
    call invalid_command_without_miuns

    endload_Command:
    
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
    mov msg, offset WrongCommandMsg
    call Write_In_Game_Notif
    cmp whichUser, 1
    jne secondMinus
    dec firstScore
    call showScore
    jmp end_invalid_command_with_miuns
    secondMinus:
    dec secondScore
    call showScore
    end_invalid_command_with_miuns:
    mov isCommandValid, 0
    call sendError
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
    mov msg, offset ForbiddenCharMsg
    call Write_In_Game_Notif
    mov isCommandValid, 0 
    popf
     pop dx
pop cx
pop bx
pop ax
    ret
invalid_command_without_miuns endp  
 
sendError proc near
        checkSendError:
        mov dx,3fDh
      	In al , dx 			
  	    AND al , 00100000b
        jz checkSendError
        mov al, 6    ; Error code!
        mov dx, 3f8h
        out dx,al
ret 
sendError endp
;///////////////////////////////////////////////////////////////////////////////////////
; get the memory number


get_memory_num_op1 proc near
 push ax
push bx
push cx
push dx 
pushf
    mov memory_num, 0
    mov si,3
    mov di,2   
    call exclude_space_op1             ; start working after delete spaces between [ and first char     
    first_half:   
        cmp operand1[si] , ' '         ; if the char is space so it can be end of operand or end of memory type or error if he contin more char (1)
        jz second_half_start

        cmp operand1[si] , '+'         ; if the char is + so it can be end of operand or end of memory type or error if he contin more char (1)
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
       mov dl,first_half_str[3]
       mov first_in_op ,dl 
       call get_type_op
       cmp  detectType,0
       JZ   its_reg1 
       jz  fixIts_num1
       jmp its_num1
       fixIts_num1:
       
       its_reg1:
       lea dx,first_half_str
       mov OP, dx
       call get_reg_code
       cmp isCommandValid, 0
       jne fixreg1
       jmp invalid_add
       fixreg1:
       cmp op1_type , 0
       Jz maybeB
       cmp op1_type,1
       jz maybeD_S
       jmp invalid_add


       maybeB:
       ;///////////   its may be  BX
       cmp op1_value_code,9   ;/////////// if its b
       jz add_B               ; add it
       jmp invalid_add             ; else its invalid

       maybeD_S:
       ;//////////////        its may be SI or DI
       cmp op1_value_code,1    ; SI value is 0 or DI is 1
       jle itsvalid 
       jmp invalid_add 
       itsvalid:             ; if op1_value_code is above 1 then its invalid
       cmp op1_value_code,0    ; add value of SI
       jz add_I
       cmp op1_value_code,1    ; add value of DI
       jz add_D
       jmp invalid_add
              
       
       add_B:
       cmp whichUser, 2
       jz takeSecondAdd_B
       mov al,RegistersArray2[2]
       mov ah,RegistersArray2[3]
       jmp contAdd_B
       takeSecondAdd_B:
       mov al,RegistersArray[2]
       mov ah,RegistersArray[3]
       contAdd_B:
       add memory_num,ax 
       jmp second_h
       
       add_D:
       cmp whichUser, 2
       jz takeSecondAdd_D
       mov al,RegistersArray2[10]
       mov ah,RegistersArray2[11]
       jmp contAdd_D
       takeSecondAdd_D:
       mov al,RegistersArray[10]
       mov ah,RegistersArray[11]
       contAdd_D:
       add memory_num,ax 
       jmp second_h
       
       
       add_I:
       cmp whichUser, 2
       jz takeSecondAdd_I
       mov al,RegistersArray2[8]
       mov ah,RegistersArray2[9]
       jmp contAdd_I
       takeSecondAdd_I:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       contAdd_I:
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
       
       mov dl, second_half_str[3]
       mov first_in_op , dl
       call get_type_op
       cmp  detectType,0
       JZ   its_reg2 
       jz  fixIts_num2
       jmp its_num2
       fixIts_num2:
       
       its_reg2:
       lea dx,second_half_str
       mov OP, dx
       call get_reg_code
       cmp isCommandValid, 0
       jne fixreg2
       jmp invalid_add
       fixreg2:
       cmp op1_type , 0
       Jz maybeB2
       cmp op1_type,1
       jz maybeD_S2
       jmp invalid_add

       maybeB2:
       ;///////////   its may be  BX
       cmp op1_value_code,9   ;/////////// if its b
       jz add_B2               ; add it
       jmp invalid_add             ; else its invalid

       maybeD_S2:
       ;//////////////        its may be SI or DI
       cmp op1_value_code,1    ; SI value is 0 or DI is 1
       jle itsreg2valid 
       jmp invalid_add     
       itsreg2valid:         ; if op1_value_code is above 1 then its invalid
       cmp op1_value_code,0    ; add value of SI
       jz add_I2
       cmp op1_value_code,1    ; add value of DI
       jz add_D2
       jmp invalid_add
       
       add_B2:
       cmp whichUser, 2
       jz takeSecondAdd_B2
       mov al,RegistersArray2[2]
       mov ah,RegistersArray2[3]
       jmp contAdd_B2
       takeSecondAdd_B2:
       mov al,RegistersArray[2]
       mov ah,RegistersArray[3]
       contAdd_B2:
       add memory_num,ax 
       jmp end_op1
       
       add_D2:
       cmp whichUser, 2
       jz takeSecondAdd_D2
       mov al,RegistersArray2[6]
       mov ah,RegistersArray2[7]
       jmp contAdd_D2
       takeSecondAdd_D2:
       mov al,RegistersArray[6]
       mov ah,RegistersArray[7]
       contAdd_D2:
       add memory_num,ax  
       jmp end_op1
       
       
       add_I2:
       cmp whichUser, 2
       jz takeSecondAdd_I2
       mov al,RegistersArray2[8]
       mov ah,RegistersArray2[9]
       jmp contAdd_I2
       takeSecondAdd_I2:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       contAdd_I2:
       add memory_num,ax 
       jmp end_op1
       
       
       its_num2:
       ConvertStrHexa second_half_str, temp_number
       mov ax,temp_number
       add memory_num,ax
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
    mov memory_num, 0
    mov si,3
    mov di,2   
    call exclude_space_opq             ; start working after delete spaces between [ and first char     
    first_halfq:   
        cmp operand2[si] , ' '         ; if the char is space so it can be end of operand or end of memory type or error if he contin more char (1)
        jz second_half_startq

        cmp operand2[si] , '+'         ; if the char is + so it can be end of operand or end of memory type or error if he contin more char (1)
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
       mov dl,first_half_str[3]
       mov first_in_op ,dl 
       call get_type_op
       cmp  detectType,0
       JZ   its_regq 
       jz  fixIts_numq
       jmp its_numq
       fixIts_numq:
       
       its_regq:
       lea dx,first_half_str
       mov OP, dx
       call get_reg_code
       cmp isCommandValid, 0
       jne fixregq
       jmp invalid_addq
       fixregq:
       cmp op1_type , 0
       Jz maybeBq
       cmp op1_type,1
       jz maybeD_Sq
       jmp invalid_addq


       maybeBq:
       ;///////////   its may be  BX
       cmp op1_value_code,9   ;/////////// if its b
       jz add_Bq               ; add it
       jmp invalid_addq             ; else its invalid

       maybeD_Sq:
       ;//////////////        its may be SI or DI
       cmp op1_value_code,1    ; SI value is 0 or DI is 1
       jle itsop2reg1
       jmp invalid_addq              ; if op1_value_code is above 1 then its invalid
       itsop2reg1:
       cmp op1_value_code,0    ; add value of SI
       jz add_Iq
       cmp op1_value_code,1    ; add value of DI
       jz add_Dq
       jmp invalid_addq
              
       
       add_Bq:
       cmp whichUser, 2
       jz takeSecondAdd_Bq
       mov al,RegistersArray2[2]
       mov ah,RegistersArray2[3]
       jmp contAdd_Bq
       takeSecondAdd_Bq:
       mov al,RegistersArray[2]
       mov ah,RegistersArray[3]
       contAdd_Bq:
       add memory_num,ax 
       jmp second_hq
       
       add_Dq:
       cmp whichUser, 2
       jz takeSecondAdd_Dq
       mov al,RegistersArray2[10]
       mov ah,RegistersArray2[11]
       jmp contAdd_Dq
       takeSecondAdd_Dq:
       mov al,RegistersArray[10]
       mov ah,RegistersArray[11]
       contAdd_Dq:
       add memory_num,ax 
       jmp second_hq
       
       
       add_Iq:
       cmp whichUser, 2
       jz takeSecondAdd_Iq
       mov al,RegistersArray2[8]
       mov ah,RegistersArray2[9]
       jmp contAdd_Iq
       takeSecondAdd_Iq:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       contAdd_Iq:
       add memory_num,ax 
       jmp second_hq
       
       
       its_numq:
       ConvertStrHexa first_half_str, temp_number
       mov ax,temp_number
       add memory_num,ax
       jmp second_hq
       
           
       second_hq:
       ; get its value and add it to memory num
       cmp second_half_str[2],'$'
       jnz fixThirtySix
       jmp end_op1q
       fixThirtySix:
       
       mov dl, second_half_str[3]
       mov first_in_op , dl
       call get_type_op
       cmp  detectType,0
       JZ   its_reg2q 
       jz  fixIts_num2q
       jmp its_num2q
       fixIts_num2q:
       
       its_reg2q:
       lea dx, second_half_str
       mov OP, dx
       call get_reg_code
       cmp isCommandValid, 0
       jne fixreg2q
       jmp invalid_addq
       fixreg2q:
       cmp op1_type , 0
       Jz maybeB2q
       cmp op1_type,1
       jz maybeD_S2q
       jmp invalid_addq

       maybeB2q:
       ;///////////   its may be  BX
       cmp op1_value_code,9   ;/////////// if its b
       jz add_B2q               ; add it
       jmp invalid_addq             ; else its invalid

       maybeD_S2q:
       ;//////////////        its may be SI or DI
       cmp op1_value_code,1    ; SI value is 0 or DI is 1
       jle its_reg2qvalid 
       jmp invalid_addq  
       its_reg2qvalid:            ; if op1_value_code is above 1 then its invalid
       cmp op1_value_code,0    ; add value of SI
       jz add_I2q
       cmp op1_value_code,1    ; add value of DI
       jz add_D2q
       jmp invalid_addq
       
       add_B2q:
       cmp whichUser, 2
       jz takeSecondAdd_B2q
       mov al,RegistersArray2[2]
       mov ah,RegistersArray2[3]
       jmp contAdd_B2q
       takeSecondAdd_B2q:
       mov al,RegistersArray2[2]
       mov ah,RegistersArray2[3]
       contAdd_B2q:
       add memory_num,ax 
       jmp end_op1q
       
       add_D2q:
       cmp whichUser, 2
       jz takeSecondAdd_D2q
       mov al,RegistersArray2[10]
       mov ah,RegistersArray2[11]
       jmp contAdd_D2q
       takeSecondAdd_D2q:
       mov al,RegistersArray[10]
       mov ah,RegistersArray[11]
       contAdd_D2q:
       add memory_num,ax  
       jmp end_op1q
       
       
       add_I2q:
       cmp whichUser, 2
       jz takeSecondAdd_I2q
       mov al,RegistersArray2[8]
       mov ah,RegistersArray2[9]
       jmp contAdd_I2q
       takeSecondAdd_I2q:
       mov al,RegistersArray[8]
       mov ah,RegistersArray[9]
       contAdd_I2q:
       add memory_num,ax  
       jmp end_op1q
       
       
       its_num2q:
       ConvertStrHexa second_half_str, temp_number
       mov ax,temp_number
       add memory_num,ax
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
   jmp finish_reg
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
   jmp finish_reg2
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
    
    cmp first_in_op ,48h
    jge its_char
    jl its_num
    
    its_num:
    mov detectType, 1
    jmp end_get  
    its_char:
    mov detectType, 0
    
    end_get:    
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
        MOV CL,0bh
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
mov dx, msg
mov msg, offset emptyString
mov yx, 1206h
mov bh, 0
call setCursor
call printMsg
mov msg, dx
mov yx, 1206h
mov bh, 0
call setCursor
call printMsg
mov ah, 86h
mov cx, 0Fh
mov dx, 4240H  ; making the program holds for about 5 seconds
int 15h 
popf
pop dx
pop cx
pop bx
pop ax
ret
Write_In_Game_Notif endp




receiveInstruction proc near
    mov msg, offset enterPower
    call Write_In_Game_Notif
    mov yx, 1400h
    mov bh, 0
    call setCursor   
    call deleteCommand
    mov ah,0
	int 16h             ; get the power up option in al
    
    cmp ah, 3eh     
    jz fix_cont_receiveInstruction
    jmp cont_receiveInstruction
    fix_cont_receiveInstruction:
    mov bl, 7
    call sendOneByte
    mov al, 1
    EndGame firstUsername, firstScore  ; abborted suddenly
    cont_receiveInstruction:

	sub al, 30h
    cmp al, 5
    ja InvalidReceiveInstruction
	cmp whichUser,1
	jnz second_power_up

    mov powerUp1,al      ; first user turn
    jmp pre_power
     
    second_power_up:      ; second user turn
    mov powerUp2,al
    
    pre_power: 

	
    call recive_power_up
    cmp levelnum, '2'
    jz level2Receive
    jmp endReceive 

    InvalidReceiveInstruction:
    call invalid_command_with_miuns 

    jmp endReceive

    level2Receive: 
    call level2AdditionalReceive
    cmp isCommandValid, 0
    jz endReceive
    mov level2Decision, al 
    
    endReceive:
ret
receiveInstruction endp


recive_power_up proc near 
    cmp whichUser, 2     ; dx: current score
    jz secondUserCurrent
    mov dx, firstScore
    jmp continue_recive_power_up
    secondUserCurrent:
    mov dx, secondScore
    continue_recive_power_up:


    cmp al, 0
    jz callExecuteRegisters
    cmp al, 1
    jz callExecuteOnOwnRegisters
    cmp al, 2
    jz callExecuteOnBothRegisters
    cmp al, 3
    jz callChangeForbidden
    cmp al, 4
    jz callClearRegisters
    cmp al, 5
    jnz fixCallChangeTargetValue
    jmp callChangeTargetValue
    fixCallChangeTargetValue:
    invalidPowerUp:
    mov msg, offset notPoweUp
    call Write_In_Game_Notif
    mov isCommandValid, 0
    jmp end_recive_power_up

    callExecuteRegisters:   
    call recive_command
    jmp end_recive_power_up

    callExecuteOnOwnRegisters:
    cmp dx, 5
    jae fixLessScore
    jmp LessScore
    fixLessScore:
    jmp callExecuteRegisters

    callExecuteOnBothRegisters:
    cmp dx, 3
    jae fixLessScore1
    jmp LessScore
    fixLessScore1:
    jmp callExecuteRegisters

    callChangeForbidden:
    cmp dx, 8
    jae fixLessScore20
    jmp LessScore
    fixLessScore20:

    ChangeForbidden:
    cmp whichUser, 2
    jz secondChangeForbidden
    mov dl, isForbiddenUsed1
    jmp contChangeForbidden
    secondChangeForbidden:
    mov dl, isForbiddenUsed2
    contChangeForbidden:
    cmp dl, 0
    jz incIsChanged
    mov msg, offset clearUsedMsg
    call Write_In_Game_Notif
    mov isCommandValid, 0
    jmp end_recive_power_up
    incIsChanged:
    cmp whichUser, 2
    jz secondChangeForbidden1
    inc isForbiddenUsed1
    jmp end_recive_power_up
    secondChangeForbidden1:
    inc isForbiddenUsed2

    jmp end_recive_power_up

    callClearRegisters:
    cmp dx, 30d
    jae fixLessScore21
    jmp LessScore
    fixLessScore21:

    clearAllRegisters:
    cmp whichUser, 2
    jz secondClearAllRegisters
    mov dl, isClearUsed1
    jmp contClearAllRegisters
    secondClearAllRegisters:
    mov dl, isClearUsed2
    contClearAllRegisters:
    cmp dl, 0
    jz incIsClear
    mov msg, offset clearUsedMsg
    call Write_In_Game_Notif
    mov isCommandValid, 0
    jmp end_recive_power_up
    incIsClear:
    cmp whichUser, 2
    jz secondClearAllRegisters1
    inc isClearUsed1
    jmp end_recive_power_up
    secondClearAllRegisters1:
    inc isClearUsed2
    
    jmp end_recive_power_up

    callChangeTargetValue:
    cmp levelnum, '2'
    je fixInvalidPowerUp
    jmp invalidPowerUp
    fixInvalidPowerUp:
    cmp whichUser, 2
    jz secondChangeTargetValue
    mov dl, isTargetUsed1
    jmp contChangeTargetValue
    secondChangeTargetValue:
    mov dl, isTargetUsed2
    contChangeTargetValue:
    cmp dl, 0
    jz incIsTarget
    mov msg, offset clearUsedMsg
    call Write_In_Game_Notif
    mov isCommandValid, 0
    jmp end_recive_power_up
    incIsTarget:
    cmp whichUser, 2
    jz secondChangeTargetValue1
    inc isTargetUsed1
    jmp end_recive_power_up
    secondChangeTargetValue1:
    inc isTargetUsed2
    jmp end_recive_power_up

    LessScore:
    mov msg, offset lessScoreMsg
    call Write_In_Game_Notif
    mov isCommandValid, 0
    end_recive_power_up:
    ret    
recive_power_up endp



recive_command proc near
    call FirstWrite   
    call checkCommand   
   
   ret
recive_command endp

deleteCommand proc near
    mov ax, 0600h
    mov bh, 0h
    mov cx, 1400h
    mov dx, 1411h
    int 10h
    mov cx, 1414h
    mov dx, 1425h
    int 10h
   ret
deleteCommand endp

receiveNewForbidden proc near
    EnterNewAgain:
	 mov ah,7h
	 int 21h
	  cmp ah,4Bh     
        jz  invalidNewChar
        cmp ah,4Dh
        jz  invalidNewChar
        cmp ah,48h
        jz  invalidNewChar
        cmp ah,50h
        jz  invalidNewChar
        cmp al,8h
        jz  invalidNewChar
        cmp al,09h
        jz  invalidNewChar
        cmp al,0dh
        jz  invalidNewChar
        cmp ah,47h
       jz  invalidNewChar
	   validNewChar:
        cmp whichUser,1
        jnz new_forbidden1

        mov forbiddenChar2,al      ; first user turn
        jmp endReceiveNewForbidden

        new_forbidden1:      ; second user turn
        mov forbiddenChar1,al
        jmp endReceiveNewForbidden
		invalidNewChar:
        mov msg, offset invalidForbiddenMsg
        call Write_In_Game_Notif
		jmp  EnterNewAgain
		endReceiveNewForbidden:
ret
receiveNewForbidden endp

validateNOP proc near
push si
push di
cmp instructionSTR[3], 'O'
jnz InvalidNOP
cmp instructionSTR[4], 'P'
jnz InvalidNOP

findDollar:
    cmp command[si], '$'
    jz endValidateNOP
    cmp command[si], ' '
    jnz InvalidNOP
    inc si
jz findDollar

InvalidNOP:
call invalid_command_with_miuns

endValidateNOP:
pop di
pop si
ret
validateNOP endp

level2AdditionalReceive proc near
mov msg, offset Level2ReceiveMsg
call Write_In_Game_Notif
mov ah, 0
int 16H

cmp ah, 3eh     
jz fix_cont_level2AdditionalReceive
jmp cont_level2AdditionalReceive
fix_cont_level2AdditionalReceive:
mov bl, 7
call sendOneByte
mov al, 1
EndGame firstUsername, firstScore  ; abborted suddenly
cont_level2AdditionalReceive:

sub al, 30h
cmp al, 1
jz endLevel2AdditionalReceive
cmp al, 2
jz endLevel2AdditionalReceive

call invalid_command_with_miuns

endLevel2AdditionalReceive:

ret
level2AdditionalReceive endp