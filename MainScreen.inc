;/////////////////
;get info from users
Get_Info proc near
    pusha
    pushf
	;First User part ////////////////////// 
    
    call firstUser
    
    ;Request continue 'print message' 
    mov msg, offset enter
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
    mov yx, 1500h
    call Draw_H_Line ; get the notification bar ready in second page

    popf
    popa
    ret
endp


;//////////////////////
; get user mode choose

MainScreen proc  near
pusha
pushf

;//////////////MAIN SCREEN///////////////
    ;welcoming the user
    mov msg, offset welcomeUser
    call Write_Not_First_Line
    mov msg, offset firstUsername+2
    call Concatinate_Not
    
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
    mov msg, offset Choose_the_mode
    call Write_Not_Second_Line
    
    mov ah, 0       ; check what key is pressed
    int 16h
    mov bh,0
    call clearScreen
    call clearNotifcationArea
    
    cmp ah, 3ch     ; check if F2 key is pressed
    je Chating 
    cmp ah, 3dh     ; check if F3 key is pressed
    je Game 
    cmp ah, 01h     ; check if ESC key is pressed
    je end1

popf
popa
ret
endp


;/////////////////////////////////
; recive first user data
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
    
    tryAgain:
    ;updating cursor position
    mov yx, 0B0Ah
    call setCursor
    
    ;getting score from user 'keyboard input'
    mov input, offset firstInputScore
    call getInput    
    Num_Input firstInputScore, firstScore, parse_int
    cmp parse_int, 0
    je tryAgain 
    
    ;updating cursor position
    mov yx, 0E0Ah
    call setCursor

    popf
    popa
    ret
endp
;/////////////////////////////////
; recive second user data
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
    
    tryAgain2:
    ;updating cursor position 
    mov bh,01
    mov yx, 0B0Ah
    call setCursor
    
    ;getting score from user 'keyboard input'
    mov input, offset secondInputScore
    call getInput    
    Num_Input secondInputScore, secondScore, parse_int
    cmp parse_int, 0
    je tryAgain2
    
    ;updating cursor position 
    mov bh,01
    mov yx, 0E0Ah
    call setCursor

    popf
    popa
    ret
endp
;///////////////////////////////////////


