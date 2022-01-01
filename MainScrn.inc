;/////////////////
;get info from users
Get_Info proc near
    push ax
push bx
push cx
push dx
    pushf
	;First User part ////////////////////// 
    
    call firstUser
    
    ;Request continue 'print message' 
    mov msg, offset enterMsg
    call printMsg
    checkEnter:	
    mov ah, 0
    int 16h
    cmp ah, 1ch ; check if enter is pressed
    jne checkEnter
    call clearScreen
    mov al,01h ; change page(put its index in al (0..7))
    call changePage
    mov bh,0   ; getNotif requires setting the page number
    mov yx, 1500h
    call Draw_H_Line ;//middle line ; get the notification bar ready in first page
    
    
    ;Second User part //////////////////////
    
    call secondUser
    
    ;Request continue 'print message' 
    mov msg, offset enterMsg
    call printMsg
    checkEnter2:
    mov ah, 0
    int 16h
    cmp ah, 1ch ; check if enter is pressed
    jne checkEnter2
    call clearScreen
    mov al,00h ; change page(put its index in al (0..7))
    call changePage    
    mov bh,1   ; witeNotif calls setCursor so set the page
    mov yx, 1500h
    call Draw_H_Line ; get the notification bar ready in second page

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
Get_Info endp


;//////////////////////
; get user mode choose
;/////////maaaaain//////////////
MainScreen proc  near
push ax
push bx
push cx
push dx
pushf

;//////////////MAIN SCREEN FOR FIRST USERA///////////////
    ;initializing cursor position 
    mov al,0
    call changePage
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
    mov msg, offset Choose_the_mode
    call Write_Not_First_Line 
    checkMode:
    mov ah, 0       ; check what key is pressed
    int 16h
    
    cmp ah, 3ch     ; check if F2 key is pressed
    je ChatingGo 
    cmp ah, 3dh     ; check if F3 key is pressed
    je GameGo 
    cmp ah, 01h     ; check if ESC key is pressed
    jne fixMozaTwo
    jmp end1
    fixMozaTwo:
    jmp checkMode
    ChatingGo:
    mov bh,0
    call clearScreen
    call clearNotifcationArea
    mov firstMode,0
    call MainScreen2
    gameGo:
    mov bh,0
    call clearScreen
    call clearNotifcationArea 
    mov firstMode,1
    call MainScreen2
    jmp game
    
popf
pop dx
pop cx
pop bx
pop ax
ret
MainScreen endp 

MainScreen2 proc  near
push ax
push bx
push cx
push dx
pushf

;//////////////MAIN SCREEN FOR SECOND USER///////////////
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
    cmp firstMode, 1    ; Check what was the first user chosen mode -> 0>>chat. 1>>game
    je gameInvite
    mov msg, offset chatInvitation
    call Write_Not_First_Line
    jmp checkSecondMode
    gameInvite:
    mov msg, offset gameInvitation
    call Write_Not_First_Line 
    
    
    checkSecondMode:
    mov ah, 0       ; check what key is pressed
    int 16h
    
    cmp ah, 3ch     ; check if F2 key is pressed
    je Chating2Go 
    cmp ah, 3dh     ; check if F3 key is pressed
    je Game2Go 
    cmp ah, 01h     ; check if ESC key is pressed
    jne fixMozaOne
    jmp end1
    fixMozaOne:
    jmp checkMode
    Chating2Go:
    mov bh,0
    call clearScreen
    call clearNotifcationArea 
    cmp firstMode, 1 ; check if the first user chosen mode was game 
    je callMainScreen
    jmp Chating
    Game2Go:
    mov bh,0
    call clearScreen
    call clearNotifcationArea
    cmp firstMode, 0 ; check if the first user chosen mode was chat 
    je callMainScreen
    jmp game 
    callMainScreen:
    call MainScreen
    
popf
pop dx
pop cx
pop bx
pop ax
ret
MainScreen2 endp



;/////////////////////////////////
; recive first user data
firstUser proc near
    push ax
push bx
push cx
push dx
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
    Num_Input firstInputScore, firstScore 
    
    ;updating cursor position
    mov yx, 0E0Ah
    call setCursor

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
firstUser endp
;/////////////////////////////////
; recive second user data
secondUser proc near
    push ax
push bx
push cx
push dx
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
    Num_Input secondInputScore, secondScore 
    mov ax, firstScore ; getting smaller score 
    cmp ax, secondScore ; if lower make secondScore = firstScore
    jbe makeSecondScore
    mov ax, secondScore ; second score is lower
    mov firstScore, ax
    jmp continueSecondUser
    makeSecondScore:
    mov secondScore, ax 
    continueSecondUser:
    ;updating cursor position 
    mov bh,01
    mov yx, 0E0Ah
    call setCursor

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
secondUser endp
;///////////////////////////////////////


