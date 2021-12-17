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
firstUsername db 15,?,15 dup('$') 
firstInputScore db 4,?,4 dup('$')
firstScore dw ?
secondUsername db 15,?,15 dup('$') 
secondInputScore db 4,?,4 dup('$')
secondScore dw ?  
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

; end of cahtting vars

.CODE

Main proc far
    mov ax, @DATA
    mov ds, ax
    
   call Get_Info
    
   main_Screen : call MainScreen   
 
  
    Chating:
        
        call ChatMode
        
  
        
        
        
        call firstOneWrite
        
        call SecondOneWrite
                  
    
        
                
    Game:
        mov msg, offset startGame
        call printMsg    
           
        
    end1:
                      
    mov ah,4ch
    int 21h    
endp
      
include Chatting.inc      
include general.inc
include MainScreen.inc

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

