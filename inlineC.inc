inlinechat proc near 
push ax
push bx
push cx
push dx
pushf
looptoinlinechat:
push inlineChatindicator
pop yx
mov bh,0
call setcursor
mov ah,0
int 16h

cmp al,8h
jnz inlinechatbackspace
call inlinespace
jmp looptoinlinechat
inlinechatbackspace:
cmp al,0dh
jnz itisnotenter
call msgenter
jmp looptoinlinechat
itisnotenter:
cmp ah,0Fh
jz theuserwillchangethemode

mov dx,inlineChatindicator
cmp dl,27h                ;if he arrivel to the end of the line
jz looptoinlinechat


;;;; ptint the char in al
mov ah,9
mov bh,0
mov cx,1
mov bl,0Fh 
int 10h
;;;;;;;;;;
mov bx,inlinechatindicator
mov bh,0
sub bl,startofinlinechat
ADD BL,2
mov di,bx
mov stringmsg[di],al                      
;;;;;; mov cursr to right
mov ax,inlinechatindicator
inc al                    ; mov cursur one right
mov inlinechatindicator,ax
mov yx,ax
mov bh,0
call setCursor


jmp looptoinlinechat

theuserwillchangethemode:

popf
pop dx
pop cx
pop bx
pop ax
ret
inlinechat endp



;''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
;/////////////////////
; BACK SPACE

inlinespace proc near
    push ax
push bx
push cx
push dx
    pushf
    
        call msginnermovleft

        mov al,' '
        mov ah,9
        mov bh,0
        mov cx,1
        mov bl,0Fh 
        int 10h

        mov dx,inlineChatindicator
        mov yx,dx
        mov bh,0
        call setCursor

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
inlinespace endp

;///////////////////////////////////////
; MOVE LEFT
msginnermovleft proc near
    push ax
push bx
push cx
push dx
    pushf

        mov dx,inlineChatindicator 
        
        cmp dl,startofinlinechat
        jz finsh_move_left
        dec dl 
        mov inlineChatindicator,dx
        mov yx,dx   
        mov bh,0
        call setCursor
          
        finsh_move_left:
        
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
msginnermovleft endp

;//////////////////////////////////////////
; PRRESS ENTER

msgenter proc near
    push ax
push bx
push cx
push dx
    pushf
    
    mov bx,inlineChatindicator
    mov bh,0
    sub bl,startofinlinechat
    ADD BL,2
    mov di,bx
    mov stringmsg[di],'$'  ;here we will call the second procedure to send the massage and clearing the line to write again
    mov bl,8
    call sendOneByte
    call sendMsg
    call clearmsg
    
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
msgenter endp

clearmsg proc near
        mov cx,inlineChatindicator
        mov ah, 6               
        mov al, 0h              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov cl,startofinlinechat
        mov dh, ch             ; row bottom
        mov dl, 27h            ; col right
        int 10h
mov inlineChatindicator,cx
mov yx,cx
mov bh,0
call setcursor
ret
clearmsg endp

clearprintedmsg proc near

        mov cx,printinlinechatindicator
        mov ah, 6               
        mov al, 0h              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov cl, startofinlinechat
        mov dh, ch             ; row bottom
        mov dl, 27h            ; col right
        int 10h

ret
clearprintedmsg endp

;//////////////////////////////////////
; ARRIVE MAX LENGTH  

receiveinlineMsg proc near 

    CALL clearprintedmsg

    mov si,2
    getStringMsg2:
    mov dx,3fdh
    in al,dx
    And al,1
    jnz getCharOfStrMsg2
    jmp getStringMsg2

    getCharOfStrMsg2:
    mov dx,3f8h
    in al,dx
    contGetCharOfStrMsg2:
    cmp al,'$'
    jz theEndOfStrMsg2
    mov ReceivedMsg[si],al
    inc si 

    jmp getStringMsg2
    theEndOfStrMsg2:
    mov ReceivedMsg[si],'$'
    mov dx,printinlinechatindicator
    mov yx,dx
    mov msg ,offset ReceivedMsg[2]
    call printMsgAtyx
    endReceiveChat2:
ret 
receiveinlineMsg endp

