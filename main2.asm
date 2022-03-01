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
startChating db 'To start chating press A','$'
startGame db 'To start the game press B','$'
endProgram db 'To end the program press ESC','$'
firstUsername db 15,?,15 dup('$') 
firstInputScore db 4,?,4 dup('$')
firstScore dw 0
secondUsername db 15,?,15 dup('$') 
secondInputScore db 4,?,4 dup('$')
secondScore dw 0
parse_int db 0
Choose_the_mode db 'choose the mode','$'
firstMode db ?                          
chatInvitation db 'You are invited to chat, if you accept press A','$'
gameInvitation db 'You are invited to the game, if you accept press B','$'
chatInviteMsg db 'You invited him to chat, please wait....','$'
gameInviteMsg db 'You are invited to the game, please wait....','$'
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
LevelMsg   db "Enter the Number of the level 1 or 2 ...",10,13," $"    
Forbidden db 10,13,"Enter the forbidden char $" 
InvalidMsgForbidden db "Enter a valid char $"  
Levelnum db ?
ForbiddenChar1 db ? 
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
regvalues db "1011"
regposition dw ?
shift db ?   
;inline chat
inlineFirstOneTalk dw ?
arrive_max_message db "Arrived Max length$"


;game vars                                               
;arrive_max_message db "max number of char is 17 bro","$"

Instructions_array DB 'NOP ADD ADC SUB SBB MOV OR  AND XOR SHR SHL SAR ROR RCL RCR ROL'
general_reg_array DB 'AL AH BL BH CL CH DL DH AX BX CX DX'
other_reg_array DB 'SI DI SP BP'
command db 45 DUP('$') ; the total command input
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
operand2 db 12,?, 12 DUP('$')  ; operand2 text
op2_type db ?                  ; type of operand1
op2_value_code dw ?            ; value of operand1
 
instruction1 db ?              ; type of op1, type of op2 , command
first_op1 dw ?
first_op2 dw ?

isCommandValid db 1  ; 0: command is invalid, 1: command is valid

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

instruction db ?   ; instruction1: lower half byte: the instruction1 itself, higher half byte: type of operand 1 (2 bits), type of op2(2bits)
op1 dw ?        ; decide register or the memory location
op2 dw ?        ; decide register or the memory location 
 
RegistersArray db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h ; al, ah, bl, bh, cl, ch, dl, dh, SIL, SIH, DIL, DIH, SPL, SPH, BPL, BPH    
MyMemoryArray db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h ;      
carryFlag db 0
RegistersArray2 db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h ; al, ah, bl, bh, cl, ch, dl, dh, SIL, SIH, DIL, DIH, SPL, SPH, BPL, BPH    
MyMemoryArray2 db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h ;      
carryFlag2 db 0
Done db 'Done!', '$'

powerUp1 db 0 ; current power up used by first player (0: no power up used, 1: executing command on first player processor, 2: Executing a command on both processors, 3: changing forbiddenChar1, 4: clearing all registers)
powerUp2 db 0 ; current power up used by second player (0: no power up used, 1: executing command on second player processor, 2: Executing a command on both processors, 3: changing forbiddenChar2, 4: clearing all registers)


hexaString db 5,?,5 dup('$') 
hexaNum dw ? 
hexaNum2 dw ?   
scoreString db 4 dup('$') ; string to display the score of first or second player( maximum 3 digits ) 

WinMsg db 'Winner  : ', '$' ; message to be shown when winner is  
congratsMsg db 'Congratulations!', '$' 
abortedMsg db 'Game is aborted suddenly ...', '$'
withScoreMsg db '  With Score  :  ', '$'  
WrongCommandMsg db 'This is Wrong Command!', '$'

ForbiddenCharMsg db 'Forbidden char', '$'
hexaStr db 3,?, 3 dup('$')
enterPower db 'Enter Your Power Up', '$'

emptyString db 28 dup(' '), '$'

enterCommand db 'Enter your command', '$'
enterForbidden db 'Enter new forbiddem char', '$'
invalidForbiddenMsg db 'Invalid char, Enter again', '$'
clearUsedMsg db 'This power up is used', '$'
isClearUsed1 db 0
isClearUsed2 db 0
isForbiddenUsed1 db 0
isForbiddenUsed2 db 0
isTargetUsed1 db 0
isTargetUsed2 db 0

lessScoreMsg db 'Not enough score', '$'
notPoweUp db 'Power up not found', '$'
Level2ReceiveMsg db 'Decide proccessor: 1, 2', '$'
x db 0
y db 180

x2 db 180
y2 db 180

center dw 15
center2 dw 195
tempScore dw 5
valinCircle dw 6
key db ?
ballTimes dw 0
colorArr db 01h, 02h, 03h, 04h, 05, 06h
ptsArr db 1h, 2h, 3h, 4h, 5h, 6h
; end of cahtting vars
level2Decision db ?
;//////////////level 2 vars
pleaseInitializeRegs db 'Please enter regs initial value in format: 000F','$'
waitMsg db 'Please wait few seconds....', '$'
targetValue dw 105eh
mainUser db 0

write_msg db "write your msg"," :","$"  
ReceivingMsg db 'Wait for other user...', '$'
writing_inductor dw ?
printing_inductor dw ?
cur_sender dw ?
next_sender dw ?
whichUser db ?
executeReceivedCommand db ?
variable db 38h
flyBIndex db 0
StringMsg db 236,?,236 dup(' ')
ReceivedMsg db 236,?,236 dup(' ')

;//// inline chat vars
inlineChatindicator dw ?
startofinlinechat db ?
printinlinechatindicator dw ?

.CODE
include Chat.inc      
include general.inc
include MainScrn.inc
include convert.inc   ; These macros must be included before code
include GameM.inc
include game.inc
include Execute.inc
include flyB.inc
INCLUDE inlineC.inc

Main proc far
    mov ax, @DATA
    mov ds, ax  
    call uart

    call clearScreen 
    mov dx , 3FDH		; Line Status Register	
    in al , dx 
	AND al , 1
    jnz MakeMeSecond
    mov whichUser, 1
    mov dx, 3f8h
    mov al, '`'
    out dx, al ; once you opened send to him to decide that he is the second

    mov al, 1
    call Get_Info
    jmp main_Screen
    MakeMeSecond:
    mov whichUser, 2
    mov al, 2
    call Get_Info
    
    main_Screen: 
    call MainScreen 
    jmp end1
    Chating:
        
        call start_chat
        jmp main_Screen 
                
    Game:
    ;the decide level will check if the user is main or not if he is main user he will decide the level and then will send the level to the second user 
    ;in the same function but if the user is second user he will receive the level only
    cmp mainuser,1
    jnz secondwillreceive
    DecideLevel
    jmp checkWhichLevel
    secondwillreceive:
    call clearScreen
    mov yx, 0B0Dh
    call setCursor
    mov msg, offset waitMsg
    call printMsg
    ;function to recive the level from the first user
    receivethelevelnumfromthefirstuser Levelnum
    call clearScreen
    checkWhichLevel:
    cmp levelnum, 31h
    jnz fixItsLevelOne
    jmp itsLevelOne
    fixItsLevelOne:
    ;After deciding the level will take the initial value from the users
    ;i will make the first user send first and then the second user
    cmp mainuser,1
    jz fixseconduserwillreceivetheinitial
    jmp seconduserwillreceivetheinitial
    fixseconduserwillreceivetheinitial:
    call GetInitialValuesToRegs
    ;loop to send the string of the initial value
    mov si,2
    sendLoopFirstUserinitialvalue:
    cmp si, 6
    jz outsendLoopFirstUserinitialvalue
    AGAIN28:  
    mov dx , 3FDH		; Line Status Register	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
    jz AGAIN28
    
    mov al, hexaString[si]
    mov dx, 3f8h
    out dx, al
    inc si
    jmp sendLoopFirstUserinitialvalue
    outsendLoopFirstUserinitialvalue:
    call clearScreen
    ConvertStrHexa hexaString, hexanum
    ; loop to recive the intial value from the second user
    ;After receiving will convert the hexastring to the hexanum2
    call clearScreen
    mov yx, 0B0Dh
    call setCursor
    mov msg, offset waitMsg
    call printMsg
    mov si,2
    LoopFirstUsertoreceivethesecondintial:
    cmp si, 6
    jz outLoopFirstUsertoreceivethesecondintial
    AGAIN29:  
    mov dx , 3FDH		; Line Status Register	
    In al , dx 			;Read Line Status
  	AND al , 00000001b
    jz AGAIN29
    
    mov dx, 3f8h
    in al,dx
    mov hexaString[si],al
    inc si
    jmp LoopFirstUsertoreceivethesecondintial
    outLoopFirstUsertoreceivethesecondintial:
    call clearScreen
    ConvertStrHexa hexaString, hexanum2
    ;After that will jmp to recive the forbidden char
    jmp thefirstsent
    seconduserwillreceivetheinitial:
    call clearScreen
    mov yx, 0B0Dh
    call setCursor
    mov msg, offset waitMsg
    call printMsg
    ;the second user will receive from the first user the initial value
    mov si,2
    LoopSecondUsertoreceivethesecondintial:
    cmp si, 6
    jz outLoopSecondUsertoreceivethesecondintial
    AGAIN30:  	
    mov dx,3fdh
    in al,dx
    And al,1
    jz AGAIN30
    
    mov dx, 3f8h
    in al,dx
    mov hexaString[si],al
    inc si
    jmp LoopSecondUsertoreceivethesecondintial
    outLoopSecondUsertoreceivethesecondintial:
    call clearScreen
    ConvertStrHexa hexaString, hexanum
    ;then the second user will put the  forbidden and then send it to the first user
    call GetInitialValuesToRegs
    mov si,2
    sendLoopSecondUserinitialvalue:
    cmp si, 6
    jz outsendLoopSecondUserinitialvalue
    mov dx , 3FDH		; Line Status Register
    AGAIN31:  	
    In al , dx 			;Read Line Status
  	AND al , 00100000b
    jz AGAIN31
    
    mov al, hexaString[si]
    mov dx, 3f8h
    out dx, al
    inc si
    jmp sendLoopSecondUserinitialvalue
    outsendLoopSecondUserinitialvalue:
    ConvertStrHexa hexaString, hexanum2
    itsLevelOne:
    thefirstsent:
    ;receive the forbidden char
    cmp whichUser,1
    jz fixtheseconduserwillputtheFobidden
    jmp theseconduserwillputtheFobidden
    fixtheseconduserwillputtheFobidden:
    mov bl, 1
    ForbiddenChar
    checktheforbidden2tosendit50:
    mov dx,3fDh
    In al , dx 			
    AND al , 00100000b
    jz checktheforbidden2tosendit50
    mov al,ForbiddenChar2
    mov dx, 3f8h
    out dx,al
    call clearScreen
    mov yx, 0B0Dh
    call setCursor
    mov msg, offset waitMsg
    call printMsg
    ;recieve the second user forbidden
    receivethelevelnumfromthefirstuser forbiddenChar1
    call clearScreen
    jmp testLevel
    theseconduserwillputtheFobidden:
    call clearScreen
    mov yx, 0B0Dh
    call setCursor
    mov msg, offset waitMsg
    call printMsg
    receivethelevelnumfromthefirstuser forbiddenChar2
    call clearScreen
    mov bl, 2
    ForbiddenChar

    checktheforbidden1tosendit:
    mov dx, 3fdh
    In al , dx 			
    AND al , 00100000b
    jz checktheforbidden1tosendit
    mov al,ForbiddenChar1
    mov dx, 3f8h
    out dx,al
    ;end of receiving the forbidden char
    testLevel:
    call clearScreen
    

    LabelDrawGame:
    mov startrow, 0  
    mov memosize, 16
    mov verticalstart, 0
    mov regsize, 4
    mov countmemo, 2
    call DrawGame
    mov user, 1
    cmp levelnum, '2'
    jnz fixDiscussion
    jmp secondLevelGame
    fixDiscussion:
    ;call gameStartProc
    gameLoop:
    mov dl, user
    cmp whichUser, dl
    jnz callReceiveCommand
    mov isCommandValid, 1
    call receiveInstruction
    cmp isCommandValid, 0 ; if yes then command is invalid(reload)
    jnz validCommandFirst
    jmp gameLoop
    validCommandFirst:
    call ExecuteTotal
    inc flyBIndex
    cmp flyBIndex, 2       ;Number of times before Flying Ball execution
    jnz fixexecuteFlyingBall
    jmp executeFlyingBall
    fixexecuteFlyingBall:
    jmp gameLoop

    callReceiveCommand:
    call receiveCommand
    cmp executeReceivedCommand, 1
    jnz toggleAndGameLoop
    cmp user, 1
    jnz secondExecute1
    call ExecuteWithPower1
    inc flyBIndex
    cmp flyBIndex, 2       ;Number of times before Flying Ball execution
    jnz gameLoop
    jmp executeFlyingBall
    secondExecute1:
    call ExecuteWithPower2
    inc flyBIndex
    cmp flyBIndex, 2       ;Number of times before Flying Ball execution
    jz executeFlyingBall
    jmp gameLoop
    toggleAndGameLoop:
    xor user, 00000011b
    inc flyBIndex
    cmp flyBIndex, 2       ;Number of times before Flying Ball execution
    jz executeFlyingBall
    jmp gameLoop
    
    
    secondLevelGame:
    ;call secondLevelGameProc
    labelhoba132:
     mov bx, 0
     mov user, 2
     drawFirstRegisters120:
     mov dx, hexanum
     mov RegistersArray[bx], dl
     call regType
    call converttostring
    call Regvalue
     inc bx
    mov RegistersArray[bx], dh
    call regType
    call converttostring
    call Regvalue 
    inc bx
    cmp bx, 16
    jne drawFirstRegisters120
    mov user, 1
    mov bx, 0
    drawFirstRegisters121:
     mov dx, hexanum2
     mov RegistersArray2[bx], dl
     call regType
    call converttostring
    call Regvalue
     inc bx
    mov RegistersArray2[bx], dh
    call regType
    call converttostring
    call Regvalue 
    inc bx
    cmp bx, 16
    jne drawFirstRegisters121

    jmp gameLoop

    executeFlyingBall:
    mov al, user
    push ax
    call clearScreenGame
    call SubGame

    mov flyBIndex, 0

    mov startrow, 0  
    mov memosize, 16
    mov verticalstart, 0
    mov regsize, 4
    mov countmemo, 2
    call DrawGame
    mov user, 2
    mov bx, 0
    drawFirstRegisters:
    call regType
    call converttostring
    call Regvalue 
    call fillmemo
    inc bx
    cmp bx, 16
    jne drawFirstRegisters
    mov bx,0  
    mov user, 1
    drawSecondRegisters: 
    call regType
    call converttostring
    call Regvalue
    call fillmemo
    inc bx
    cmp bx, 16
    jne drawSecondRegisters
    pop ax
    mov user, al
    mov flyBIndex, 0
    jmp gameLoop  


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

; instruction not found
; register not found
; memory not found
; typo in instruction
; typo in register (A  X)
; invalid addressing mode
; comma not found
; no [ or ]
; forbidden char exists
; number in op1
; NOP
; 
 