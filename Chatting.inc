ChatMode proc near
    pusha
    pushf

    mov al ,01h
    call changePage
    mov bh,1
    mov yx, 0102h
    call setCursor
    mov dx, yx
    add dl, firstUsername+1 
    mov msg, offset firstUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h
    mov yx, 0A00h
    Call Draw_H_Line ;middle line
    mov yx, 0B02h
    call setCursor
    mov dx, yx
    add dl, secondUsername+1 
    mov msg, offset secondUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h


        lea dx ,ChangeControlMsg
        mov msg,dx                  ; starting comment
        mov bh,1
        call Write_Not_First_Line

        lea dx,EndChatMode
        mov msg,dx
        call Write_Not_Second_Line

    mov yx, 0204h
    call setCursor





    popf
    popa

    ret
endp 

secondChatMode proc near
    pusha
    pushf
    mov al,01
    call changePage
    mov bh,3
    mov yx, 0102h
    call setCursor
    mov dx, yx
    add dl, secondUsername+1 
    mov msg, offset secondUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h
    mov yx, 0A00h
    Call Draw_H_Line ;middle line
    mov yx, 0B02h
    call setCursor
    mov dx, yx
    add dl, firstUsername+1 
    mov msg, offset firstUsername + 2
    call printMsg
    mov yx, dx
    call setCursor
    mov ah,2
    mov dl, ' '
    int 21h
    mov ah,2
    mov dl, ':'
    int 21h
    
    popf
    popa
    ret
endp


;// if enter was pressed he cursir will go to next line
EnterPressed proc near
    pusha
    pushf

    mov ax,FirstOneTalk
	sub al,4h
	mov ah,0
	mov si,ax
	mov StringMsg[si],'$'
	mov ax,FirstOneTalk
    cmp ah,09h
    jL call newline
    jae call shiftup

    popf
    popa
    jmp check
    
    ret
endp 

;// backSpace
backSpace proc near
    pusha
    pushf

    call innerMovLeft

    mov dl,' ' 
    mov ah,2
    int 21h 

    mov dx,FirstOneTalk
    mov yx,dx
    mov bh,1
    call setCursor

        popf
        popa
    
    jmp check


    ret
endp 


ScrollUp proc near
    pusha
    pushf

        mov ah, 6               ; http://www.ctyme.com/intr/rb-0096.htm
        mov al, 1              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 2               ; row top
        mov cl, 4               ; col left
        mov dh, 9             ; row bottom
        mov dl, 4fh              ; col right
        int 10h  
        

        mov dx , FirstOneTalk
        cmp dh,02h
        jnz nothere 
        mov FirstOneTalk,0204h
        mov yx,0204h   
        mov bh,1
        call setCursor 
        jmp check

        nothere:
        mov dx,FirstOneTalk
        dec dh 
        mov FirstOneTalk,dx  
        mov yx,dx
        mov bh,1
        
        call setCursor


            popf
            popa

        jmp check

    ret
endp 


;// backSpace
ScrollDown proc near
    pusha
    pushf

        mov ah, 7               ; http://www.ctyme.com/intr/rb-0096.htm
        mov al, 1               ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 2               ; row top
        mov cl, 4               ; col left
        mov dh, 9               ; row bottom
        mov dl, 4fh             ; col right
        int 10h 

        mov dx , FirstOneTalk
        cmp dh,09h
        jnz nothere2
        jmp check
        
        nothere2:
        mov dx,FirstOneTalk
        inc dh 
        mov FirstOneTalk,dx
        mov yx,dx 
        mov bh,1
        call setCursor
          popf
          popa


        jmp check  

    
    ret
endp 


MovRight proc near
    pusha
    pushf

     mov dx,FirstOneTalk
        cmp dl,4fh  
        jz check
        inc dl 
        mov FirstOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

            popf
            popa

        jmp check 

    ret
endp 


MovLeft proc near
    pusha
    pushf

       mov dx,FirstOneTalk 
        cmp dl,04h
        jz check
        dec dl 
        mov FirstOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
            popf
            popa
        jmp check

    ret
endp 

innerMovLeft proc near
    pusha
    pushf

       mov dx,FirstOneTalk 
        cmp dl,04h
        jz check
        dec dl 
        mov FirstOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
    popf
    popa
    ret
endp 

innerMovRight proc near
    pusha
    pushf

       
     mov dx,FirstOneTalk
        cmp dl,4fh  
        jz check
        inc dl 
        mov FirstOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

    popf
    popa
    ret
endp 


shiftup proc near
    pusha
    pushf

        mov ah, 6               ; http://www.ctyme.com/intr/rb-0096.htm
        mov al, 1              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 2               ; row top
        mov cl, 4               ; col left
        mov dh, 9             ; row bottom
        mov dl, 4fh              ; col right
        int 10h  
        call goTostartOfLine
        jmp check


    popf
    popa
    ret
endp 



newline proc near
    pusha
    pushf
        
    mov ax,FirstOneTalk
    inc ah
    mov al,04h
    mov FirstOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor


    popf
    popa
    
        jmp check


    ret
endp


goTostartOfLine proc near
    pusha
    pushf

    mov ax,FirstOneTalk
    mov al,04h
    mov FirstOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor

    popf
    popa
    ret
endp


StratNew proc near
    pusha
    pushf

        mov ah, 7               ; http://www.ctyme.com/intr/rb-0096.html
        mov al, 10              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 2               ; row top
        mov cl, 4               ; col left
        mov dh, 9               ; row bottom
        mov dl, 4fh              ; col right
        int 10h 

        mov dx,0204h;
        mov FirstOneTalk,dx
        mov yx,dx
        mov bh,1
        call setCursor


        jmp check  

    
    ret
endp 



firstOneWrite proc near
    pusha
    pushf

        mov dx,FirstOneTalk 
        mov yx,dx
        call setCursor

    check:

        mov ah,0
        int 16h     
        inc si
        cmp ah,4Bh
        jz call MovLeft
        cmp ah,4Dh
        jz call MovRight
        cmp ah,48h
        jz call ScrollUp
        cmp ah,50h
        jz call ScrollDown
        cmp al,8h
        jz call backSpace
        cmp ah,0Fh
        jz call SecondOneWrite
        cmp al,0dh
        jz call EnterPressed
        cmp ah,47h
        jz call StratNew 
        cmp ah,3Dh
        ;jz back to main screen 
     
        mov dx,FirstOneTalk
        cmp dl,50h                ;if he arrivel to the end of the line ;should handel it 
        jz call EnterPressed       
        mov ah,9
        mov bh,1
        mov cx,1
        mov bl,0Fh 
        int 10h
		;;;;
		mov dh,0
		sub dl,4
		mov si,dx
        mov stringmsg[si],al
		;;;;;;;;;;;;;
        mov ax,FirstOneTalk
        inc al                    ; mov cursur one right
        mov FirstOneTalk,ax
        mov yx,ax
        call setCursor   


        jmp check

    popf
    popa
    ret
endp 




;////////////////////////////////////////////////
; secon one proc




;// if enter was pressed he cursir will go to next line
SecondEnterPressed proc near
    pusha
    pushf

    mov ax,SecondOneTalk
    cmp ah,14h
    jL call Secondnewline
    jae call Secondshiftup

    popf
    popa
    jmp Secondcheck
    
    ret
endp 

;// backSpace
SecondbackSpace proc near
    pusha
    pushf

    call SecondinnerMovLeft

    mov dl,' ' 
    mov ah,2
    int 21h 

    mov dx,SecondOneTalk
    mov yx,dx
    mov bh,1
    call setCursor

        popf
        popa
    
    jmp Secondcheck


    ret
endp 


SecondScrollUp proc near
    pusha
    pushf

        mov ah, 6               ; http://www.ctyme.com/intr/rb-0096.htm
        mov al, 1              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 0ch              ; row top
        mov cl, 04h               ; col left
        mov dh, 14h             ; row bottom
        mov dl, 4fh              ; col right
        int 10h 

        

        mov dx , SecondOneTalk
        cmp dh,0ch
        jnz Seondnothere 
        mov SecondOneTalk,0c04h
        mov yx,0c04h   
        mov bh,1
        call setCursor 
        jmp Secondcheck

        Seondnothere:
        mov dx,SecondOneTalk
        dec dh 
        mov SecondOneTalk,dx  
        mov yx,dx
        mov bh,1
        
        call setCursor


            popf
            popa

        jmp Secondcheck

    ret
endp 


;// backSpace
SecondScrollDown proc near
    pusha
    pushf
        
        mov ah, 7               ; http://www.ctyme.com/intr/rb-0096.htm
        mov al, 1              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 0ch              ; row top
        mov cl, 04h               ; col left
        mov dh, 14h             ; row bottom
        mov dl, 4fh              ; col right
        int 10h 


        mov dx , SecondOneTalk
        cmp dh,14h
        jnz Secondnothere2
        jmp Secondcheck
        
        Secondnothere2:
        mov dx,SecondOneTalk
        inc dh 
        mov SecondOneTalk,dx
        mov yx,dx 
        mov bh,1
        call setCursor
          popf
          popa


        jmp Secondcheck  

    
    ret
endp 


SecondMovRight proc near
    pusha
    pushf

     mov dx,SecondOneTalk
        cmp dl,4fh  
        jz Secondcheck
        inc dl 
        mov SecondOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

            popf
            popa

        jmp Secondcheck 

    ret
endp 


SecondMovLeft proc near
    pusha
    pushf

       mov dx,SecondOneTalk 
        cmp dl,04h
        jz Secondcheck
        dec dl 
        mov SecondOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
            popf
            popa
        jmp Secondcheck

    ret
endp 

SecondinnerMovLeft proc near
    pusha
    pushf

       mov dx,SecondOneTalk 
        cmp dl,04h
        jz Secondcheck
        dec dl 
        mov SecondOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
    popf
    popa
    ret
endp 

SecondinnerMovRight proc near
    pusha
    pushf

       
     mov dx,SecondOneTalk
        cmp dl,4fh  
        jz Secondcheck
        inc dl 
        mov SecondOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

    popf
    popa
    ret
endp 


Secondshiftup proc near
    pusha
    pushf

        mov ah, 6               ; http://www.ctyme.com/intr/rb-0096.htm
        mov al, 1              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 0ch              ; row top
        mov cl, 04h               ; col left
        mov dh, 14h             ; row bottom
        mov dl, 4fh              ; col right
        int 10h  
        call SecondgoTostartOfLine
        jmp Secondcheck


    popf
    popa
    ret
endp 



Secondnewline proc near
    mov stringmsg[si],"$"
	mov si,-1  
    pusha
    pushf
    mov ax,SecondOneTalk
    inc ah
    mov al,04h
    mov SecondOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor


    popf
    popa
    
        jmp Secondcheck


    ret
endp


SecondgoTostartOfLine proc near
    pusha
    pushf

    mov ax,SecondOneTalk
    mov al,04h
    mov SecondOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor

    popf
    popa
    ret
endp


SecondStratNew proc near
    pusha
    pushf

        mov ah, 6               ; http://www.ctyme.com/intr/rb-0096.htm
        mov al, 10              ; number of lines to scroll
        mov bh, 0               ; attribute
        mov ch, 0ch              ; row top
        mov cl, 04h               ; col left
        mov dh, 14h             ; row bottom
        mov dl, 4fh              ; col right
        int 10h 

        mov dx,0c04h;
        mov SecondOneTalk,dx
        mov yx,dx
        mov bh,1
        call setCursor


        jmp Secondcheck  

    
    ret
endp 



SecondOneWrite proc near
    pusha
    pushf

        mov dx,SecondOneTalk
        mov yx,dx
        call setCursor

    Secondcheck:

        mov ah,0
        int 16h     
        
        cmp ah,4Bh
        jz call SecondMovLeft
        cmp ah,4Dh
        jz call SecondMovRight
        cmp ah,48h
        jz call SecondScrollUp
        cmp ah,50h
        jz call SecondScrollDown
        cmp al,8h
        jz call SecondbackSpace
        cmp al,09h
        jz call firstOneWrite
        cmp al,0dh
        jz call SecondEnterPressed
        cmp ah,47h
        jz call SecondStratNew 
        cmp ah,3Dh
        ;jz back to main screen 
        
        
        mov dx,SecondOneTalk
        cmp dl,50h                ;if he arrivel to the end of the line
        jz call EnterPressed
                    
        mov ah,9
        mov bh,1
        mov cx,1
        mov bl,0Fh 
        int 10h
      
        mov ax,SecondOneTalk
        inc al                    ; mov cursur one right
        mov SecondOneTalk,ax
        mov yx,ax
        call setCursor   


        jmp Secondcheck

    popf
    popa
    ret
endp 
; this macro used to decide the level of the game and with the validations if the user enter 1 or 2 the forbidden page will appear and otherwise 
;the macro invalid msg will print invalid msg at the end of the page only one time by using the count which will be checked before call the macro 
macro DecideLevel 
	 mov al ,01h
	 call changePage 
	 call clearScreen
	 call clearNotifcationArea; doesn't work
	 mov yx,0202h
	 call setCursor
	 mov dx,offset LevelMsg
	 mov msg,dx
	 call printMsgAtyx
	 mov yx,0204h
	 call setCursor
	 Again:
	 mov ah,7h
	 int 21h 
	 cmp al,31h
	 jz Valid
	 cmp al,32h
	 jz Valid
	 cmp al,0Dh
	 ;;call main=>moza
	 cmp count,0
	 jnz Again
	 InvalidMsgProc ;macro call on time only 
	 inc count
	 jmp Again

	 Valid:
	 ForbiddenChar
	 Decided:
endm DecideLevel
;Proc Frobidden char use it to take the forbidden char
macro ForbiddenChar
	 mov al ,01h
	 call changePage 
     call clearScreen
	 call clearNotifcationArea
	 mov yx,0202h
	 mov dx,offset Forbidden
	 mov msg,dx
	call printMsgAtyx
	mov yx,0502h
	call setCursor
	 EnterAgain:
	 mov ah,7h
	 int 21h
	  cmp ah,4Bh
        jz invalidchar
        cmp ah,4Dh
        jz invalidchar
        cmp ah,48h
        jz invalidchar
        cmp ah,50h
        jz invalidchar
        cmp al,8h
        jz invalidchar
        cmp al,09h
        jz invalidchar
        cmp al,0dh
        jz invalidchar
        cmp ah,47h
       jz invalidchar
	   validchar:
		mov ForbiddenChar1,al
		jmp ForbiddenTaken
		invalidchar:
		cmp count2,0
		jnz EnterAgain
		inc count2 
		InvalidMsgForbiddenProc
		jnz EnterAgain
		ForbiddenTaken:

endm ForbiddenChar
; this macro is used to print the msg invalid number if the user enter invalid number to the level
macro InvalidMsgProc 
	mov dx,offset InvalidMsg
	mov msg,dx
	mov bh,1
	call Write_Not_First_Line
	mov yx,0204h
	call setCursor
endm InvalidMsgProc

; this macro is used to print the msg invalid number if the user enter invalid char to the forbidden
macro InvalidMsgForbiddenProc 
	mov dx,offset InvalidMsgForbidden
	mov msg,dx
	mov bh,1
    call Write_Not_First_Line
	mov yx,0502h
	call setCursor
endm InvalidMsgProc 