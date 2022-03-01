; .MODEL SMALL
; .286
; .STACK 64
; .DATA

; x db 0
; y db 180

; x2 db 180
; y2 db 180

; center dw 15
; center2 dw 195
; tempScore dw 5
; valinCircle dw 6
; key db ?
; ballTimes dw 0
; colorArr db 01h, 02h, 03h, 04h, 05, 06h
; ptsArr db 1h, 2h, 3h, 4h, 5h, 6h

; whichUser db 1
; firstScore dw 50
; secondScore dw 50

; .CODE

; ;x dw 0
; ;y dw 180
; ;center dw 15
; ;tempScore dw 5
; ;valinCircle dw 6
; ;key db ?

SubGame proc near
call uart
push ax
push bx
push cx
push dx
push di
push si
    mov       ax,13h
    int       10h                 ;mode 13h
    push      0a000h
    pop       es
    ; mov bx, 0a00h
    ; mov es, bx   
                    
    mov       dx,200              ;Xc
    mov       di,100              ;Yc

    mov si, ballTimes
    mov       al,colorArr[si]              ;Colour
    mov       bx,10                ;Radius

                    
    call      flying_ball              ;Draw circle

    call scoreHandling

    mov x, 0
    mov y, 180

    mov x2, 180
    mov y2, 180

    mov center, 15
    mov center2, 195  
                    
    cmp ballTimes, 4
    jne increaseBT
    mov ballTimes, 0
    jmp resetBT
    increaseBT:
    inc ballTimes
    resetBT:

pop si
pop di
pop dx
pop cx
pop bx
pop ax
    ret
SubGame endp


;*** Circle
; dx= x coordinate center
; di= y coordinate center
; bx= radius
; al= colour
Circle proc near

        
    call print_in_circle

            mov       bp,0                ;X coordinate
            mov       si,bx               ;Y coordinate
needMorePx:                call      eightPixels            ;Set 8 pixels
            sub       bx,bp               ;D=D-X
            inc       bp                  ;X+1
            sub       bx,bp               ;D=D-(2x+1)
            jg        chckXY              ;no step for Y
            add       bx,si               ;D=D+Y
            dec       si                  ;Y-1
            add       bx,si               ;D=D+(2Y-1)
chckXY:                cmp       si,bp               ;Check X>Y
            jae       needMorePx                 ; Need more pixels
            ret
eightPixels:           call      fourPixels            ;4 pixels
fourPixels:           xchg      bp,si               ;Swap x and y
            call      twoPixels            ;2 pixels
twoPixels:           neg       si
            push      di
            add       di,si
            imul      di, 320
            add       di,dx
            mov       es:[di+bp],al
            sub       di,bp
            stosb
            pop       di
ret
Circle endp


print_in_circle proc near
push ax
push bx
push cx
push dx
push di
push si

        mov ax , dx
        mov cl,8
        div cl

        mov dl,al
        mov ax , di
        mov cl,8
        div cl
        mov dh,al

        mov ah,2
        int 10h

        mov ah,09
        mov si, ballTimes
        mov al, ptsArr[si]
        add al, 30h
        mov cx,1
        mov bl,0fh
        int 10h

pop si
pop di
pop dx
pop cx
pop bx
pop ax
ret
print_in_circle endp


flying_ball proc near
    cmp whichUser, 1
    jnz flytheSecondGuy
    call flying_ball1
    jmp thefirstGuyFlew
    flytheSecondGuy:
    call flying_ball2
    thefirstGuyFlew:
ret
flying_ball endp


flying_ball1 proc near
push ax
push bx
push cx
push dx
push di

    mov cx,20

    fly:

    call eraseCircle
    sub dx, 155
    call eraseCircle

    call EraseRect
    call EraseRect2

    call communicateReceive
    cmp x2,'`'
    jne fixNormalEnd
    jmp normalEnd
    fixNormalEnd:

    traceKey:
    push dx
    push ax
    call getKey
    mov key, ah
    cmp key, 77
    jne checkLeft
    cmp x,146      ;the user will go to the end of the page 
    jae dontMove
    add x, 4
    add center, 4
    call communicateSend
    checkLeft:
    cmp key, 75
    jne checkShooter
    cmp x,0       ;the user will go to the start of the page
    je dontMove
    sub x, 4
    sub center, 4
    call communicateSend
    checkShooter:
    cmp key, 57
    jne dontMove
    call bulletPixel
    ;What happens to the user if he hits or misses
    pop ax
    cmp center, dx
    jne lessButValid
    push di
    mov di, ballTimes
    mov al, ptsArr[di]
    cbw 
    add firstScore, ax               ;TO BE CHANGED (tempScore)
    pop di
    jmp handleDX
    lessButValid:
    sub dx, 10
    cmp center, dx
    jl handleDX
    add dx, 20
    cmp center, dx
    ja handleDX
    push di
    mov di, ballTimes
    mov al, ptsArr[di]
    cbw 
    add firstScore, ax
    pop di
    handleDX:
    pop dx
    jmp shootEnd

    dontMove:
    pop ax
    pop dx

    call DrawRect
    call DrawRect2

    mov dx,cx
    mov bx,10
    call Circle

    push cx
    add cx, 155
    mov dx, cx
    mov bx, 10
    call Circle
    pop cx

    push ax
    push cx
    push dx
    mov ah,86h    ;; Delaaaaaaaaaaaay
    mov cx,0h
    mov dx ,6710h
    int 15h
    pop dx
    pop cx
    pop ax

    
    

    add cx,1
    
    

    cmp cx, 155
    ja dontFly
    jmp fly
    dontFly:
    call DrawRect
    call DrawRect2
    mov bx,10
    mov si, ballTimes
    mov al, colorArr[si]
    call Circle
    jmp normalEnd

    shootEnd:
    call DrawRect
    call DrawRect2
    mov bx,10
    mov si, ballTimes
    mov al, colorArr[si]
    call Circle
    call sendEndSignal

    normalEnd:
    

pop di
pop dx
pop cx
pop bx
pop ax
ret
flying_ball1 endp

flying_ball2 proc near
push ax
push bx
push cx
push dx
push di

    mov cx,20

    fly2:

    call eraseCircle
    sub dx, 155
    call eraseCircle

    call EraseRect2
    call EraseRect

    call communicateReceive
    cmp x,'`'
    jne fixNormalEnd2
    jmp normalEnd2
    fixNormalEnd2:


    traceKey2:
    push dx
    push ax
    call getKey
    mov key, ah
    cmp key, 77
    jne checkLeft2
    cmp x2,252      ;the user will go to the end of the page 
    jae dontMove2
    add x2, 4
    add center2, 4
    call communicateSend
    checkLeft2:
    cmp key, 75
    jne checkShooter2
    cmp x2,180       ;the user will go to the start of the page
    je dontMove2
    sub x2, 4
    sub center2, 4
    call communicateSend
    checkShooter2:
    cmp key, 57
    jne dontMove2
    call bulletPixel2
    ;What happens to the user if he hits or misses
    pop ax
    add dx, 155
    cmp center2, dx
    jne lessButValid2
    push di
    mov di, ballTimes
    mov al, ptsArr[di]
    cbw 
    add secondScore, ax               ;TO BE CHANGED (tempScore)
    pop di
    jmp handleDX2
    lessButValid2:
    sub dx, 10
    cmp center2, dx
    jl handleDX2
    add dx, 20
    cmp center2, dx
    ja handleDX2
    push di
    mov di, ballTimes
    mov al, ptsArr[di]
    cbw 
    add secondScore, ax
    pop di
    handleDX2:
    pop dx
    jmp shootEnd2

    dontMove2:
    pop ax
    pop dx

    call DrawRect2
    call DrawRect

    mov dx,cx
    mov bx,10
    call Circle

    push cx
    add cx, 155
    mov dx, cx
    mov bx, 10
    call Circle
    pop cx

    push ax
    push cx
    push dx
    mov ah,86h    ;; Delaaaaaaaaaaaay
    mov cx,0h
    mov dx ,6710h
    int 15h
    pop dx
    pop cx
    pop ax

    
    

    add cx,1
    
    

    cmp cx, 155
    ja dontFly2
    jmp fly2
    dontFly2:
    call DrawRect
    call DrawRect2
    mov bx,10
    mov si, ballTimes
    mov al, colorArr[si]
    call Circle 
    jmp normalEnd2

    shootEnd2:
    call DrawRect
    call DrawRect2
    mov bx,10
    mov si, ballTimes
    mov al, colorArr[si]
    call Circle

    call sendEndSignal 

    normalEnd2:
     

pop di
pop dx
pop cx
pop bx
pop ax
ret
flying_ball2 endp


DrawRect proc near
    push ax
    push bx
    push cx
    push dx
    push di

    ;Rectangle
    mov bh,0
    mov bl, x
    mov cx, bx
    add bx, 30
    mov dh,0
    mov dl, y
    mov al,4 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    back: int 10h 
    inc cx
    cmp cx,bx
    jnz back
    mov ch,0
    mov cl, x
    dec dx
    cmp dx, 170
    jnz back

    ;Arrow
    mov di, center
    add di, 2       ;x limit of the arrow
    mov bx, 169     ;variable y limit of the arrow
    mov dx, 170
    mov cx, center
    sub cx, 3
    mov al,4 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    loop1x: int 10h
    dec dx
    cmp dx, bx
    jnz loop1x
    mov dx, 170
    inc cx
    cmp cx, di
    jz endloops
    cmp cx, center
    jl upFluxion
    inc bx
    jmp loop1x
    upFluxion:
    dec bx
    jmp loop1x
    endloops:

    
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
ret

DrawRect endp





DrawRect2 proc near
    push ax
    push bx
    push cx
    push dx
    push di

    ;Rectangle
    mov bh,0
    mov bl, x2
    mov cx, bx
    add bx, 30
    mov dh,0
    mov dl, y2
    mov al,4 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    back2: int 10h 
    inc cx
    cmp cx,bx
    jnz back2
    mov ch,0
    mov cl, x2
    dec dx
    cmp dx, 170
    jnz back2

    ;Arrow
    mov di, center2
    add di, 2       ;x limit of the arrow
    mov bx, 169     ;variable y limit of the arrow
    mov dx, 170
    mov cx, center2
    sub cx, 3
    mov al,4 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    loop12x: int 10h
    dec dx
    cmp dx, bx
    jnz loop12x
    mov dx, 170
    inc cx
    cmp cx, di
    jz endloops2
    cmp cx, center2
    jl upFluxion2
    inc bx
    jmp loop12x
    upFluxion2:
    dec bx
    jmp loop12x
    endloops2:

    
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
ret

DrawRect2 endp

EraseRect proc near
    push ax
    push bx
    push cx
    push dx

    ;rect
    mov bh,0
    mov bl, x
    mov cx, bx
    add bx, 30
    mov dh,0
    mov dl, y
    mov al,0 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    back22: int 10h 
    inc cx
    cmp cx,bx
    jnz back22
    mov cl,x
    mov ch, 0
    dec dx
    cmp dx, 165
    jnz back22

    

    pop dx
    pop cx
    pop bx
    pop ax
ret
EraseRect endp


EraseRect2 proc near
    push ax
    push bx
    push cx
    push dx

    ;rect
    mov bh , 0
    mov bl, x2
    mov cx, bx
    add bx, 30
    mov dh,0
    mov dl, y2
    mov al,0 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    back222: int 10h 
    inc cx
    cmp cx,bx
    jnz back222
    mov ch,0
    mov cl, x2
    dec dx
    cmp dx, 165
    jnz back222

    

    pop dx
    pop cx
    pop bx
    pop ax
ret
EraseRect2 endp

eraseCircle proc near
; Remoooooooooooooooove ball
    push ax
    push bx
    push cx
    push dx
    mov bx,6
    mov ax, dx ; git center x pos
    mov cl,8
    div cl    ; get row
    sub al, bl   ; get the higher left point x pos 
    mov dl, al   ; store x value in dl
    mov ax, di  ; get center y pos
    mov cl,8
    div cl    ; get column
    sub al, bl ; get the higher left point y pos
    mov dh, al  ; store y value in dh
    mov cx, dx
    add cx, 0303h
    add dl, bl
    add dh, bl
    add dx, 0101h
    mov bh, 0h
    mov ax, 0600h
    int 10h
    pop dx
    pop cx
    pop bx
    pop ax
    ;///////////

ret
eraseCircle endp

getKey proc near
    mov ah, 01H
    int 16H
    jnz keybdpressed
    mov key, ah
    ret
keybdpressed:
    ;extract the keystroke from the buffer
    mov ah, 00H
    int 16H
    mov key, 0
ret
getKey endp

bulletPixel proc near
    push dx
    mov cx, center
    mov dx, 94
    mov al,6 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    int 10h
    inc cx
    int 10h
    inc dx
    int 10h
    dec cx
    int 10h
    pop dx
ret
bulletPixel endp

bulletPixel2 proc near
    push dx
    mov cx, center2
    mov dx, 94
    mov al,6 ;Pixel color
    mov ah,0ch ;Draw Pixel Command
    int 10h
    inc cx
    int 10h
    inc dx
    int 10h
    dec cx
    int 10h
    pop dx
ret
bulletPixel2 endp

communicateSend proc near
push ax
push bx
push cx
push dx
pushf

    cmp whichUser,1
    jne communicateSend2
    mov dx, 3fdh
    IN al, dx
    AND al, 00100000b
    jz dontSend

    mov dx,3f8h
    mov al,x
    out dx,al 

    communicateSend2:
    mov dx, 3fdh
    IN al, dx
    AND al, 00100000b
    jz dontSend

    mov dx,3f8h
    mov al,x2
    out dx,al 

    
    dontSend:

popf
pop dx
pop cx
pop bx
pop ax

ret
communicateSend endp

communicateReceive proc near
push ax
push bx
push cx
push dx
pushf
    cmp whichUser, 1
    jnz communicateReceive2
    mov dx, 3fdh
    IN al, dx
    AND al, 1
    jz dontReceive
    mov dx,3f8h
    in al,dx
    mov x2,al ;get the second user position
    cmp al, '`'
    je dontReceive
    mov ah, 0
    mov center2, ax
    add center2, 15

    communicateReceive2:
    mov dx, 3fdh
    IN al, dx
    AND al, 1
    jz dontReceive
    mov dx,3f8h
    in al,dx
    mov x,al ;get the second user position
    cmp al, '`'
    je dontReceive
    mov ah, 0
    mov center, ax
    add center, 15

    dontReceive:
popf
pop dx
pop cx
pop bx
pop ax
ret
communicateReceive endp

scoreHandling proc near
    cmp user, 1
    je scenarioOne
    call scoreHandling2
    jmp endScenarioOne
    scenarioOne:
    call scoreHandling1
    endScenarioOne:
ret
scoreHandling endp

scoreHandling1 proc near
    call uart

    cmp whichUser,1
    jnz hanldeScore22
    call receiveScore
    call uart
    call sendScore
    jmp dontDOanythingElse2
    hanldeScore22:
    call uart
    call sendScore
    call uart
    call receiveScore
    

    dontDOanythingElse2:

ret
scoreHandling1 endp

scoreHandling2 proc near
    call uart

    cmp whichUser,1
    jnz hanldeScore2
    call uart
    call sendScore
    call uart
    call receiveScore
    jmp dontDOanythingElse
    hanldeScore2:
    call receiveScore
    call uart
    call sendScore
    

    dontDOanythingElse:

ret
scoreHandling2 endp


sendScore proc near
; ;Resetting the DOS screen
    push ax
    push cx
    push dx
    mov ah,86h    ;; Delaaaaaaaaaaaay
    mov cx,2h
    mov dx ,2710h
    int 15h
    pop dx
    pop cx
    pop ax
    
    cmp whichUser, 1
    jnz takefromsecondScore
    ;Sending
    mov ax, firstScore 
    jmp beginFirstScore
    takefromsecondScore:
    mov ax, secondScore
    beginFirstScore:

    mov cl, al
    AGAINN:  	
    mov dx , 3FDH		; Line Status Register
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAINN
    mov dx, 3f8h
    mov al, ah
    out dx, al
   
    AGAINN2:  	
    mov dx , 3FDH		; Line Status Register
    In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAINN2
    mov dx, 3f8h
    mov al, cl
    out dx, al
    
    ;;;;;;;;;;;;;;;;;;;;;;;;;;

ret
sendScore endp

receiveScore proc near   
    ;Receiving
	getseconduserscore1flyB:	
    mov dx , 3FDH		; Line Status Register
    in al , dx 
  	AND al , 00000001b
  	JZ getseconduserscore1flyB
    mov dx, 3f8h
    in al, dx


    mov ch, al
    getseconduserscore2flyB:	
    mov dx , 3FDH		; Line Status Register
    in al , dx 
  	AND al , 00000001b
  	JZ getseconduserscore2flyB
    mov dx, 3f8h
    in al, dx
    mov cl, al
    
    cmp whichUser, 1
    jz giveToSecondScore
    mov firstScore, cx
    jmp giveToFirstScore
    giveToSecondScore:
    mov secondScore, cx
    giveToFirstScore:
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ret
receiveScore endp


sendEndSignal proc near
push ax
push dx
    mov dx, 3dfh
    chckSendEndSignal:
    in al, dx
    and al, 00100000b
    jz chckSendEndSignal
    mov al, '`'
    mov dx, 3f8h
    out dx, al
pop dx
pop ax
ret
sendEndSignal endp

