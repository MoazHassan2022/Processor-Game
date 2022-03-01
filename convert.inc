ConvertStrHexa macro hexaString, hexaNum ; macro to convert hexa string to hexa number
LOCAL oneH, twoH, threeH, fourH, itsOneDec, itsOneDec2, secondChar2, itsTwoDec2, fixMozaFour, getSize, outGetSize, zeroH
LOCAL secondChar3, thirdChar3, itsOneDec3, itsTwoDec3, itsThreeDec3, secondChar4, thirdChar4, fourthChar4, itsOneDec4, itsTwoDec4, itsThreeDec4, itsFourDec4, exitConvertStrHexa
push ax
push bx
push cx
push dx
pushf
mov ah, 0
mov al, hexaString + 2 ; get first char
mov dl, 0 
mov si, 2
getSize:
cmp hexaString[si], '$'
jz outGetSize      
inc si
inc dl
jmp getSize
outGetSize:
mov bx, 0 ; We will store the result ( 2 bytes ) in dx then in hexaNum
cmp dl, 0
je zeroH
cmp dl, 1 ; 1 digit
je oneH 
cmp dl, 2 ; 2 digits
je twoH 
cmp dl, 3 ; 3 digits
je threeH
cmp dl, 4 ; 4 digits
jne fixMozaFour
jmp fourH 
fixMozaFour:                   
;///////////// Zero////////////
zeroH:
mov dx, 0
jmp exitConvertStrHexa
;////////////// One Digit ///////////////
oneH:
cmp al, '9'
jbe itsOneDec ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  ; if > 9 we can convert to hexa with subtracting 37h
MOV BL, al
jmp exitConvertStrHexa
itsOneDec:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
add bl, al
jmp exitConvertStrHexa
;////////////// Two Digits ///////////////
twoH:
cmp al, '9'
jbe itsOneDec2 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  ; if > 9 we can convert to hexa with subtracting 37h
mov cl, 10h  
mul cl       ; make it in the second digit
add bl, al

secondChar2:   
mov ah, 0
mov al, hexaString + 3 ; get second char
cmp al, '9'
jbe itsTwoDec2 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  ; if > 9 we can convert to hexa with subtracting 37h
add bl, al
jmp exitConvertStrHexa
itsOneDec2:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
mov cl, 10h
mul cl ; make it in the second digit
add bl, al
jmp secondChar2
itsTwoDec2:
sub al, 30h
add bl, al
jmp exitConvertStrHexa  
;//////////// Three Digits ////////////
threeH:
cmp al, '9'
jbe itsOneDec3 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  ; if > 9 we can convert to hexa with subtracting 37h
mov cx, 100h  
mul cx       ; make it in the third digit
add bx, ax

secondChar3:   
mov ah, 0
mov al, hexaString + 3 ; get second char
cmp al, '9'
jbe itsTwoDec3 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  ; if > 9 we can convert to hexa with subtracting 37h
mov cl, 10h
mul cl
add bl, al 

thirdChar3:
mov ah, 0
mov al, hexaString + 4 ; get third char
cmp al, '9'
jbe itsThreeDec3 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h
add bl, al
jmp exitConvertStrHexa
itsOneDec3:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
mov cx, 100h
mul cx ; make it in the third digit
add bx, ax
jmp secondChar3
itsTwoDec3:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
mov cl, 10h ; make it in the second digit
mul cl
add bl, al
jmp thirdChar3
itsThreeDec3:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
add bl, al
jmp exitConvertStrHexa 
;//////////// Four Digits ////////////
fourH:
cmp al, '9'
jbe itsOneDec4 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  ; if > 9 we can convert to hexa with subtracting 37h
mov cx, 1000h  
mul cx       ; make it in the fourth digit
add bx, ax

secondChar4:   
mov ah, 0
mov al, hexaString + 3 ; get second char
cmp al, '9'
jbe itsTwoDec4 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  ; if > 9 we can convert to hexa with subtracting 37h
mov cx, 100h ; make it in the third digit
mul cx
add bx, ax 

thirdChar4:
mov ah, 0
mov al, hexaString + 4 ; get third char
cmp al, '9'
jbe itsThreeDec4 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h  
mov cl, 10h       ; make it in the second digit
mul cl
add bl, al 

fourthChar4: 
mov ah, 0
mov al, hexaString + 5 ; get fourth char
cmp al, '9'
jbe itsFourDec4 ; if <= 9 then deal with it as decimal. else --> hexa digit
sub al, 37h
add bl, al 
jmp exitConvertStrHexa

itsOneDec4:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
mov cx, 1000h
mul cx ; make it in the fourth digit
add bx, ax
jmp secondChar4
itsTwoDec4:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
mov cx, 100h ; make it in the third digit
mul cx
add bx, ax
jmp thirdChar4
itsThreeDec4:
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
mov cl, 10h
mul cl      ; make it in the second digit
add bl, al
jmp fourthChar4                               
itsFourDec4: 
sub al, 30h ; if <= 9 we can convert to decimal with subtracting 30h
add bl, al

exitConvertStrHexa:
mov hexaNum, bx
popf
pop dx
pop cx
pop bx
pop ax
Endm convertStrHexa
ConvertDecString macro decimal, string   
    LOCAL twoDigits, threeDigits, exitConvertDecString, loopEmptyString
    push ax
push bx
push cx
push dx
    pushf         
	mov string[0], '$' 
	mov string[1], '$'  
	mov string[2], '$'  
	mov string[3], '$'  
    mov ax, decimal ; get the number ( MAXIMUM 3 DIGITS )
    cmp ax, 99  ; if larger then it's 3 digits
    ja threeDigits                              
    cmp ax, 9 ; if larger then it's 2 digits
    ja twoDigits ; else it's 1 digit
    add al, 30h  ; convert to char
    mov string, al 
    jmp exitConvertDecString ; Finished 
    
    twoDigits:
    mov bl, 10
    div bl        ; ah = lower digit, al = higher digit
    add al, 30h   ; convert to char
    mov string, al ; higher char (digit)
    add ah, 30h   ; convert to char
    mov string + 1, ah ; lower char (digit)
    jmp exitConvertDecString 
    
    threeDigits:
    mov bl, 10
    div bl        ; ah = lower digit, al = higher 2 digits 
    add ah, 30h   ; lower digit
    mov string + 2, ah 
    mov ah, 0  
    div bl        ; ah = lower digit, al = higher digit
    add al, 30h   ; convert to char
    mov string, al ; higher char (digit)
    add ah, 30h   ; convert to char
    mov string + 1, ah ; lower char (digit) 
    
    exitConvertDecString:
    popf
    pop dx
pop cx
pop bx
pop ax
endm ConvertDecString

EndGame macro winnerUsername, winnerScore ; //////// This is a MACRO to end the game and return to main screen /////////
    LOCAL noWinner, doneEndGame, fixNoWinner, suddenlyDontSend
	cmp al, 1
	jz suddenlyDontSend
	push ax
	call sendCommand
	pop ax
	suddenlyDontSend:
    mov bl, al ; Get whether the game is ended normally or no: al = 0 normal, al = 1 suddenly 

	mov al, 0
	call changePage     ; Activate page number 2 to show in
	call clearScreen

    mov bh, 0  
	mov yx, 0822h   
	call setCursor      ; Set cursor to be at the middle of the screen
	
	cmp bl, 1 ; This means that game is aborted suddenly: no winner
	jne fixNoWinner
	jmp noWinner
	fixNoWinner:
	mov msg, offset WinMsg ; There is a winner! 
	call printMsg
	mov bh, 0  
	mov yx, 0A22h   
	call setCursor
	mov msg, offset winnerUsername + 2 ; Show Winner username
	call printMsg
	
	ConvertDecString winnerScore, scoreString
	mov bh, 0  
	mov yx, 0C20h   
	call setCursor
	mov msg, offset withScoreMsg ; Show Winner score
	call printMsg 
	
	mov msg, offset scoreString ; Show Winner score
	call printMsg
	
	mov bh, 0  
	mov yx, 0E22h   
	call setCursor
	mov msg, offset congratsMsg  ; Congratulations!
	call printMsg
	jmp doneEndGame
	
	noWinner:
	mov bh, 0  
	mov yx, 0918h   
	call setCursor
	mov msg, offset abortedMsg ; Show aborted
	call printMsg
	mov bh, 0  
	mov yx, 0B18h   
	call setCursor
	mov msg, offset firstUsername + 2 ; Show first player username
	call printMsg
	
	ConvertDecString firstScore, scoreString
	mov bh, 0  
	mov yx, 0C18h   
	call setCursor
	mov msg, offset withScoreMsg 
	call printMsg 
	
	mov msg, offset scoreString ; Show first player score
	call printMsg
	mov bh, 0  
	mov yx, 0D18h   
	call setCursor
	mov msg, offset secondUsername + 2 ; Show second player username
	call printMsg
	
	ConvertDecString secondScore, scoreString
	mov bh, 0  
	mov yx, 0E18h   
	call setCursor
	mov msg, offset withScoreMsg 
	call printMsg 
	
	mov msg, offset scoreString ; Show second player score
	call printMsg
	
	doneEndGame:
	call delay

	mov bh, 0       ; return to Main Screen Mode
	call clearScreen 
	jmp main_Screen
endm endGame