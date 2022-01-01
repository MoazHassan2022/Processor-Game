.MODEL LARGE
.STACK 64
.286
.DATA    
;get info vars
usernameRequest db 'Please enter your username:','$'
scoreRequest db 'Enter your initial score:','$' 
enterMsg db 'Press Enter key to continue', '$'
;end of get info vars

; main screen vars
startChating db 'To start chating press F2','$'
startGame db 'To start the game press F3','$'
endProgram db 'To end the program press ESC','$'
firstUsername db 15,?,15 dup('$') 
firstInputScore db 4,?,4 dup('$')
firstScore dw 5
secondUsername db 15,?,15 dup('$') 
secondInputScore db 4,?,4 dup('$')
secondScore dw 5  
Choose_the_mode db 'choose the mode','$'
firstMode db ?                          
chatInvitation db 'You are invited to chat, if you accept press F2','$'
gameInvitation db 'You are invited to the game, if you accept press F3','$'
Firstcountname db 9
secondcountname db 6

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

; the vars in the proc decide level
InvalidMsg db "The Number is invalid enter only 1 or 2...$"
LevelMsg   db "Enter the Number of the level 1 or 2 ...",10,13," and if You want to return to the main screen press Enter  ...$"    
Forbidden db 10,13,"Enter the forbidden char $" 
InvalidMsgForbidden db "Enter a valid char $"  
Levelnum db "2"
ForbiddenChar1 db "A" 
count db 0  
count2 db 0 

;vars to draw the page
verticalend dw ?
horizotalpostion dw ?  
colnum dw ?   
endrow dw ? 
startrow dw 0 
verticalstart dw 0
;vars of memory cells
Memo1 db "00010203040506070809101112131415"
Memo2 db "00000000000000000000000000000000"  
Memotemp db ?
memosize db 16       
countmemo db 2
memolocation db ?
memolocationvalue db '03' 
scoreintialization db "Score"
;vars of registers
regInitialvalue db '0000','$'
regSize db 4
registerscount db 4 
RegsPosition db ? 
regnum db ?  
tempregname db "AXSICXDIBXSPDXBP" 
regvalues db "1101"
regposition dw ?
shift db ?   
;inline chat
inlineFirstOneTalk dw ?
arrive_max_message db "you are exceeded the max leght of the massage $"

; end of cahtting vars
StringMsg db ?

;game vars                                               
;arrive_max_message db "max number of char is 17 bro","$"

Instructions_array DB 'NOP ADD ADC SUB SBB MOV XOR AND OR SHR SHL SAR ROR RCL RCR ROL'
general_reg_array DB 'AL AH BL BH CL CH DL DH AX BX CX DX'
other_reg_array DB 'SI DI SP BP'
command db 19,?,19    DUP(' ') ; the total command input
OP DW ?         ; OP pointer to the operand which will make operation on
POS Dw -1       ; var used for and search opreation


user db 1
;for memory check
memory_num dw 0   ; number of the memory that access to 
first_half_str db 5,?,5  DUP("$")       ; first half in memory in operand
second_half_str db 5,?,5  DUP("$")      ; second half in memory in operand
temp_number dw ?                        ; number that used to convert string number to actual number
Number_op dw ?                          ; if the operand is directly number

; FOR CHECK THE TYPE OF OPERAND
first_in_op db ?   ; its used to detect type of op is number or reg
detectType db 0    ; if its number it will be 1, if its reg will be 0


;forbiddenChar1 db ?
forbiddenChar2 db ?

;////////////// instruction vars
instructionSTR db 6,?,6  DUP('$') ; instruction as string
command_code db ?              ; instruction final code
;//////////// operrand1 vars
operand1 db 12,?,12  DUP(' ')  ; operand1 text
op1_type db ?                  ; type of operand1
op1_value_code dw ?            ; value of operand1
                            
;//////////// operrand2 vars
operand2 db 12,?,12  DUP(' ')  ; operand2 text
op2_type db ?                  ; type of operand1
op2_value_code dw ?            ; value of operand1
 
instruction1 db ?              ; type of op1, type of op2 , command
first_op1 dw ?
first_op2 dw ?

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

instruction db ?   ; instruction1: lower half byte: the instruction1 itself, higher half byte: type of operand 1 (2 bits), type of op2(2bits)
op1 dw ?        ; decide register or the memory location
op2 dw ?        ; decide register or the memory location 
 
RegistersArray db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ; al, ah, bl, bh, cl, ch, dl, dh, SIL, SIH, DIL, DIH, SPL, SPH, BPL, BPH    
MyMemoryArray db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ;      
carryFlag db 1
RegistersArray2 db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ; al, ah, bl, bh, cl, ch, dl, dh, SIL, SIH, DIL, DIH, SPL, SPH, BPL, BPH    
MyMemoryArray2 db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh ;      
carryFlag2 db 1
Done db 'Done!', '$'

powerUp1 db ? ; current power up used by first player (0: no power up used, 1: executing command on first player processor, 2: Executing a command on both processors, 3: changing forbiddenChar1, 4: clearing all registers)
powerUp2 db ? ; current power up used by second player (0: no power up used, 1: executing command on second player processor, 2: Executing a command on both processors, 3: changing forbiddenChar2, 4: clearing all registers)


hexaString db 5,?,5 dup('$') 
hexaNum dw ?   
scoreString db 4 dup('$') ; string to display the score of first or second player( maximum 3 digits ) 

WinMsg db 'Winner  : ', '$' ; message to be shown when winner is  
congratsMsg db 'Congratulations!', '$' 
abortedMsg db 'Game is aborted suddenly ...', '$'
withScoreMsg db '  With Score  :  ', '$'  
WrongCommandMsg db 'This is Wrong Command!', '$'

ForbiddenCharMsg db 'Forbidden char', '$'

.CODE
include Chat.inc      
include general.inc
include MainScrn.inc
include convert.inc   ; These macros must be included before code
include GameM.inc
include game.inc
include Execute.inc


Main proc far
    mov ax, @DATA
    mov ds, ax  

    ;call clearScreen 
    
    ;call Get_Info
    
    main_Screen: 
    ;call MainScreen 
    Chating:
        
     ;   call ChatMode
        
      ;  call firstOneWrite
        
       ; call SecondOneWrite
                
    Game:
        mov msg, offset startGame
        call printMsg
        
        DecideLevel
        ForbiddenChar

        DrawGame
        
        
        mov user, 1
        labelHoba:  
        call receiveInstruction
        ;call ExecuteWithPower1
           
        
    end1:
                      
    mov ah,4ch
    int 21h    
main endp


      


end main                        

            

; set cursor postion setCursor  to var( yx )                                     ----> setCursor
; print msg in var( yx ) with msg in var ( msg )                                 ----> printMsgAtyx
; print msg in current cursor postion with msg in var ( msg )                    ----> printMsg 
; get the input and put it in var( input )                                       ----> getInput
; chage between pages with the value in al                                       ----> changePage
; clean the screen except the notification area                                  ----> clearScreen
; Draw horizontal line at var ( yx )                                             ----> Draw_H_Line
; Clear Notification Area                                                        ----> clearNotifcationArea
; recive number and convert it from user                                         ----> Num_Input
; write in first line in notification area with msg in var( msg )                ----> Write_Not_First_Line
; write in seconline in notification area with sg in var( msg )                  ----> Write_Not_Second_Line
; Clear first line in Notifiction area                                           ----> clearNotFirst
; Clear Second line in Notifiction area                                          ----> clearNotSecond

