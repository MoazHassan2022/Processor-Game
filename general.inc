; set  the cursor at postion exist in var( yx )
setCursor proc near
    pusha
    pushf
    
    mov ah, 2
    mov dx,yx
    int 10h

    popf
    popa
    ret  
endp

;////////////////////////////////////////
; write the mesagee in var ( msg ) in postion in var ( yx )

printMsgAtyx proc near
    pusha
    pushf

    call setCursor 
    mov ah, 9
    mov bh,2h
    mov dx, msg
    int 21h
    
    popf
    popa
    ret
endp

;//////////////////////////////
;print msg in var( msg ) in current curser postion 
printMsg proc near
    pusha
    pushf
    mov ah, 9
    mov dx, msg
    int 21h
    popf
    popa
    ret
endp
;//////////////////////////////////
; get the input and put it in var( input )
getInput proc near
    pusha
    pushf
    mov ah, 0Ah
    mov dx, input
    int 21h
    popf
    popa
    ret
endp
;/////////////////////////////////
;chage between pages with the value in al
changePage proc near
    pusha
    pushf
    mov ah,05h
    int 10h
    popf
    popa
    ret
endp
;//////////////////////////////////
; clean the screen except the notification area
clearScreen proc near
    pusha
    pushf
    mov ax, 0600h   ;clear screen
    mov bh,07
    mov cx,00
    mov dx,184fh
    int 10h
    popf
    popa
    ret
endp
;///////////////////////////////
;Draw horizontal line at var ( yx )
Draw_H_Line proc near
    pusha
    pushf 
    call setCursor 
    mov ah,9
    mov al, '-'
    mov bl,0fh
    mov cx,80
    int 10h
    popf
    popa
    ret
endp
;//////////////////////////////
;Clear Notification Area
clearNotifcationArea proc near
    pusha
    pushf
    mov ax, 0602h   ;clear after bar
    mov bh,07
    mov cx,1700h
    mov dx,184fh
    int 10h
    popf
    popa
    ret
endp
;//////////////////////
; recive number and convert it from user
Num_Input macro inputScore, score ; macro to convert score to digits
    LOCAL one,two,three,end
    pusha
    pushf    
    mov ah,0
    mov al,inputScore + 2 ; get first char
    mov bl , inputScore + 1
    cmp bl , 1   ; compare size with 1 if yes then go to this case
    jz one
    cmp bl , 2  ; compare size with 2 if yes then go to this case
    jz two 
    cmp bl , 3  ; compare size with 2 if yes then go to this case
    jz three
    one:
    sub al, 30h
    mov dx, ax  
    jmp end
    two:
    sub al, 30h
    mov cl, 10
    mul cl      ; ax = al * 10
    mov dx, ax    
    mov al,inputScore + 3  ; get second char
    sub al, 30h
    add dx,ax 
    jmp end  
    three:
    sub al, 30h
    mov cl, 100
    mul cl      ; ax = al * 10
    mov dx, ax    
    mov al,inputScore + 3  ; get second char
    sub al, 30h
    mov cl, 10
    mul cl 
    add dx,ax
    mov al,inputScore + 4   ; get 3rd char
    sub al, 30h
    mov ah,0
    add dx,ax
    
    end:
    mov score, dx
    popf
    popa
    
    Endm getScore
;///////////////////////////////////
; write in first line in notification area with msg in var( msg )
Write_Not_First_Line proc near
    pusha
    pushf   
    
    call clearNotFirst
    mov yx, 1600h 
    call setCursor  
    call printMsg
    
    popf
    popa
    ret
endp

;///////////////////////////////////
; write in seconline in notification area with sg in var( msg )
Write_Not_Second_Line proc near
    pusha
    pushf   
    
    call clearNotSecond
    mov yx, 1700h 
    call setCursor  
    call printMsg
    
    popf
    popa
    ret
endp
;///////////////////////////////
;Clear first line in Notifiction area
clearNotFirst proc near
    pusha
    pushf
    mov ax, 0602h   ;clear after bar
    mov bh,07
    mov cx,1700h
    mov dx,174fh
    int 10h
    popf
    popa
    ret
endp


;///////////////////////////////
;Clear Second line in Notifiction area
clearNotSecond proc near
    pusha
    pushf
    mov ax, 0602h   ;clear after bar
    mov bh,07
    mov cx,1800h
    mov dx,184fh
    int 10h
    popf
    popa
    ret
endp

    