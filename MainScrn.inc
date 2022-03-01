;/////////////////
;get info from users

;the first moza compares if he is second or first user  
; if he is first moza will send his name  and the score
; and will receiving the second user score and name




; if he is second 
; will receiving the first user name and will get the first user score
; send his score and it will be the min score and will send the name


;//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Get_Info proc near
    push ax
push bx
push cx
push dx
    pushf
    cmp al, 2 
    jnz fixCallSecondUser
    jmp callSecondUser
    fixCallSecondUser:
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
    ; send firstUsername, firstSore /////////// SERIAL ////////////

    mov dx, 3f8h
    mov si, 2

    sendLoopFirstUsername:
    mov dx , 3FDH		; Line Status Register
    AGAIN:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN
    cmp firstUsername[si], '$'
    jz outSendLoopFirstUsername
    
    mov al, firstUsername[si]
    mov dx, 3f8h
    out dx, al
    inc si
    jmp sendLoopFirstUsername
    outSendLoopFirstUsername:
    ; to end the receving  you should send a $
    mov dx , 3FDH		; Line Status Register
    AGAIN1:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN1
    
    mov dx, 3f8h
    mov al,firstUsername[si]
    out dx,al
    ; end sending first username
    mov ax, firstScore 

    mov cl, al
    mov dx , 3FDH		; Line Status Register
    AGAIN2:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN2
    mov dx, 3f8h
    mov al, ah
    out dx, al
    mov dx , 3FDH		; Line Status Register
    AGAIN3:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN3
    mov dx, 3f8h
    mov al, cl
    out dx, al
    ; end sending first score
    mov yx, 0B0Dh
    call setCursor
    mov msg, offset waitMsg
    call printMsg

    ; receiving the second score 
    mov dx , 3FDH		; Line Status Register
	  getseconduserscore1:	
    in al , dx 
  	AND al , 1
  	JZ getseconduserscore1
    mov dx, 3f8h
    in al, dx
    mov ch, al
    mov dx , 3FDH		; Line Status Register
    getseconduserscore2:	
    in al , dx 
  	AND al , 1
  	JZ getseconduserscore2
    mov dx, 3f8h
    in al, dx
    mov cl, al
    mov firstScore, cx
    mov secondScore, cx

    mov si,2
    getthesecondusername:
    mov dx,3fdh
    in al,dx
    And al,1
    jnz getcharofsecondusername
    jmp getthesecondusername


    getcharofsecondusername:
    mov dx,3f8h
    in al,dx
    cmp al,'$'
    jz theendofthesecondusername
    cmp al, '`'
    jz getthesecondusername
    mov secondUsername[si],al
    inc si 

    jmp getthesecondusername
    theendofthesecondusername:
    mov secondUsername[si],al

    call clearScreen

    ;//////////////////////////////////////////////////////////////////////////////////

    ;///////////////////////
    mov bh,0   ; getNotif requires setting the page number
    mov yx, 1500h
    call Draw_H_Line ;//middle line ; get the notification bar ready in first page
    popf
    pop dx
    pop cx
    pop bx
    pop ax
    ret
    ;Second User part //////////////////////
    callSecondUser:
    ; loop to wait to receive firstUsername, firstSore /////////// SERIAL ////////////
    ; the first loop to get the first user name and the his score
    ;we will wait to receving 
    mov yx, 0B0Dh
    call setCursor
    mov msg, offset waitMsg
    call printMsg

    mov si,2
    getthefirstusername:
    mov dx,3fdh
    in al,dx
    And al,1
    jnz getcharoffirstusername
    jmp getthefirstusername


    getcharoffirstusername:
    mov dx,3f8h
    in al,dx
    cmp al,'$'
    jz theendofthefirstusername
    cmp al, '`'
    jz getthefirstusername
    mov firstUsername[si],al
    inc si 

    jmp getthefirstusername
    theendofthefirstusername:
    mov firstUsername[si],al

    ; receiving the first score 
    mov dx , 3FDH		; Line Status Register
	  getfirstuserscore1:	
    in al , dx 
  	AND al , 1
  	JZ getfirstuserscore1
    mov dx, 3f8h
    in al, dx
    mov ch, al
    mov dx , 3FDH		; Line Status Register
    getfirstuserscore2:	
    in al , dx 
  	AND al , 1
  	JZ getfirstuserscore2
    mov dx, 3f8h
    in al, dx
    mov cl, al
    mov firstScore, cx

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

    mov ax, firstScore ; getting smaller score 
    cmp ax, secondScore ; if lower make secondScore = firstScore
    jbe makeSecondScore
    mov ax, secondScore ; second score is lower
    mov firstScore, ax
    jmp continueSecondUser
    makeSecondScore:
    mov secondScore, ax 
    continueSecondUser:

    mov ax, firstScore 

    mov cl, al
    mov dx , 3FDH		; Line Status Register
    AGAIN4:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN4
    mov dx, 3f8h
    mov al, ah
    out dx, al
    mov dx , 3FDH		; Line Status Register
    AGAIN5:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN5
    mov dx, 3f8h
    mov al, cl
    out dx, al
    ; end sending score
    ; start sending second username
    mov si, 2
    sendLoopSecondUsername:
    mov dx , 3FDH		; Line Status Register
    AGAIN6:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN6
    cmp secondUsername[si], '$'
    jz outSendLoopSecondUsername
    
    mov al, secondUsername[si]
    mov dx, 3f8h
    out dx, al
    inc si
    jmp sendLoopSecondUsername
    outSendLoopSecondUsername:
    ; to end the receving  you should send a $
    mov dx , 3FDH		; Line Status Register
    AGAIN7:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN7
    
    mov dx, 3f8h
    mov al,secondUsername[si]
    out dx,al

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
    startMainAgain:
    mov al,0
    call changePage
    call clearScreen
    mov bh,0 
    mov yx, 050Ah
    call setCursor
    
    
    ;'print message'
    mov msg, offset startChating
    call printMsg 
    
    mov yx, 080Ah
    call setCursor
    
    
    ;'print message'
    mov msg, offset startGame
    call printMsg
    
    mov yx, 0B0Ah
    call setCursor
    
    
    ;'print message'
    mov msg, offset endProgram
    call printMsg 
    mov bh,0 
    mov msg, offset Choose_the_mode
    call Write_Not_First_Line
    mov al, 0   ; default value in order to know that if changed so send this mode 
    checkMode:
    ; check receive: if you received anything so you have to receive the mode: jmp receiveMode
    mov dx, 3fdh
    in al, dx
  	AND al , 1
    jz fixReceiveMode
    jmp receiveMode
    fixReceiveMode:
    
    call getKeyMainScreen
    cmp al, 0
    jz checkMode
    sendMode:
    cmp al, 61h     ; check if 'a' key is pressed
    je ChatingGo
    cmp al, 62h     ; check if 'b' key is pressed
    je GameGo 
    cmp ah, 01h     ; check if ESC key is pressed
    jne fixMozaTwo
    call sendEndMainScreen
    mov ah,4ch
    int 21h
    fixMozaTwo:
    jmp checkMode
    ChatingGo:
    mov bh,0
    call clearScreen
    call clearNotifcationArea
    mov mainUser, 1 ; when I send so I'm the main user
    mov msg, offset chatInviteMsg
    call Write_Not_First_Line
    ; send chating mode
    mov dx , 3FDH		; Line Status Register
    AGAINMainScreen:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAINMainScreen
    mov dx, 3f8h
    mov al, 1   ; 1: chating, 2: game, 0: wrong
    out dx, al
    ; loop to wait to receive the other chosen mode if equal then jmp Chating if no so go again to startMainAgain
    mov dx, 3fdh
    waitReceive:
    in al, dx
  	AND al , 1
    jz waitReceive
    mov dx, 3f8h
    in al, dx
    cmp al, 3
    jnz contChatingGo
    mov ah,4ch
    int 21h  
    contChatingGo:
    cmp al, 0
    jz fixChating
    jmp Chating
    fixChating:
    jmp startMainAgain
    
    gameGo:
    mov bh,0
    call clearScreen
    call clearNotifcationArea 
    mov mainUser, 1 ; when I send so I'm the main user
    mov msg, offset gameInviteMsg
    call Write_Not_First_Line
    mov dx , 3FDH		; Line Status Register
    AGAINMainScreen1:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAINMainScreen1
    mov dx, 3f8h
    mov al, 2   ; 1: chating, 2: game, 0: wrong
    out dx, al
    ; loop to wait to receive the other chosen mode if equal then jmp Game if no so go again to startMainAgain
    mov dx, 3fdh
    waitReceive1:
    in al, dx
  	AND al , 1
    jz waitReceive1
    mov dx, 3f8h
    in al, dx
    cmp al, 3
    jnz contGameGo
    mov ah,4ch
    int 21h  
    contGameGo: 
    cmp al, 0
    jz fixGame
    jmp Game
    fixGame:
    jmp startMainAgain

    receiveMode:
    mov mainUser, 0 ; when I receive so I'm the main user
    ; receive the other chosen mode in bl
    mov dx, 3f8h
    in al, dx
    cmp al, 3
    jnz contReceiveMode
    mov ah,4ch
    int 21h   
    contReceiveMode:
    mov bl, al
    cmp bl, 2
    je gameInviteMain
    mov msg, offset chatInvitation
    call Write_Not_First_Line
    jmp checkMode2
    gameInviteMain:
    mov msg, offset gameInvitation
    call Write_Not_First_Line
    checkMode2:
    mov ah, 0       ; check what key is pressed
    int 16h           ; to be edited with interrupt that doesn't wait
    sendMode2:
    cmp al, 61h     ; check if 'a' key is pressed
    je ChatingGo2
    cmp al, 62h     ; check if 'b' key is pressed
    je GameGo2 
    cmp ah, 01h     ; check if ESC key is pressed
    jne fixMozaTwo2
    jmp end1
    fixMozaTwo2:
    jmp checkMode2
    ChatingGo2:
    mov bh,0
    call clearScreen
    call clearNotifcationArea
    ; check if the other was chating if yes send him chating mode to make him start it and jmp Chating if no so send him no and jmp startMainAgain
    cmp bl, 1   ; 1: chating, 2: game, 0: wrong
    jnz goStartMainAgain
    mov dx , 3FDH		; Line Status Register
    AGAINMainScreen5:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAINMainScreen5
    mov dx, 3f8h
    mov al, 1   ; 1: chating, 2: game, 0: wrong
    out dx, al
    jmp Chating
    goStartMainAgain:
    mov dx , 3FDH		; Line Status Register
    AGAINMainScreen4:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAINMainScreen4
    mov dx, 3f8h
    mov al, 0   ; 1: chating, 2: game, 0: wrong
    out dx, al
    jmp startMainAgain
    gameGo2:
    mov bh,0
    call clearScreen
    call clearNotifcationArea 
    ; check if the other was game if yes send him Game mode to make him start it and jmp Game if no so send him no jmp startMainAgain
    cmp bl, 2   ; 1: chating, 2: game, 0: wrong
    jnz goStartMainAgain
    mov dx , 3FDH		; Line Status Register
    AGAINMainScreen6:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAINMainScreen6
    mov dx, 3f8h
    mov al, 2   ; 1: chating, 2: game, 0: wrong
    out dx, al
    jmp Game
popf
pop dx
pop cx
pop bx
pop ax
ret
MainScreen endp 



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
    
    tryAgaingetScore:
    ;updating cursor position
    mov bh, 0
    mov yx, 0B0Ah
    call setCursor
    
    ;getting score from user 'keyboard input'
    mov input, offset firstInputScore
    call getInput    
    Num_Input firstInputScore, firstScore, parse_int
    cmp parse_int, 0
    jne fixHundred
    jmp tryAgaingetScore
    fixHundred: 
    
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
    call clearScreen
    ;initializing cursor position  
    mov bh,0 ;///////////IMPORTANT/////////// YOU HAVE TO SAY WHAT PAGE YOU WANT BEFORE SETCURSOR! #MOZAELSYA7
    mov yx, 020Ah
    call setCursor
    
    
    ;Request username 'print message'
    mov msg, offset usernameRequest
    call printMsg
    
    ;updating cursor position 
    mov bh,0
    mov yx, 030Ah
    call setCursor
    
    ;getting username from user 'keyboard input'
    mov input, offset secondUsername
    call getInput     
    
    ;Score Part ////////////////////////
    
    ;updating cursor position  
    mov bh,0
    mov yx, 0A0Ah
    call setCursor

    ;Request score 'print message' 
    mov msg, offset scoreRequest
    call printMsg
    
    tryAgain2getScore:
    ;updating cursor position 
    mov bh,0
    mov yx, 0B0Ah
    call setCursor
    
    ;getting score from user 'keyboard input'
    mov input, offset secondInputScore
    call getInput    
    Num_Input secondInputScore, secondScore, parse_int
    cmp parse_int, 0
    jne fixHundredOne
    jmp tryAgain2getScore
    fixHundredOne:

    ;updating cursor position 
    mov bh,0
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

getKeyMainScreen proc near
    mov ah, 01H
    int 16H
    jnz keybdpressedMainScreen   
    mov al, 0
    ret
keybdpressedMainScreen:
    ;extract the keystroke from the buffer
    mov ah, 00H
    int 16H
ret
getKeyMainScreen endp


sendEndMainScreen proc near
    mov dx , 3FDH		; Line Status Register
    againSendEndMainScreen:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ againSendEndMainScreen
    
    mov dx, 3f8h
    mov al,3
    out dx,al
ret
sendEndMainScreen endp
