
; res in bl
; make di stop in first of string
getlen proc near 
mov bl,0
len:
mov bh,'$'
cmp [di] , bh
jz finsihlen
inc bl
inc di
jmp len

finsihlen:
ret 
getlen endp


DrawGame proc near
push ax
push bx
push cx
push dx
pushf


;//////////////////////////// calc the length of both users names

mov di , offset firstUsername[2]
call getlen
mov Firstcountname , bl

mov di , offset secondUsername[2]
call getlen
mov secondcountname , bl


;compare the which user
cmp whichuser,1
jnz metheseconduser
mov dx,0
mov dl,Firstcountname
mov dh,16h
mov startofinlinechat ,dl
mov inlineChatindicator,dx

mov dl, Secondcountname
inc dh
mov printinlinechatindicator ,dx

jmp labeltoendtheindector
metheseconduser:

mov dx,0
mov dl,Secondcountname
mov dh,17h
mov startofinlinechat ,dl
mov inlineChatindicator,dx

mov dl,Firstcountname
dec dh
mov printinlinechatindicator ,dx
labeltoendtheindector:

;////////////////////////////////

mov ah,0
mov al,13h
int 10h

mov verticalend,133
mov horizotalpostion,18
call drawvertical


mov verticalend,155
mov horizotalpostion,40
call drawvertical


mov verticalend,133
mov horizotalpostion,159
call drawvertical


mov verticalend,133
mov horizotalpostion,300
call drawvertical


mov verticalend,155
mov horizotalpostion,279
call drawvertical

mov verticalstart, 155
mov verticalend,174
mov horizotalpostion,159
call drawvertical

mov endrow,320
mov colnum,133
call drawhorziontal
cmp Levelnum,31h
jnz Gameleveltwo
mov verticalstart,145
mov verticalend,155
mov horizotalpostion,10
call drawvertical

mov verticalstart,145
mov horizotalpostion,310
call drawvertical
call showforbiddenchar

Gameleveltwo:
mov colnum,155
call drawhorziontal

mov colnum,174
call drawhorziontal

labelreda9:

mov endrow,36
mov colnum,9
drawcells1:
	;call drawhorziontal
	add colnum,9
cmp colnum,144
jnz drawcells1


mov colnum,9
mov endrow,320
mov startrow,284
drawcells2:
	;call drawhorziontal
	add colnum,9
cmp colnum,144
jnz drawcells2

;/////////////////////////////////////////////////
;draw the registers vertical lines
mov horizotalpostion,50
call drawregsver

;draw the registers horziontal lines
;the below line
mov colnum,24
mov startrow,50
mov endrow,90
call drawregshor

;the above line
mov colnum,14
mov startrow,50
mov endrow,90
call drawregshor



;the second four regs
;draw the registers vertical lines
mov horizotalpostion,100
call drawregsver



;draw the registers horziontal lines
;the below line
mov colnum,24
mov startrow,100
mov endrow,140
call drawregshor

;the above line
mov colnum,14
mov startrow,100
mov endrow,140
call drawregshor


;/////////////draw the regs to the second user


;draw the registers vertical lines
mov horizotalpostion,185
call drawregsver

;draw the registers horziontal lines
;the below line
mov colnum,24
mov startrow,185
mov endrow,225
call drawregshor

;the above line
mov colnum,14
mov startrow,185
mov endrow,225
call drawregshor



;the second four regs
;draw the registers vertical lines
mov horizotalpostion,235
call drawregsver



;draw the registers horziontal lines
;the below line
mov colnum,24
mov startrow,235
mov endrow,275
call drawregshor

;the above line
mov colnum,14
mov startrow,235
mov endrow,275
call drawregshor



;///start write the words
 mov yx,0003
call fillmemocells1

 mov yx,0035
call fillmemocells1

 mov yx,0000
call fillmemocells2


 mov yx,0038
call fillmemocells2


mov RegsPosition,7
call fillreg

mov registerscount,4
mov RegsPosition,24
call fillreg
mov yx,0107h
call fillthenamesoftheregs

mov yx,0118h
call fillthenamesoftheregs

call usersnames
;call Inlinechat
mov yx,1100h
call scoretext
mov yx,1123h
call scoretext
mov user, 1
call showScore
mov user, 2
call showScore

mov user, 1
popf
pop dx
pop cx
pop bx
pop ax
ret
DrawGame endp

;/////////////////////////////////////////////////////////////////
;Memory and Registers
Fillmemo proc near
push ax
push bx
push cx
push dx 
pushf
cmp user,1 
jz default
mov yx,0000
mov dx,yx
add dh,bl
mov yx,dx
mov dl, MyMemoryArray[bx] ; /// bx is given to the proc
jmp startfill
default: mov yx,0038
mov dx,yx
add dh,bl
mov yx,dx
mov dl, MyMemoryArray2[bx] ; /// bx is given to the proc
startfill:
mov regvalues, dl ;/// To call convert you have to put the value in regvalues
call converttostring
mov countmemo, 2
mov si,2
mov bh,0
li22:
call setCursor
            mov ah,9
            mov al, hexaStr[si]
            mov bh,0
            mov cx,1
            mov bl,7
            int 10h
			inc yx
			inc si
	dec countmemo
cmp countmemo,0
jnz li22


popf 
pop dx
pop cx
pop bx
pop ax
ret
Fillmemo endp 


fillmemocells1 proc near 
push ax
push bx
push cx
push dx
pushf
mov memosize, 16
mov bh,0
mov si,0
li:mov countmemo, 2

li2:call setCursor
            mov ah,9
            mov al, memo1[si]
            mov bh,0
            mov cx,1
            mov bl,7
            int 10h
			inc yx
			inc si
	dec countmemo
jnz li2
mov cx,yx
inc ch
dec cl
dec cl
mov yx,cx
dec memosize
cmp memosize , 0
jnz li 
popf
pop dx
pop cx
pop bx
pop ax
ret
fillmemocells1 endp


fillmemocells2 proc near 
push ax
push bx
push cx
push dx
pushf
mov memosize, 16
mov bh,0
mov si,0
li3:mov countmemo, 2

li4:call setCursor
            mov ah,9
            mov al, memo2[si]
            mov bh,0
            mov cx,1
            mov bl,7
            int 10h
			inc yx
			inc si
	dec countmemo
jnz li4
mov cx,yx
inc ch
dec cl
dec cl
mov yx,cx
dec memosize
cmp memosize , 0
jnz li3 
popf
pop dx
pop cx
pop bx
pop ax
ret
fillmemocells2 endp
     
fillreg proc near
push ax
push bx
push cx
push dx
pushf
    mov registerscount, 4
    mov bh,0  
    mov dh, 2
    mov dl, RegsPosition
    mov yx, dx
    label1:
    mov countmemo, 2
    label2:
    mov regSize, 4
    label3:
    call setCursor
            mov ah,9            
            mov al, '0'
            mov bh,0
            mov cx,1
            mov bl,4
            int 10h
            inc yx
    dec regSize
    jnz label3
    
    add dl, 6
    mov yx, dx
    dec countmemo
    jnz label2
    mov dl, RegsPosition
    add dh, 3
    mov yx, dx
    dec registerscount
    jnz label1
popf
pop dx
pop cx
pop bx
pop ax
ret
fillreg endp





;//////////////////////////////////////////////////////////////////////////////
drawvertical proc near 
push ax
push bx
push cx
push dx
pushf
mov bh,1
mov cx,horizotalpostion
mov dx,verticalstart
mov al,0fh
mov ah , 0ch
condraw: int 10h
inc dx
cmp dx,verticalend
jnz condraw
popf
pop dx
pop cx
pop bx
pop ax
ret
drawvertical endp

drawhorziontal proc near 
push ax
push bx
push cx
push dx
pushf
mov bh,1
mov cx,startrow
mov dx,colnum
mov al,0fh
mov ah , 0ch
condraw2: int 10h
inc cx
cmp cx,endrow
jnz condraw2
popf
pop dx
pop cx
pop bx
pop ax
ret
drawhorziontal endp




drawregsver proc near 
push ax
push bx
push cx
push dx
pushf
mov si,2
loopregs1:
	mov verticalstart,14
	mov verticalend,24
drawregs1:
	call drawvertical
	add verticalend,24
	add verticalstart,24
cmp verticalend,96
jle drawregs1
add horizotalpostion,40
dec si
cmp si,0
jnz loopregs1

popf
pop dx
pop cx
pop bx
pop ax
ret
drawregsver endp

drawregshor proc near 
push ax
push bx
push cx
push dx
pushf

drawregshor1:
	call drawhorziontal
	add colnum,24
cmp colnum,100
jle drawregshor1

popf
pop dx
pop cx
pop bx
pop ax
ret
drawregshor endp
;//////////////////////function to set the value in the regs 
;this function takes the name of the reg and the user value if user1 takes 1 if the second user takes 2
Regtype proc near
push ax
push bx
push cx
push dx
pushf

cmp user,1 
jnz fixRedaTwo
jmp usertwo
fixRedaTwo:



cmp bx,0    ;al
jnz secondcheckreg3
mov regposition,0209h
jmp setlocation1



secondcheckreg3:
cmp bx,1    ;ah
jnz Thridcheck
mov regposition,0207h
jmp setlocation1

Thridcheck:
cmp bx,4  ;cl
jnz Thridcheck3
mov regposition,0509h
jmp setlocation1



Thridcheck3:
cmp bx,5  ;ch
jnz fourcheck3
mov regposition,0507h
jmp setlocation1

fourcheck3:
cmp bx,2  ;bl
jnz fourcheck
mov regposition,0809h
jmp setlocation1

fourcheck:
cmp bx,3  ;bh
jnz fifthckeck3
mov regposition,0807h
jmp setlocation1

fifthckeck3:
cmp bx,6  ;dl
jnz fifthckeck
mov regposition,0b09h
jmp setlocation1

fifthckeck:
cmp bx,7  ;dh 
jnz sixckeck5
mov regposition,0b07h
jmp setlocation1


sixckeck5:  ;sil
cmp bx,8
jnz Sixcheck3
mov regposition,020fh
jmp setlocation1


Sixcheck3:  ;sih
cmp bx,9
jnz sevevcheck
mov regposition,020dh
jmp setlocation1


sevevcheck:  ;dil
cmp bx, 0ah
jnz sevevcheck3
mov regposition,050fh
jmp setlocation1


sevevcheck3:
cmp bx,0bh		;dih
jnz eightcheck3
mov regposition,050dh
jmp setlocation1

eightcheck3:
cmp bx,0ch    ; spl
jnz eightcheck		
mov regposition,080fh
jmp setlocation1

eightcheck:
cmp bx,0dh    ; sph
jnz ninecheck3		
mov regposition,080dh
jmp setlocation1

ninecheck3:
cmp bx,0eh    ; Bpl
jnz ninecheck		
mov regposition,0B0fh
jmp setlocation1

ninecheck:
cmp bx,0fh    ; Bph	
mov regposition,0B0dh
jmp setlocation1


usertwo:


cmp bx,0    ;al
jnz secondcheckreg4
mov regposition,021Ah
jmp setlocation1



secondcheckreg4:
cmp bx,1    ;ah
jnz Thridcheck1
mov regposition,0218h
jmp setlocation1

Thridcheck1:
cmp bx,4  ;cl
jnz Thridcheck4
mov regposition,051Ah
jmp setlocation1



Thridcheck4:
cmp bx,5  ;ch
jnz fourcheck4
mov regposition,0518h
jmp setlocation1

fourcheck4:
cmp bx,2  ;bl
jnz fourcheck1
mov regposition,081Ah
jmp setlocation1

fourcheck1:
cmp bx,3  ;bh
jnz fifthckeck4
mov regposition,0818h
jmp setlocation1

fifthckeck4:
cmp bx,6  ;dl
jnz fifthckeck1
mov regposition,0b1Ah
jmp setlocation1

fifthckeck1:
cmp bx,7  ;dh 
jnz sixckeck1
mov regposition,0b18h
jmp setlocation1


sixckeck1:  ;sil
cmp bx,8
jnz Sixcheck4
mov regposition,0220h
jmp setlocation1


Sixcheck4:  ;sih
cmp bx,9
jnz sevevcheck1
mov regposition,021Eh
jmp setlocation1


sevevcheck1:  ;dil
cmp bx, 0ah
jnz sevevcheck4
mov regposition,0520h
jmp setlocation1


sevevcheck4:
cmp bx,0bh		;dih
jnz eightcheck4
mov regposition,051Eh
jmp setlocation1

eightcheck4:
cmp bx,0ch    ; spl
jnz eightcheck1		
mov regposition,0820h
jmp setlocation1

eightcheck1:
cmp bx,0dh    ; sph
jnz ninecheck4		
mov regposition,081Eh
jmp setlocation1

ninecheck4:
cmp bx,0eh    ; Bpl
jnz ninecheck1		
mov regposition,0B20h
jmp setlocation1

ninecheck1:
cmp bx,0fh    ; Bph
mov regposition,0B1Eh
jmp setlocation1

setlocation1:
cmp user,1
jz usertwoval
mov dl,RegistersArray[bx]
jmp endselection
usertwoval:
mov dl,RegistersArray2[bx]
endselection:
mov regvalues,dl

popf 
pop dx
pop cx
pop bx
pop ax
ret
Regtype endp


Regvalue proc
push ax
push bx
push cx
push dx
pushf
mov dx,regposition
mov yx,dx
mov bh,0
mov regSize,2
mov si,2

labelR:
mov bh,0
    call setCursor
            mov ah,9            
            mov al, hexaStr[si] ;;;;;;;;;;;; HERE
            mov bh,0
            mov cx,1
            mov bl,4 
            int 10h
			inc si
            inc yx
    dec regSize
    jnz labelR


popf
pop dx
pop cx
pop bx
pop ax
ret
Regvalue endp


;/i don't need this function
compareregs proc
 push ax
push bx
push cx
push dx 
 pushf
 mov di,0
 mov si,0
 ;add si , shift
 mov cx,2
 labelll:
 ;mov al, regname[di]
 mov dl,tempregname[si]
 cmp dl,al
 jnz notequalchar
 inc si
 inc di
loop labelll
;mov isexist,1
notequalchar:
 popf
 pop dx
pop cx
pop bx
pop ax
 ret
compareregs endp


 fillthenamesoftheregs proc near
 push ax
push bx
push cx
push dx
 pushf
 mov si,0
 mov regSize,4
 loop11:
 mov shift,2
 loop0:
 mov countmemo,2
 loop1:
 mov bh,0
 call setcursor
		    mov ah,9            
            mov al, tempregname[si]
            mov bh,0
            mov cx,1
            mov bl,7
            int 10h
            inc si
			inc yx
			dec countmemo

 cmp countmemo,0
 jnz loop1
 add yx,6
 dec shift
 cmp shift,0
 jnz loop0
 mov cx,yx
 sub cl,10h
 add  ch ,3
 mov yx,cx
 dec regsize
 cmp regsize,0
 jnz loop11
 


 popf
 pop dx
pop cx
pop bx
pop ax
 ret
 fillthenamesoftheregs endp


 ;fucntion to fill the names of the users
 usersnames proc near
 push ax
push bx
push cx
push dx
 pushf
 mov yx,1600h
 mov bh,0
 call setcursor
 mov cl,Firstcountname
 dec cl
 mov ch,0
 mov si,2
 labelloop:
			call setcursor
			mov ah,9            
            mov al, firstUsername[si]
            mov bh,0
			push cx
            mov cx,1
            mov bl,7
            int 10h
			pop cx
			inc yx
            inc si
 loop labelloop
 mov si,2
 mov yx,1700h
 mov bh,0
 call setcursor
 mov cl,secondcountname
 dec cl
 mov ch,0
 labelloop2:
			call setcursor
			mov ah,9            
            mov al, secondUsername[si]
            mov bh,0
			push cx
            mov cx,1
            mov bl,7
            int 10h
			pop cx
			inc yx
            inc si
 loop labelloop2


 popf
 pop dx
pop cx
pop bx
pop ax
 ret
 usersnames endp


 showforbiddenchar proc near
 push ax
push bx
push cx
push dx
 pushf
 cmp levelnum,31h
 jnz leveltwo
 mov yx,1200h
 mov bh,0
 call setcursor
 mov ah,9            
 mov al,ForbiddenChar1
 mov cx,1
 mov bl,0Fh 
 int 10h
 mov al,ForbiddenChar2
 mov yx,1227h
 call setcursor
 int 10h
 jmp endshow
 leveltwo:
 endshow:

 popf
 pop dx
pop cx
pop bx
pop ax
 ret
 showforbiddenchar endp


 scoretext proc near
 push ax
push bx
push cx
push dx
 pushf
 mov si,0
 mov regSize,5
 looptofillscoretext:
 mov bh,0
 call setcursor
 mov ah,9            
 mov al,scoreintialization[si]
 mov cx,1
 mov bl,1
 int 10h
 inc si
 inc yx
 dec regsize
 cmp regsize,0
 jnz looptofillscoretext



 popf
 pop dx
pop cx
pop bx
pop ax
 ret
 scoretext endp

 showScore proc near
    cmp user, 1
    jnz secondUserScore
    ConvertDecString firstScore, scoreString
    labelScore:
    mov yx, 1202h
    jmp endShowScore
    secondUserScore:
    ConvertDecString secondScore, scoreString
    mov yx, 1223h
    endShowScore:
    push yx
    mov si, 3
    emptyScoreLoop:
     mov ah,9            
    mov al,' '
    mov bh, 0
    call setCursor
    mov cx,1
    mov bl,1
    int 10h
    dec si
    inc yx
    cmp si, 0
    jnz emptyScoreLoop
    pop yx
    mov si, 0
    showScoreLoop:
     mov ah,9            
    mov al,scoreString[si]
    cmp al, '$'
    je outShowScoreLoop
    mov bh, 0
    call setCursor
    mov cx,1
    mov bl,1
    int 10h
    inc si
    inc yx
    jmp showScoreLoop
    outShowScoreLoop:
    ret
showScore endp    

;///////////////////////////////////////////////////////////////////
 



;Proc Frobidden char use it to take the forbidden char
; bl: 1 ->> forbiddenChar1, 2 ->> forbiddenChar2
ForbiddenChar macro 
LOCAL ForbiddenTaken, validchar, invalidchar, EnterAgain, receiveForbidden2
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
        jz  invalidchar
        cmp ah,4Dh
        jz  invalidchar
        cmp ah,48h
        jz  invalidchar
        cmp ah,50h
        jz  invalidchar
        cmp al,8h
        jz  invalidchar
        cmp al,09h
        jz  invalidchar
        cmp al,0dh
        jz  invalidchar
        cmp ah,47h
       jz  invalidchar
	   validchar:
       cmp bl, 1
       jne receiveForbidden2
        mov ForbiddenChar2,al
        jmp ForbiddenTaken
       receiveForbidden2:
		mov ForbiddenChar1,al
		jmp  ForbiddenTaken
		invalidchar:
		cmp count2,0
		jnz  EnterAgain
		inc count2 
		InvalidMsgForbiddenProc
		jnz  EnterAgain
		ForbiddenTaken:

endm ForbiddenChar
; this macro used to decide the level of the game and with the validations if the user enter 1 or 2 the forbidden page will appear and otherwise 
;the macro invalid msg will print invalid msg at the end of the page only one time by using the count which will be checked before call the macro 
;the new version of decide level that the main user who only will decide the level of the game and the fucntion will send the level after that
DecideLevel macro  
LOCAL Decided, Valid, Again, notLvlTwo, fixLvlTwo, fixLvlTwo2, fixLvlTwo3
	 mov al ,01h
	 call changePage 
	 call clearScreen
	 call clearNotifcationArea; doesn't work
	 mov yx,0202h
	 call setCursor
	 mov dx,offset LevelMsg
	 mov msg,dx
	 call printMsgAtyx
	 mov yx,0402h
	 call setCursor
	 Again:
	 mov ah,7h
	 int 21h 
	 cmp al,31h
	 jnz fixLvlTwo2
     jmp Valid
     fixLvlTwo2:
	 cmp al,32h
     jnz fixLvlTwo3
     jmp Valid
     fixLvlTwo3:
	 cmp count,0
	 jz fixLvlTwo
     jmp  Again
     fixLvlTwo:
	 InvalidMsgProc ;macro call on time only 
	 inc count
	 jmp  Again

	 Valid:
     mov levelnum, al
	 Decided:
        checktheleveltosendit:
        mov dx,3fDh
      	In al , dx 			
  		AND al , 00100000b
        jz checktheleveltosendit
        mov dx, 3f8h
        mov al,levelnum
        out dx,al
endm DecideLevel


receivethelevelnumfromthefirstuser macro variable
    LOCAL checktheleveltosendthelevel	
        checktheleveltosendthelevel:
        mov dx , 3FDH		; Line Status Register
        in al , dx 
        AND al , 1
        jz checktheleveltosendthelevel
        mov dx,3f8h
        in al,dx
        mov variable,al
endm receivethelevelnumfromthefirstuser

; this macro is used to print the msg invalid number if the user enter invalid number to the level
InvalidMsgProc macro 
	mov dx,offset InvalidMsg
	mov msg,dx
	mov bh,1
	call Write_Not_First_Line
	mov yx,0204h
	call setCursor
endm InvalidMsgProc

; this macro is used to print the msg invalid number if the user enter invalid char to the forbidden
InvalidMsgForbiddenProc macro  
	mov dx,offset InvalidMsgForbidden
	mov msg,dx
	mov bh,1
    call Write_Not_First_Line
	mov yx,0502h
	call setCursor
endm InvalidMsgForbiddenProc 


;prepareForGame proc near   ;To get the forbidden char and level
    ;DecideLevel
   ; ForbiddenChar
;prepareForGame endp

converttostring proc near
push ax
push bx
push cx
push dx
pushf

mov ah, 0
     mov al, regvalues
     mov cl, 16
     div cl
     mov dx, ax  ; higher in dl, lower in dh
     cmp dl, 9
     ja biggerThan
     add dl, 30h
     jmp secondDigit
     biggerThan:
     add dl, 37h 
     secondDigit:
     cmp dh, 9
     ja biggerThan1
     add dh, 30h   
     jmp endConvert
     biggerThan1:
     add dh, 37h
     endConvert:
     ror dx, 8
     mov si, 2
    mov hexaStr[si], dh
    inc si
    mov hexaStr[si], dl

popf
pop dx
pop cx
pop bx
pop ax
ret
converttostring endp

GetInitialValuesToRegs proc near
push ax
push bx
push cx
push dx

    call clearScreen

    mov yx, 0203h
    mov bh, 0
    call setCursor

    mov ah, 9
    mov dx, offset pleaseInitializeRegs
    int 21h

    mov yx, 0403h
    call setCursor

    mov cx, 4
    mov si, 2
    loopLabelRegs:
    mov ah, 0
    int 16H
    cmp al, 39H
    ja checkhex
    cmp al, 30h
    jl loopLabelRegs
    jmp valid
    checkhex:
    cmp al, 41H
    jl loopLabelRegs
    cmp al, 46H
    ja loopLabelRegs
    valid:
    mov hexaString[si], al
    mov ah, 02
    mov dl, al
    int 21h
    inc yx
    call setCursor
    inc si
    loop  loopLabelRegs

pop dx
pop cx
pop bx
pop ax

ret
GetInitialValuesToRegs endp
