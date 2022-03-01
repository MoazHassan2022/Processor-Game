;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;General;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
; set  the cursor at postion exist in var( yx )
setCursor proc near
    push ax
push bx
push cx
push dx
    pushf
    
    mov ah, 2
    mov dx,yx
    int 10h

    popf
    pop dx
pop cx
pop bx
pop ax
    ret  
setCursor endp

;////////////////////////////////////////
; write the mesagee in var ( msg ) in postion in var ( yx )

printMsgAtyx proc near
    push ax
push bx
push cx
push dx
    pushf

    call setCursor 
    mov ah, 9
    mov bh,2h
    mov dx, msg
    int 21h
    
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
printMsgAtyx endp

;//////////////////////////////
;print msg in var( msg ) in current curser postion 
printMsg proc near
    push ax
push bx
push cx
push dx
    pushf
    mov ah, 9
    mov dx, msg
    int 21h
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
printMsg endp
;//////////////////////////////////
; get the input and put it in var( input )
getInput proc near
    push ax
push bx
push cx
push dx
    pushf
    inputWasEnter:
    mov ah, 0Ah
    mov dx, input
    int 21h
    mov di, input
    mov ax, [di] + 2
    cmp ax, 240Dh
    je inputWasEnter
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
getInput endp
;/////////////////////////////////
;chage between pages with the value in al
changePage proc near
    push ax
push bx
push cx
push dx
    pushf
    mov ah,05h
    int 10h
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
changePage endp
;//////////////////////////////////
; clean the screen except the notification area
clearScreen proc near
    push ax
push bx
push cx
push dx
    pushf

    ;Resetting the DOS screen
    mov ah,0 
    mov al,13h
    int 10h 
    
    mov ah,0 
    mov al,3h
    int 10h 

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
clearScreen endp
;///////////////////////////////
; clean the screen except the notification area
clearScreenGame proc near
    push ax
push bx
push cx
push dx
    pushf

    ;Resetting the DOS screen
    mov ah,0 
    mov al,3h
    int 10h 
    
    mov ah,0 
    mov al,13h
    int 10h 

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
clearScreenGame endp
;///////////////////////////////
;Draw horizontal line at var ( yx )
Draw_H_Line proc near
    push ax
push bx
push cx
push dx
    pushf 
    call setCursor 
    mov ah,9
    mov al, '-'
    mov bl,0fh
    mov cx,80
    int 10h
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
Draw_H_Line endp
;//////////////////////////////
;Clear Notification Area
clearNotifcationArea proc near
    push ax
push bx
push cx
push dx
    pushf
    mov ax, 0602h   ;clear after bar
    mov bh,07
    mov cx,1700h
    mov dx,184fh
    int 10h
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
clearNotifcationArea endp
;//////////////////////
; recive number and convert it from user
Num_Input macro inputScore, score, parse_int ; macro to convert score to digits
    LOCAL one,two,three,end, success, notInt
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
    cmp al, 0   ; parse_int 
    jb notInt   ; parse_int 
    cmp al, 9   ; parse_int 
    ja notInt   ; parse_int
    mov dx, ax  
    jmp success
    two:
    sub al, 30h
    cmp al, 0   ; parse_int 
    jb notInt   ; parse_int 
    cmp al, 9   ; parse_int 
    ja notInt   ; parse_int
    mov cl, 10
    mul cl      ; ax = al * 10
    mov dx, ax    
    mov al,inputScore + 3  ; get second char
    sub al, 30h
    cmp al, 0   ; parse_int 
    jb notInt   ; parse_int 
    cmp al, 9   ; parse_int 
    ja notInt   ; parse_int
    add dx,ax 
    jmp success  
    three:
    sub al, 30h
    cmp al, 0   ; parse_int 
    jb notInt   ; parse_int 
    cmp al, 9   ; parse_int 
    ja notInt   ; parse_int
    mov cl, 100
    mul cl      ; ax = al * 10
    mov dx, ax    
    mov al,inputScore + 3  ; get second char
    sub al, 30h
    cmp al, 0   ; parse_int 
    jb notInt   ; parse_int 
    cmp al, 9   ; parse_int 
    ja notInt   ; parse_int
    mov cl, 10
    mul cl 
    add dx,ax
    mov al,inputScore + 4   ; get 3rd char
    sub al, 30h
    cmp al, 0   ; parse_int 
    jb notInt   ; parse_int 
    cmp al, 9   ; parse_int 
    ja notInt   ; parse_int
    mov ah,0
    add dx,ax
    
    success:
    mov score, dx
    mov parse_int, 1
    jmp end

    notInt:
    mov parse_int, 0

    end:
    mov score, dx
    popf
    popa
    
Endm Num_Input
;///////////////////////////////////

; write in first line in notification area with msg in var( msg )
Write_Not_First_Line proc near
    push ax
push bx
push cx
push dx
    pushf   
    
    call clearNotFirst
    mov yx, 1700h 
    call setCursor  
    call printMsg
    
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
Write_Not_First_Line endp

;///////////////////////////////////
; write in seconline in notification area with sg in var( msg )
Write_Not_Second_Line proc near
    push ax
push bx
push cx
push dx
    pushf   
    
    call clearNotSecond
    mov yx, 1800h 
    call setCursor  
    call printMsg
    
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
Write_Not_Second_Line endp
;///////////////////////////////
;Clear first line in Notifiction area
clearNotFirst proc near
    push ax
push bx
push cx
push dx
    pushf
    mov ax, 0602h   ;clear after bar
    mov bh,07
    mov cx,1700h
    mov dx,174fh
    int 10h
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
clearNotFirst endp


;///////////////////////////////
;Clear Second line in Notifiction area
clearNotSecond proc near
    push ax
push bx
push cx
push dx
    pushf
    mov ax, 0602h   ;clear after bar
    mov bh,07
    mov cx,1800h
    mov dx,184fh
    int 10h
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
clearNotSecond endp                   

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

uart proc near
push ax
push DX
    ;set divisor latch access bit
        mov dx, 3fbh
    mov al, 10000000b
    out dx, al
    
    ;set LSB byte of the baud rate divisor latch register
    mov dx, 3f8h
    mov al, 0ch
    out dx, al
    
    ;set MSB byte of the Baud rate divisor latch register
    mov dx, 3f9h
    mov al, 00h
    out dx, al
    
    ;set port configuration
    mov dx, 3fbh
    mov al, 00011011b ;Bit 0, for receiver buffer, transmitter buffer
    out dx, al
    
pop dx
pop ax
    ret       
uart endp   

sendEndCurrent proc near
    mov dx , 3FDH		; Line Status Register
    againSendEndCurrent1:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ againSendEndCurrent1
    
    mov dx, 3f8h
    mov al,0
    out dx,al
ret
sendEndCurrent endp

delay proc near
system_time:   
  mov  ah, 2ch
  int  21h 
  xor  dh, dh   
  mov  ax, dx   
  mov  bl, 80
  div  bl      
  cmp  ah, 0   
  jnz  system_time
  ret
delay endp