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
Choose_the_mode db 'choose the mode','$'

.CODE

Main proc far
    mov ax, @DATA
    mov ds, ax
    
    call Get_Info
    
    call MainScreen
    
    Chating:
        call firstChatMode 
        mov yx, 0204h
        call setCursor
        call secondChatMode  
        mov bh,01
        mov yx, 0204h
        call setCursor        
        jmp end1 
        
                
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
