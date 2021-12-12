firstChatMode proc near
    pusha
    pushf
    mov bh,0
    mov yx, 0102h
    call setCursor
    mov dx, yx
    add dl, firstUsername+1 
    mov msg, offset firstUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h
    mov yx, 0A00h
    Call Draw_H_Line ;middle line
    mov yx, 0B02h
    call setCursor
    mov dx, yx
    add dl, secondUsername+1 
    mov msg, offset secondUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h
    mov yx, 0204h
    call setCursor
    popf
    popa
    ret
endp 

secondChatMode proc near
    pusha
    pushf
    mov al,01
    call changePage
    mov bh,1
    mov yx, 0102h
    call setCursor
    mov dx, yx
    add dl, secondUsername+1 
    mov msg, offset secondUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h
    mov yx, 0A00h
    Call Draw_H_Line ;middle line
    mov yx, 0B02h
    call setCursor
    mov dx, yx
    add dl, firstUsername+1 
    mov msg, offset firstUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h
    
    popf
    popa
    ret
endp