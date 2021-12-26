DrawGame macro 
mov ah,0
mov al,13h
int 10h

mov verticalend,144
mov horizotalpostion,19
call drawvertical


mov verticalend,165
mov horizotalpostion,38
call drawvertical


mov verticalend,180
mov horizotalpostion,160
call drawvertical


mov verticalend,144
mov horizotalpostion,301
call drawvertical


mov verticalend,165
mov horizotalpostion,282
call drawvertical

mov endrow,320
mov colnum,144
call drawhorziontal

mov colnum,165
call drawhorziontal

mov colnum,180
call drawhorziontal



mov endrow,36
mov colnum,9
drawcells1:
	call drawhorziontal
	add colnum,9
cmp colnum,144
jnz drawcells1


mov colnum,9
mov endrow,320
mov startrow,284
drawcells2:
	call drawhorziontal
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
;call fillmemocells

mov yx,0036
;call fillmemocells

mov user, 1
mov memolocation, 3
;call fillmemo

mov user, 2
mov memolocation, 3
;call fillmemo


call fillreg









endm DrawGame

;/////////////////////////////////////////////////////////////////
;Memory and Registers
Fillmemo proc near
pusha 
pushf
cmp user,1 
jnz default
mov yx,0000
jmp startfill
default: mov yx,0038
startfill:
mov cl,memolocation
mov dx,yx
add dh,cl
mov yx,dx
mov countmemo, 2
mov si, 0
mov bh, 1
li22:
call setCursor
            mov ah,9
            mov al, memolocationvalue[si]
            mov bh,1
            mov cx,1
            mov bl,0Fh 
            int 10h
			inc yx
			inc si
	dec countmemo
cmp countmemo,0
jnz li22


popf 
popa
ret
endp 


fillmemocells proc near 
pusha
pushf
mov memosize, 16
mov bh,1
mov si,0
li:mov countmemo, 2

li2:call setCursor
            mov ah,9
            mov al, memo[si]
            mov bh,1
            mov cx,1
            mov bl,0Fh 
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
popa
ret
endp
     
fillreg proc near
pusha
pushf
    mov bh, 1  
    mov dh, 7
    mov dl, 10
    mov yx, dx
    label1:
    mov countmemo, 2
    label2:
    mov regSize, 4
    label3:
    call setCursor
            mov ah,9            
            mov al, '0'
            mov bh,1
            mov cx,1
            mov bl,0Fh 
            int 10h
            inc yx
    dec regSize
    jnz label3
    
    mov dl, 15
    mov yx, dx
    dec countmemo
    jnz label2
    mov dl, 10
    add dh, 3
    mov yx, dx
    dec registerscount
    jnz label1
popf
popa
ret
endp





;//////////////////////////////////////////////////////////////////////////////
drawvertical proc near 
pusha
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
popa
ret
endp

drawhorziontal proc near 
pusha
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
popa
ret
endp




drawregsver proc near 
pusha
pushf
mov si,2
loopregs1:
	mov verticalstart,14
	mov verticalend,24
drawregs1:
	call drawvertical
	add verticalend,30
	add verticalstart,30
cmp verticalend,134
jle drawregs1
add horizotalpostion,40
dec si
cmp si,0
jnz loopregs1

popf
popa
ret
endp

drawregshor proc near 
pusha
pushf

drawregshor1:
	call drawhorziontal
	add colnum,30
cmp colnum,124
jle drawregshor1

popf
popa
ret
endp



