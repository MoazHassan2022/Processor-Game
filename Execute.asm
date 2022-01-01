; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

.model small
.stack
.data  

;get info vars
usernameRequest db 'Please enter your username:','$'
scoreRequest db 'Enter your initial score:','$' 
enter db 'Press Enter key to continue', '$'
;end of get info vars

; main screen vars
startChating db 'To start chating press F2','$'
startGame db 'To start the game press F3','$'
endProgram db 'To end the program press ESC','$'
firstUsername db 15,?,15 dup('$') 
firstInputScore db 4,?,4 dup('$')
firstScore dw 4
secondUsername db 15,?,15 dup('$') 
secondInputScore db 4,?,4 dup('$')
secondScore dw 0  
Choose_the_mode db 'choose the mode','$'
firstMode db ?                          
chatInvitation db 'You are invited to chat, if you accept press F2','$'
gameInvitation db 'You are invited to the game, if you accept press F3','$'

;end of main screen vars

; general vars
yx dw ?  ; currrent positin of cursor
msg dw ?
input dw ?
; end of general vars
 
; cahtting vars
ChangeControlMsg db 'if you end you talk click Tab $'
EndChatMode db 'if your want to end the chat press F3 $'
WriteSomeTing db 'Wirte some thing to other man'      
FirstOneTalk dw 0204h
SecondOneTalk dw 0C04h
; end of cahtting vars 

instruction db ?   ; instruction1: lower half byte: the instruction1 itself, higher half byte: type of operand 1 (2 bits), type of op2(2bits)
instruction2 db ?   ; instruction1: lower half byte: the instruction1 itself, higher half byte: type of operand 1 (2 bits), type of op2(2bits)
op1 dw ?        ; decide register or the memory location
op2 dw ?        ; decide register or the memory location 
secondOp1 dw ?        ; decide register or the memory location
secondOp2 dw ?        ; decide register or the memory location 
RegistersArray db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ; al, ah, bl, bh, cl, ch, dl, dh, SIL, SIH, DIL, DIH, SPL, SPH, BPL, BPH    
MyMemoryArray db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ;      
carryFlag db 1
RegistersArray2 db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ; al, ah, bl, bh, cl, ch, dl, dh, SIL, SIH, DIL, DIH, SPL, SPH, BPL, BPH    
MyMemoryArray2 db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ;      
carryFlag2 db 1
WrongCommandMsg db 'Wrong Command!', '$' 
Done db 'Done!', '$'

powerUp1 db 0 ; current power up used by first player (0: no power up used, 1: executing command on first player processor, 2: Executing a command on both processors, 3: changing forbiddenChar1, 4: clearing all registers)
powerUp2 db 0 ; current power up used by second player (0: no power up used, 1: executing command on second player processor, 2: Executing a command on both processors, 3: changing forbiddenChar2, 4: clearing all registers)

forbiddenChar1 db 'G' ; forbidden character for first player
forbiddenChar2 db 'M' ; forbidden character for second player

hexaString db 5,?,5 dup('$') 
hexaNum dw ?   
scoreString db 4 dup('$') ; string to display the score of first or second player( maximum 3 digits ) 

WinMsg db 'Winner  : ', '$' ; message to be shown when winner is  
congratsMsg db 'Congratulations!', '$' 
abortedMsg db 'Game is aborted suddenly ...', '$'
withScoreMsg db '  With Score  :  ', '$'  

include convertAndOthers.inc   ; These macros must be included before code


.code   
MAIN        PROC FAR 
	mov ax,@data                               
	mov ds,ax         
	
	executeAgain:  
	mov bh, 0
	mov ah, 07
	int 21h   
	cmp al, '2'
	je ExecuteGeneralTwo 
	mov bh, 0
	mov ah, 07
	int 21h
	cmp al, '1'
	je commandTwoMoza  
	mov instruction, 00010101B
	mov op1, 0009h 
	mov op2, 0003h
	mov ah, 0
	call ExecuteGeneral 
	jmp executeAgain
	
	commandTwoMoza: 
	mov instruction, 10110001B
	mov op1, 000fh
	mov op2, 00f0h
	mov ah, 0 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral  
	jmp executeAgain
	
	ExecuteGeneralTwo:
    mov bh, 0
	mov ah, 07
	int 21h
	cmp al, '1'
	je commandTwoMoza2  
	mov instruction2, 01000111B
	mov secondOp1, 0000h
	mov secondOp2, 0008h
	mov ah, 1
	call ExecuteGeneral 
	jmp executeAgain
	
	commandTwoMoza2: 
	mov instruction2, 10110111B
	mov secondOp1, 000eh
	mov secondOp2, 00f0h
	mov ah, 1 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral  
	
	jmp executeAgain
	
	     
	mov ah , 4ch 
	int 21h
MAIN                ENDP
include Execute.inc

end main


