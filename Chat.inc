
start_chat proc near
    call ChatMode
    mov cur_sender, 4875h
    mov printing_inductor, 0h
    call start_writing

start_chat endp
      

start_writing proc near
    mov yx,1600h  
    mov bh,1
    call setCursor
    mov writing_inductor,1600h
    

    get_more:
        push writing_inductor
        pop yx
        mov bh, 1
        call setCursor
        mov dx,3fdh
        in al,dx
        And al,1
        jz dontCallReceiveMsg
        call receiveMsg
        dontCallReceiveMsg:
    
        call getKeyMainScreen 
        cmp al, 0
        jz get_more
        cmp ah, 01h     ; check if ESC key is pressed
        jne dont_end_chat_waer
        call sendEndCurrent
        jmp main_Screen
        dont_end_chat_waer:
        cmp ah,4Bh
        jnz Not_mov_left
        call MovLeft    ; mov left and can up to high line
        JMP get_more
        Not_mov_left:
        cmp ah,4Dh
        jnz not_mov_right
        call MovRight ; mov right and can down with line
        JMP get_more
        not_mov_right:
        cmp al,8h
        jnz not_back_space 
        call backSpace ;
        JMP get_more
        not_back_space:
        cmp al,0dh
        jnz not_enter
        call EnterPressed ;;
        JMP get_more
        not_enter:
        
        mov dx,writing_inductor
        cmp dl,4Eh
        JNZ not_go_to_new_line
            call downline
        not_go_to_new_line:
    
        mov ah,9
        mov bh,1
        mov cx,1
        mov bl,0Fh 
        int 10h
        ;;;;
        mov Bx,writing_inductor
        
        push ax     ; just to save the value of al which carry the char
        
        sub bh,16h
        mov al,bh
        mov ah,0
        mov cx,4Eh
        mul cx
        add al,bl
        mov bx,ax
        add bx,2
        
        pop ax
        
        mov stringmsg[bx],al
        ;;;;;;;;;;;;;
        call MovRight   

    jmp far ptr get_more



start_writing endp


ChatMode proc near
    mov al ,01h
    call changePage

    mov bh,1
    mov yx,1400h
    call Draw_H_Line
    
    mov yx,1500h
    mov bh,1
    mov msg,offset write_msg
    call setCursor
    call printMsgAtyx

    ret
ChatMode endp 

upline proc near
    mov dx,writing_inductor
    cmp dh,16h
    jle end_upline
    dec dh
    mov dl,4eh
    mov writing_inductor,dx
    mov yx,dx   
    mov bh,1
    call setCursor
    end_upline:
    ret
upline endp

MovLeft proc near
    mov dx,writing_inductor
    cmp dl,00h
    jz upline_then_end
    dec dl 
    mov writing_inductor,dx
    mov yx,dx   
    mov bh,1
    call setCursor
    jmp end_mov_left
    
    upline_then_end:
    call upline
    end_mov_left:
    ret
MovLeft endp



MovRight proc near

    mov dx,writing_inductor
    cmp dl,4Dh
    jz downline_then_end
    inc dl 
    mov writing_inductor,dx
    mov yx,dx   
    mov bh,1
    call setCursor
    jmp end_mov_right
    
    downline_then_end:
    call downline
    
    end_mov_right:    
    ret
MovRight endp


downline proc near
    mov dx,writing_inductor
    cmp dh,18h
    jae end_downline
    inc dh
    mov dl,0
    mov writing_inductor,dx
    mov yx,dx   
    mov bh,1
    call setCursor
    end_downline:
    ret
downline endp

backSpace proc near

    mov dl,' ' 
    mov ah,2
    int 21h
    call MovLeft
    mov dl,' ' 
    mov ah,2
    int 21h 
    
    mov dx,writing_inductor
    mov yx,dx
    mov bh,1
    call setCursor
    ret
backspace endp

EnterPressed proc near

        mov Bx,writing_inductor
        sub bh,16h
        mov al,bh
        mov ah,0
        mov cx,4Eh
        mul cx
        add al,bl
        mov bx,ax
        add bx,2
        
        cmp bx,2
        jz no_text_typed
        
        mov stringmsg[bx],'$'
        
        call clear_writing_area
    
    cmp whichUser, 2
    jz nextIsSecond
    mov next_sender , offset firstUsername
    jmp contNext
    nextIsSecond:
    mov next_sender , offset secondUsername
    contNext:
    call sendMsg
    lea di , StringMsg
    add di,2 
    CALL print_in_chat
    jmp end_enter
    
    no_text_typed:

    
    end_enter:
        mov yx,1600h
        mov bh,1
        call setCursor
        mov writing_inductor,1600h
EnterPressed endp


clear_writing_area proc near
        mov ah, 6               
        mov al, 0h              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 16h               ; row top
        mov cl, 0               ; col left
        mov dh, 19h             ; row bottom
        mov dl, 4fh              ; col right
        int 10h
        
        mov yx,1600h
        mov bh,1
        call setCursor
        mov writing_inductor,1600h  

        ret
clear_writing_area endp

    
; if cur_sender === next_sender so we dont need to print the name
; make di stop in the begin of string
; name var point to sender name    
    

 print_in_chat proc near
     
 MOV Ax , next_sender
 cmp cur_sender , Ax
 jz print_without_name
 
 mov ax, printing_inductor
 cmp ah, 13h
 jnz dontScrollName
 call scroll_up_chat
 dontScrollName:
 
 push printing_inductor
 pop yx
 mov bh,1
 call setCursor
 mov si, next_sender
 add si, 2
 call setCursor
 printUserName:
 mov al, [si]
 cmp al, '$'
 jz outPrintUserName
 mov ah, 9
 mov bh, 1
 mov cx, 1
 mov bl, 04h
 int 10h
 inc si
 inc yx
 call setCursor
 jmp printUserName
 outPrintUserName:
 
 mov ax, printing_inductor
 inc ah

 mov al,0
 mov printing_inductor,ax
 mov yx,ax
 mov bh,1
 call setCursor
 
 print_without_name:
 push printing_inductor
 pop yx
 mov bh,1
 call setCursor
 
 print_msg_in_chat:
    mov ax , printing_inductor
    cmp ah, 13h
    jnz dont_scroll_up
    call scroll_up_chat
    dont_scroll_up: 

    cmp al , 4Eh
    jnz dont_down_line
        call downline_print
    dont_down_line:
    
    mov al,[di]
    mov ah,9
    mov bh,1
    mov cx,1
    mov bl,0Fh 
    int 10h

    mov al,20h
    mov [di],al
    inc di
    mov ax , printing_inductor
    inc al
    mov printing_inductor , ax
    mov yx,ax
    mov bh,1
    call setCursor
    
    
    mov al,24h
     cmp [di],al
     jnz print_msg_in_chat 

    mov ax,printing_inductor
    add ah,1
    mov al,0
    mov printing_inductor , ax
    mov ax, printing_inductor

         
 push next_sender    
 pop cur_sender                   
RET   
print_in_chat endp 
     
     
downline_print proc near
    mov dx,printing_inductor
    inc dh
    cmp dh,14h
    jl noscroll
    call scroll_up_chat
    noscroll:
    mov dl,0
    mov printing_inductor,dx
    mov yx,dx   
    mov bh,1
    call setCursor

    ret
downline_print endp

scroll_up_chat proc near
    push ax
    push bx
    push cx
    push dx
    pushf
    mov ah, 6               
    mov al, 1h              ; number of lines to scroll
    mov bh, 0               ; attribute
    mov ch, 0h               ; row top
    mov cl, 0               ; col left
    mov dh, 13h             ; row bottom
    mov dl, 4fh              ; col right
    int 10h

    mov ax,printing_inductor
    dec ah
    mov al,0
    mov printing_inductor ,ax
    mov yx, ax
    mov bh,1
    call setCursor

    popf
    pop dx
    pop cx
    pop bx
    pop ax

ret
scroll_up_chat endp

sendMsg proc near
    mov si, 2
    sendLoopStrMsg:
    mov dx , 3FDH		; Line Status Register
    againSendMsg:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ againSendMsg
    cmp StringMsg[si], '$'
    jz outSendStrMsg
    
    mov al, StringMsg[si]
    mov dx, 3f8h
    out dx, al
    inc si
    jmp sendLoopStrMsg
    outSendStrMsg:
    ; to end the receving  you should send a $
    mov dx , 3FDH		; Line Status Register
    againSendMsg1:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ againSendMsg1
    
    mov dx, 3f8h
    mov al,'$'
    out dx,al
    
ret
sendMsg endp

receiveMsg proc near 

    mov si,2
    getStringMsg:
    mov dx,3fdh
    in al,dx
    And al,1
    jnz getCharOfStrMsg
    jmp getStringMsg


    getCharOfStrMsg:
    mov dx,3f8h
    in al,dx
    cmp al, 0   ; This means end of chat
    jnz contGetCharOfStrMsg
    jmp main_Screen
    contGetCharOfStrMsg:
    cmp al,'$'
    jz theEndOfStrMsg
    mov ReceivedMsg[si],al
    inc si 

    jmp getStringMsg
    theEndOfStrMsg:
    mov ReceivedMsg[si],'$'

    cmp whichUser, 1
    jz nextIsSecond1
    mov next_sender , offset firstUsername
    jmp contNext1
    nextIsSecond1:
    mov next_sender , offset secondUsername
    contNext1:
    lea di , ReceivedMsg
    add di,2 
    CALL print_in_chat

    endReceiveChat:
ret 
receiveMsg endp

