;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Chatting;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ChatMode proc near
    push ax
push bx
push cx
push dx
    pushf
    

    mov al ,01h
    call changePage
    mov bh,1
    mov yx, 0402h
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
    mov yx, 0E00h
    Call Draw_H_Line ;middle line
    mov yx, 0F02h
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

    popf
    pop dx
pop cx
pop bx
pop ax

    ret
ChatMode endp 

secondChatMode proc near
    push ax
push bx
push cx
push dx
    pushf
    mov al,01
    call changePage
    mov bh,3
    mov yx, 0402h
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
    mov yx, 0D00h
    Call Draw_H_Line ;middle line
    mov yx, 0E02h
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
    pop dx
pop cx
pop bx
pop ax
    ret
secondChatMode endp


;// if enter was pressed he cursir will go to next line
EnterPressed proc near
    push ax
push bx
push cx
push dx
    pushf

    mov ax,FirstOneTalk
	sub al,4h
	mov ah,0
	mov si,ax
	mov StringMsg[si],'$'
	mov ax,FirstOneTalk
    cmp ah,09h
    jae fixThirtyFour
    call newline
    fixThirtyFour:
    call shiftup

    popf
    pop dx
pop cx
pop bx
pop ax
    jmp far ptr check
    
    ret
EnterPressed endp 

;// backSpace
backSpace proc near
    push ax
push bx
push cx
push dx
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
        pop dx
pop cx
pop bx
pop ax
    
    jmp far ptr check


    ret
backSpace endp 


ScrollUp proc near
    push ax
push bx
push cx
push dx
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
        mov yx,0504h   
        mov bh,1
        call setCursor 
        jmp far ptr check

        nothere:
        mov dx,FirstOneTalk
        dec dh 
        mov FirstOneTalk,dx  
        mov yx,dx
        mov bh,1
        
        call setCursor


            popf
            pop dx
pop cx
pop bx
pop ax

        jmp far ptr check

    ret
ScrollUp endp 


;// backSpace
ScrollDown proc near
    push ax
push bx
push cx
push dx
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
        jmp far ptr check
        
        nothere2:
        mov dx,FirstOneTalk
        inc dh 
        mov FirstOneTalk,dx
        mov yx,dx 
        mov bh,1
        call setCursor
          popf
          pop dx
pop cx
pop bx
pop ax


        jmp far ptr check  

    
    ret
ScrollDown endp 


MovRight proc near
    push ax
push bx
push cx
push dx
    pushf

     mov dx,FirstOneTalk
        cmp dl,4fh  
        jnz fixThirtyThree
        jmp check
        fixThirtyThree:
        inc dl 
        mov FirstOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

            popf
            pop dx
pop cx
pop bx
pop ax

        jmp far ptr check 

    ret
MovRight endp 


MovLeft proc near
    push ax
push bx
push cx
push dx
    pushf

       mov dx,FirstOneTalk 
        cmp dl,04h
        jnz fixThirtyTwo
        jmp check
        fixThirtyTwo:
        dec dl 
        mov FirstOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
            popf
            pop dx
pop cx
pop bx
pop ax
        jmp far ptr check

    ret
MovLeft endp 

innerMovLeft proc near
    push ax
push bx
push cx
push dx
    pushf

       mov dx,FirstOneTalk 
        cmp dl,04h
        jnz fixThirtyOne
        jmp check
        fixThirtyOne:
        dec dl 
        mov FirstOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
innerMovLeft endp 

innerMovRight proc near
    push ax
push bx
push cx
push dx
    pushf

       
     mov dx,FirstOneTalk
        cmp dl,4fh  
        jnz fixThirty
        jmp check
        fixThirty:
        inc dl 
        mov FirstOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
innerMovRight endp 


shiftup proc near
    push ax
push bx
push cx
push dx
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
        jmp far ptr check


    popf
    pop dx
pop cx
pop bx
pop ax
    ret
shiftup endp 



newline proc near
    push ax
push bx
push cx
push dx
    pushf
        
    mov ax,FirstOneTalk
    inc ah
    mov al,04h
    mov FirstOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor


    popf
    pop dx
pop cx
pop bx
pop ax
    
        jmp far ptr check


    ret
newline endp


goTostartOfLine proc near
    push ax
push bx
push cx
push dx
    pushf

    mov ax,FirstOneTalk
    mov al,04h
    mov FirstOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
goTostartOfLine endp


StratNew proc near
    push ax
push bx
push cx
push dx
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


        jmp far ptr check  

    
    ret
StratNew endp 



firstOneWrite proc near
    push ax
push bx
push cx
push dx
    pushf

        mov bh, 1
        mov dx,FirstOneTalk 
        mov yx,dx
        call setCursor

    check:

        mov ah,0
        int 16h     
        inc si
        cmp ah,4Bh
        jnz fixTwentySix
        call MovLeft
        fixTwentySix:
        cmp ah,4Dh
        jnz fixTwentyFive
        call MovRight
        fixTwentyFive:
        cmp ah,48h
        jnz fixTwentyFour
        call ScrollUp
        fixTwentyFour:
        cmp ah,50h
        jnz fixTwentyThree
        call ScrollDown
        fixTwentyThree:
        cmp al,8h
        jnz fixTwentyTwo 
        call backSpace
        fixTwentyTwo:
        cmp ah,0Fh
        jnz fixTwentyOne 
        call SecondOneWrite
        fixTwentyOne:
        cmp al,0dh
        jnz fixTwenty
        call EnterPressed
        fixTwenty:
        cmp ah,47h
        jnz fixNineteen
        call StratNew
        fixNineteen: 
        cmp ah,3Dh
        jnz fixWaer
        jmp main_Screen
        fixWaer:

        mov dx,FirstOneTalk
        cmp dl,50h                ;if he arrivel to the end of the line ;should handel it 
        jnz fixTwentyNine
        call EnterPressed
        fixTwentyNine:       
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


        jmp far ptr check

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
firstOneWrite endp 


;////////////////////////////////////////////////
; secon one proc




;// if enter was pressed he cursir will go to next line
SecondEnterPressed proc near
    push ax
push bx
push cx
push dx
    pushf

    mov ax,SecondOneTalk
    cmp ah,14h
    jae fixTwentyEight
    call Secondnewline
    fixTwentyEight: 
    jl fixTwentySvn
    call Secondshiftup
    fixTwentySvn:

    popf
    pop dx
pop cx
pop bx
pop ax
    jmp far ptr Secondcheck
    
    ret
SecondEnterPressed endp 

;// backSpace
SecondbackSpace proc near
    push ax
push bx
push cx
push dx
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
        pop dx
pop cx
pop bx
pop ax
    
    jmp far ptr Secondcheck


    ret
SecondbackSpace endp 


SecondScrollUp proc near
    push ax
push bx
push cx
push dx
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
        mov yx,0F04h   
        mov bh,1
        call setCursor 
        jmp far ptr Secondcheck

        Seondnothere:
        mov dx,SecondOneTalk
        dec dh 
        mov SecondOneTalk,dx  
        mov yx,dx
        mov bh,1
        
        call setCursor


            popf
            pop dx
pop cx
pop bx
pop ax

        jmp far ptr Secondcheck

    ret
SecondScrollUp endp 


;// backSpace
SecondScrollDown proc near
    push ax
push bx
push cx
push dx
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
        jmp far ptr Secondcheck
        
        Secondnothere2:
        mov dx,SecondOneTalk
        inc dh 
        mov SecondOneTalk,dx
        mov yx,dx 
        mov bh,1
        call setCursor
          popf
          pop dx
pop cx
pop bx
pop ax


        jmp far ptr Secondcheck  

    
    ret
SecondScrollDown endp 


SecondMovRight proc near
    push ax
push bx
push cx
push dx
    pushf

     mov dx,SecondOneTalk
        cmp dl,4fh  
        jnz fixEighteen
        jmp Secondcheck
        fixEighteen:
        inc dl 
        mov SecondOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

            popf
            pop dx
pop cx
pop bx
pop ax

        jmp far ptr Secondcheck 

    ret
SecondMovRight endp 


SecondMovLeft proc near
    push ax
push bx
push cx
push dx
    pushf

       mov dx,SecondOneTalk 
        cmp dl,04h
        jnz fixSvteen
        jmp Secondcheck
        fixSvteen:
        dec dl 
        mov SecondOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
            popf
            pop dx
pop cx
pop bx
pop ax
        jmp far ptr Secondcheck

    ret
SecondMovLeft endp 

SecondinnerMovLeft proc near
    push ax
push bx
push cx
push dx
    pushf

       mov dx,SecondOneTalk 
        cmp dl,04h
        jnz fixSixteen
        jmp Secondcheck
        fixSixteen:
        dec dl 
        mov SecondOneTalk,dx
        mov yx,dx   
        mov bh,1
        call setCursor
    popf
    pop dx
pop cx
pop bx
pop ax
    ret
SecondinnerMovLeft endp 

SecondinnerMovRight proc near
    push ax
push bx
push cx
push dx
    pushf

       
     mov dx,SecondOneTalk
        cmp dl,4fh  
        jnz fixFvteen
        jmp Secondcheck
        fixFvteen:
        inc dl 
        mov SecondOneTalk,dx
        mov yx,dx  
        mov bh,1
        call setCursor

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
SecondinnerMovRight endp 


Secondshiftup proc near
    push ax
push bx
push cx
push dx
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
        jmp far ptr Secondcheck


    popf
    pop dx
pop cx
pop bx
pop ax
    ret
Secondshiftup endp 



Secondnewline proc near
    mov stringmsg[si],"$"
	mov si,-1  
    push ax
push bx
push cx
push dx
    pushf
    mov ax,SecondOneTalk
    inc ah
    mov al,04h
    mov SecondOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor


    popf
    pop dx
pop cx
pop bx
pop ax
    
        jmp far ptr Secondcheck


    ret
Secondnewline endp


SecondgoTostartOfLine proc near
    push ax
push bx
push cx
push dx
    pushf

    mov ax,SecondOneTalk
    mov al,04h
    mov SecondOneTalk,ax 
    mov yx,ax
    mov bh,1
    call setCursor

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
SecondgoTostartOfLine endp


SecondStratNew proc near
    push ax
push bx
push cx
push dx
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


        jmp far ptr Secondcheck  

    
    ret
SecondStratNew endp 



SecondOneWrite proc near
    push ax
push bx
push cx
push dx
    pushf

        mov dx,SecondOneTalk
        mov yx,dx
        call setCursor

    Secondcheck:

        mov ah,0
        int 16h     
        
        cmp ah,4Bh
        jnz fixSvn
        call SecondMovLeft
        fixSvn: 
        cmp ah,4Dh
        jnz fixEight
        call SecondMovRight
        fixEight: 
        cmp ah,48h
        jnz fixNine
        call SecondScrollUp
        fixNine:
        cmp ah,50h
        jnz fixTen
        call SecondScrollDown
        fixTen:
        cmp al,8h
        jnz fixElvn 
        call SecondbackSpace
        fixElvn:
        cmp al,09h
        jnz fixTwlv
        call firstOneWrite
        fixTwlv:
        cmp al,0dh
        jnz fixThrtn
        call SecondEnterPressed
        fixThrtn:
        cmp ah,47h
        jnz fixFourteen
        call SecondStratNew 
        fixFourteen:
        cmp ah,3Dh
        jnz fixReda
        jmp main_Screen
        fixReda: 
        
        
        mov dx,SecondOneTalk
        cmp dl,50h                ;if he arrivel to the end of the line
        jnz fixSix
        call EnterPressed
        fixSix:             
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


        jmp far ptr Secondcheck

    popf
    pop dx
pop cx
pop bx
pop ax
    ret
SecondOneWrite endp 





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
