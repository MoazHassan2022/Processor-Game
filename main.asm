.MODEL LARGE
.STACK 64
.DATA    
;get info vars
usernameRequest db 'Please enter your username:','$'
scoreRequest db 'Enter your initial score:','$' 
enter db 'Press Enter key to continue', '$'
;end of get info vars

; main screen vars
startChating db 'To start chating press F2','$'
startGame db 'To start the game press F3','$'
endProgram db 'To end the program press ESC','$'
firstUsername db 15,?,"Mahmoud:",15 dup('$')   
Firstcountname db 9
firstInputScore db 4,?,4 dup('$')
firstScore dw ?
secondUsername db 15,?,"Waer:",15 dup('$')  
secondcountname db 6
secondInputScore db 4,?,4 dup('$')
secondScore dw 4  
Choose_the_mode db 'choose the mode','$' 

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
user db 1
;vars of registers
regInitialvalue db '0000','$'
regSize db 4
registerscount db 4 
RegsPosition db ? 
regnum db ?  
tempregname db "AXSICXDIBXSPDXBP" 
regvalues db "1101"
regposition dw ?   
isexist db ?   
shift dw 0 
;inline chat
inlineFirstOneTalk dw ?
arrive_max_message db "you are exceeded the max leght of the massage $"
; end of cahtting vars 
StringMsg db ?

.CODE

Main proc far
    mov ax, @DATA
    mov ds, ax
    
   ;call Get_Info
    
   main_Screen : call MainScreen   
 
  
    Chating:
        
        call ChatMode
        
  
        
        
        
        call firstOneWrite
        
        call SecondOneWrite
                  
    
        
                
    Game:
      ;DecideLevel 
     
      DrawGame     
  

           
        
    end1: 
    mov al, 0 
    mov ah,03
    int 10h                 
    mov ah,4ch
    int 21h    
endp
      
include Chatting.inc      
include general.inc
include MainScreen.inc
include GameMacros.inc                              
                              
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
