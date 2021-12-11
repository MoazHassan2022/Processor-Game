
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

getScore macro inputScore, score ; macro to convert score to digits
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

.MODEL LARGE
.STACK 64
.DATA    
usernameRequest db 'Please enter your username:','$'
scoreRequest db 'Enter your initial score:','$' 
enter db 'Press Enter key to continue', '$'
startChating db 'To start chating press F2','$'
startGame db 'To start the game press F3','$'
endProgram db 'To end the program press ESC','$'
firstUsername db 15,?,15 dup('$') 
firstInputScore db 4,?,4 dup('$')
firstScore dw ?
secondUsername db 15,?,15 dup('$') 
secondInputScore db 4,?,4 dup('$')
secondScore dw ?
yx dw ?
msg dw ?
input dw ? 
notif db 'Choose the mode','$'
notif1 db '2tkallam ya 3rs', '$'


.CODE

Main proc far
    mov ax, @DATA
    mov ds, ax
    
    
    ;First User part ////////////////////// 
    
    call firstUser
    
    ;Request continue 'print message' 
    mov msg, offset enter
    call printMsg
    mov ah, 0
    int 16h
    cmp ah, 1ch ; check if enter is pressed
    jne end1
    call clearScreen
    mov al,01h ; change page(put its index in al (0..7))
    call changePage
    mov bh,0   ; getNotif requires setting the page number
    call getNotifReady ; get the notification bar ready in first page
    
    
    ;Second User part //////////////////////
    
    call secondUser
    
    ;Request continue 'print message' 
    mov msg, offset enter
    call printMsg
    mov ah, 0
    int 16h
    cmp ah, 1ch ; check if enter is pressed
    jne end1        
    call clearScreen
    mov al,00h ; change page(put its index in al (0..7))
    call changePage    
    mov bh,1   ; witeNotif calls setCursor so set the page
    call getNotifReady ; get the notification bar ready in second page
    ;mov bh,0
    ;call writeNotif
    
    ;//////////////MAIN SCREEN///////////////
    ;initializing cursor position
    mov bh,0 
    mov yx, 020Ah
    call setCursor
    
    
    ;'print message'
    mov msg, offset startChating
    call printMsg 
    
    mov yx, 050Ah
    call setCursor
    
    
    ;'print message'
    mov msg, offset startGame
    call printMsg
    
    mov yx, 080Ah
    call setCursor
    
    
    ;'print message'
    mov msg, offset endProgram
    call printMsg 
    mov bh,0 
    mov msg, offset notif
    call writeNotif
    
    mov ah, 0       ; check what key is pressed
    int 16h
    mov bh,0
    call clearScreen
    call clearNotif
    cmp ah, 3ch     ; check if F1 key is pressed
    je Chating 
    cmp ah, 3dh     ; check if F2 key is pressed
    je Game 
    cmp ah, 01h     ; check if ESC key is pressed
    je end1
    Chating:
        call firstChatMode 
        mov msg, offset notif1 
        call writeNotif
        mov yx, 0204h
        call setCursor
        mov ah, 0       ; buffer
        int 16h
        call secondChatMode
        mov bh,01 
        mov msg, offset notif1
        call writeNotif  
        mov bh,01
        mov yx, 0204h
        call setCursor
        mov ah, 0       ; buffer
        int 16h
        jmp end1
    Game:
        mov msg, offset startGame
        call printMsg    
           
    
    
    end1:
    
    hlt    
endp




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
changePage proc near
    pusha
    pushf
    mov ah,05h
    int 10h
    popf
    popa
    ret
endp 
clearScreen proc near
    pusha
    pushf
    mov ax, 0600h   ;clear screen
    mov bh,07
    mov cx,00
    mov dx,134fh
    int 10h
    popf
    popa
    ret
endp 
getNotifReady proc near
    pusha
    pushf 
    mov yx, 1400h 
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

firstUser proc near
    pusha
    pushf   
    ;initializing cursor position 
    mov yx, 020Ah
    call setCursor
    
    
    ;Request username 'print message'
    mov msg, offset usernameRequest
    call printMsg
    
    ;updating cursor position
    mov yx, 030Ah
    call setCursor
    
    ;getting username from user 'keyboard input'
    mov input, offset firstUsername
    call getInput     
    
    ;Score Part ////////////////////////
    
    ;updating cursor position
    mov yx, 0A0Ah
    call setCursor

    ;Request score 'print message' 
    mov msg, offset scoreRequest
    call printMsg
    
    ;updating cursor position
    mov yx, 0B0Ah
    call setCursor
    
    ;getting score from user 'keyboard input'
    mov input, offset firstInputScore
    call getInput    
    getScore firstInputScore, firstScore 
    
    ;updating cursor position
    mov yx, 0E0Ah
    call setCursor

    popf
    popa
    ret
endp

secondUser proc near
    pusha
    pushf
    
    ;initializing cursor position  
    mov bh,01 ;///////////IMPORTANT/////////// YOU HAVE TO SAY EHAT PAGE YOU WANT BEFORE SETCURSOR! #MOZAELSYA7
    mov yx, 020Ah
    call setCursor
    
    
    ;Request username 'print message'
    mov msg, offset usernameRequest
    call printMsg
    
    ;updating cursor position 
    mov bh,01
    mov yx, 030Ah
    call setCursor
    
    ;getting username from user 'keyboard input'
    mov input, offset secondUsername
    call getInput     
    
    ;Score Part ////////////////////////
    
    ;updating cursor position  
    mov bh,01
    mov yx, 0A0Ah
    call setCursor

    ;Request score 'print message' 
    mov msg, offset scoreRequest
    call printMsg
    
    ;updating cursor position 
    mov bh,01
    mov yx, 0B0Ah
    call setCursor
    
    ;getting score from user 'keyboard input'
    mov input, offset secondInputScore
    call getInput    
    getScore secondInputScore, secondScore 
    
    ;updating cursor position 
    mov bh,01
    mov yx, 0E0Ah
    call setCursor

    popf
    popa
    ret
endp

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
    mov yx, 0900h
    call setCursor
    mov ah,9
    mov al, '-'
    mov bl,0fh
    mov cx,80
    int 10h
    mov yx, 0a02h
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
    mov yx, 0900h
    call setCursor
    mov ah,9
    mov al, '-'
    mov bl,0fh
    mov cx,80
    int 10h
    mov yx, 0a02h
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

writeNotif proc near
    pusha
    pushf
    mov yx, 1600h 
    call setCursor  
    call printMsg
    popf
    popa
    ret
endp 
clearNotif proc near
    pusha
    pushf
    mov ax, 0602h   ;clear after bar
    mov bh,07
    mov cx,1500h
    mov dx,184fh
    int 10h
    popf
    popa
    ret
endp

end main


