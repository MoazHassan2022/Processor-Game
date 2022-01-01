ExecuteWithPower1 proc near 
    push ax 
	push bx
	push cx 
	push dx
    pushf 
    mov al, powerUp1
    cmp al, 0 ; no power up: executing command on second player processor
    je callExecute
    cmp al, 1 ; executing command on first player processor
    je callExecuteOnFirst 
    cmp al, 2 ; executing a command on both processors
    jne fixCallExecuteOnBoth
    jmp callExecuteOnBoth
    fixCallExecuteOnBoth:
    cmp al, 3 ; changing forbiddenChar1
    jne fixChangeForbidden1
    jmp changeForbidden1
    fixChangeForbidden1:     
    cmp al, 4 ; clearing all registers
    jne fixClearAll
    jmp clearAll
    fixClearAll:
    
    
    callExecute:
    mov ah, 1 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral  
	jmp exitExecuteWithPower1
	
	callExecuteOnFirst:
	mov ah, 0 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral
	mov bx, firstScore
	sub bx, 5     ; minus first player 5 points for using this power up
	mov firstScore, bx
	cmp firstScore, 0  ; if lower or equal so player 2 wins
	jbe secondWins1
	jmp exitExecuteWithPower1
	secondWins1:
	mov al, 0    ;/////// There is a player won
	EndGame secondUsername, secondScore ;//////// Second player won
	
	callExecuteOnBoth:
	mov ah, 0 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral
	mov ah, 1
	call ExecuteGeneral
	mov bx, firstScore
	sub bx, 3     ; minus first player 3 points for using this power up
	mov firstScore, bx
	cmp firstScore, 0  ; if lower or equal so player 2 wins
	ja fix2SecondWins1
    jmp secondWins1
    fix2SecondWins1:
	jmp exitExecuteWithPower1  
	
	changeForbidden1:
	mov bh, 1
	mov ah, 07
	int 21h   ; Receive the new char
	mov forbiddenChar1, al 
	mov bx, firstScore
	sub bx, 8     ; minus first player 8 points for using this power up
	mov firstScore, bx
	cmp firstScore, 0  ; if lower or equal so player 2 wins
	ja fix1SecondWins1
    jmp secondWins1
    fix1SecondWins1:
	jmp exitExecuteWithPower1
	
	clearAll:
	mov bx,0     
	mov user, 1
	clearFirstRegisters:
	mov RegistersArray[bx], 0  
	;call updateRegister /////////////////////REDA////////////////////
	inc bx
	cmp bx, 16
	jne clearFirstRegisters
	mov bx,0  
	mov user, 2
	clearSecondRegisters:
	mov RegistersArray2[bx], 0   
	;call updateRegister /////////////////////REDA////////////////////
	inc bx
	cmp bx, 16
	jne clearSecondRegisters
	mov bx, firstScore
	sub bx, 30     ; minus first player 30 points for using this power up
	mov firstScore, bx
	cmp firstScore, 0  ; if lower or equal so player 2 wins
	ja fixSecondWins1
    jmp secondWins1
    fixSecondWins1:
	 
    exitExecuteWithPower1:
	mov user, 2
    popf
    pop dx 
	pop cx 
	pop bx 
	pop ax
    ret
ExecuteWithPower1 endp 

ExecuteWithPower2 proc near 
    push ax 
	push bx 
	push cx 
	push dx
    pushf 
    mov al, powerUp2
    cmp al, 0 ; no power up: executing command on first player processor
    je callExecute2
    cmp al, 1 ; executing command on second player processor
    je callExecuteOnSecond 
    cmp al, 2 ; executing a command on both processors
    jne fixCallExecuteOnBoth2
    jmp callExecuteOnBoth2
    fixCallExecuteOnBoth2:
    cmp al, 3 ; changing forbiddenChar2
    jne fixChangeForbidden2
    jmp changeForbidden2
    fixChangeForbidden2:     
    cmp al, 4 ; clearing all registers
    jne fixClearAll2
    jmp clearAll2
    fixClearAll2:
    
    
    callExecute2:
    mov ah, 0 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral  
	jmp exitExecuteWithPower2
	
	callExecuteOnSecond:
	mov ah, 1 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral
	mov bx, secondScore
	sub bx, 5     ; minus second player 5 points for using this power up
	mov secondScore, bx
	cmp secondScore, 0  ; if lower or equal so player 1 wins
	jbe firstWins1
	jmp exitExecuteWithPower2
	firstWins1:
	mov al, 0    ;/////// There is a player won
	EndGame firstUsername, firstScore ;//////// First player won
	
	callExecuteOnBoth2:
	mov ah, 0 ; to call ExecuteGeneral decide(first person: ah = 0, second person ah = 1) 
	call ExecuteGeneral
	mov ah, 1
	call ExecuteGeneral
	mov bx, secondScore
	sub bx, 3     ; minus second player 3 points for using this power up
	mov secondScore, bx
	cmp secondScore, 0  ; if lower or equal so player 1 wins
	ja fix2FirstWins1
    jmp firstWins1
    fix2FirstWins1:
	jmp exitExecuteWithPower2  
	
	changeForbidden2:
	mov bh, 1
	mov ah, 07
	int 21h   ; Receive the new char
	mov forbiddenChar2, al 
	mov bx, secondScore
	sub bx, 8     ; minus first player 8 points for using this power up
	mov secondScore, bx
	cmp secondScore, 0  ; if lower or equal so player 1 wins
	ja fix1FirstWins1
    jmp firstWins1
    fix1FirstWins1:
	jmp exitExecuteWithPower2
	
	clearAll2:
	mov bx,0   
	mov user, 1
	clearFirstRegisters2:
	mov RegistersArray[bx], 0   
	; call updateRegister ///////////////REDA///////////////
	inc bx
	cmp bx, 16
	jne clearFirstRegisters2
	mov bx,0              
	mov user, 2
	clearSecondRegisters2:
	mov RegistersArray2[bx], 0   
	; call updateRegister ///////////////REDA///////////////
	inc bx
	cmp bx, 16
	jne clearSecondRegisters2
	mov bx, secondScore
	sub bx, 30     ; minus first player 30 points for using this power up
	mov secondScore, bx
	cmp secondScore, 0  ; if lower or equal so player 1 wins
	ja fixFirstWins1
    jmp firstWins1
    fixFirstWins1:
	 
    exitExecuteWithPower2:     
    mov user, 1
    popf
    pop dx 
	pop cx 
	pop bx 
	pop ax
    ret
ExecuteWithPower2 endp

ExecuteGeneral proc near
    push ax 
	push bx 
	push cx 
	push dx
    pushf  ;//////////////Validate from errors////////// 
    
    cmp ah, 1
    jz callExecuteGeneral2
    call ExecuteGeneral1 
    jmp exitExecuteGeneral
    
    callExecuteGeneral2:
    call ExecuteGeneral2
      
    jmp exitExecuteGeneral
    exitExecuteGeneral:
    popf
    pop dx 
	pop cx 
	pop bx 
	pop ax
    ret
ExecuteGeneral endp

ExecuteGeneral1 proc near
    push ax 
	push bx 
	push cx 
	push dx
    pushf
    mov al, instruction     ; ///////////validate memory to memory operation(WRONG!)///////////
    and al, 11000000b   ; getting type 1 in al
    cmp al, 10000000b   ; operand 1 is a memory!
    je mem1
    cmp al, 0         ; validate if reg<al, ah, bl, ....> , reg<ax, bx, cx, dx>
    je reg1
    jmp done1
    mem1:
    mov al, instruction     ; ///////////validate memory to memory operation(WRONG!)///////////
    and al, 00110000b   ; getting type 2 in al
    cmp al, 00100000b   ; operand 2 is a memory! ERROR: Memory to memory operation
    je minus2
    jmp done1 ; no errors, just size mismatch remains
    reg1:
    mov al, instruction
    and al, 00110000b
    cmp al, 0 ; reg, reg
    je fixDone1
    jmp done1
    fixDone1:
    cmp op1, 7 ; if al, ah, bl, .... then it might be error i.e. mov al, bx 
    jbe fix1Done1
    jmp done1
    fix1Done1:
    cmp op2, 7 ; if ax, bx, cx, dx (<=7) the it's error if not continue
    ja fix2Done1
    jmp done1
    fix2Done1: 
    minus2:
    mov dx, secondScore
    dec dx ; minus second player  
    mov secondScore, dx 
    cmp secondScore, 0  ; if lower or equal so player 1 wins
    jbe firstWins2	;////////////////
    ;call receiveInput ;////////////WAER///////////////////
	jmp done1
    firstWins2:
    mov al, 0    ;/////// There is a player won
    EndGame firstUsername, firstScore ;//////// First player won		
    done1:
    call ExecuteInstruction
    exitExecuteGeneral1:
    popf
    pop dx
	pop cx 
	pop bx 
	pop ax
    ret
ExecuteGeneral1 endp

ExecuteGeneral2 proc near
    push ax 
	push bx 
	push cx 
	push dx
    pushf
    mov al, instruction     ; ///////////validate memory to memory operation(WRONG!)///////////
    and al, 11000000b   ; getting type 1 in al
    cmp al, 10000000b   ; operand 1 is a memory!
    je mem2
    cmp al, 0         ; validate if reg<al, ah, bl, ....> , reg<ax, bx, cx, dx>
    je reg2
    jmp done2
    mem2:
    mov al, instruction     ; ///////////validate memory to memory operation(WRONG!)///////////
    and al, 00110000b   ; getting type 2 in al
    cmp al, 00100000b   ; operand 2 is a memory! ERROR: Memory to memory operation
    je minus1
    jmp done2 ; no errors, just size mismatch remains
    reg2:
    mov al, instruction
    and al, 00110000b
    cmp al, 0 ; reg, reg
    je fixDone2
    jmp done2
    fixDone2:
    cmp op1, 7 ; if al, ah, bl, .... then it might be error i.e. mov al, bx 
    jbe fix1Done2
    jmp done2
    fix1Done2:
    cmp op2, 7 ; if ax, bx, cx, dx (<=7) the it's error if not continue
    ja fix2Done2
    jmp done2
    fix2Done2: 
    minus1:
    mov dx, firstScore
    dec dx ; minus first player  
    mov firstScore, dx
    cmp firstScore, 0  ; if lower or equal so player 2 wins
    jbe secondWins2	
	;call receiveInput ;////////////WAER///////////////////
	jmp done2
    secondWins2:
    mov al, 0    ;/////// There is a player won
    EndGame secondUsername, secondScore ;//////// Second player won	
    done2:
    call ExecuteInstruction2
    exitExecuteGeneral2:
    popf
    pop dx 
	pop cx 
	pop bx 
	pop ax
    ret
ExecuteGeneral2 endp
ExecuteInstruction proc near
	push ax 
	push bx 
	push cx 
	push dx
	pushf       
	mov ch, instruction
	and ch, 0Fh ; ch now has 0000xxxx, the lower half byte represents the instruction
	
	cmp ch, 0  ; 0000 is NOP
	jne fixDoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fixDoneLabel:
	INST: 
	mov dh, instruction
	and dh, 11000000b ; get type of operand 1 in dh    
	cmp dh, 0 ; if 0 the operand 1 is a register between ax, bx, cx, dx, al, ah, bl, bh, cl, ch, dl, dh
	je INSTReg1
	cmp dh, 01000000b ; if 1 the operand 1 is a register between SI, DI, SP, BP
	jne fixINSTRegI1
    jmp INSTRegI1
    fixINSTRegI1:
	cmp dh, 10000000b ; if 2 the operand 1 is a memory location
	jne fixINSTMem1
    jmp INSTMem1
    fixINSTMem1:
	
	
	;////////////////////////////////
	
	INSTReg1:
	mov dh, instruction
	and dh, 00110000b ; get type of operand 2 in dh  
	cmp dh, 0 ; if 0 the operand 2 is a register between ax, bx, cx, dx, al, ah, bl, bh, cl, ch, dl, dh
	je INSTReg1Reg2
	cmp dh, 00010000b ; if 1 the operand 2 is a register between SI, DI, SP, BP 
	jne fixINSTReg1RegI2
    jmp INSTReg1RegI2
    fixINSTReg1RegI2:
	cmp dh, 00100000b ; if 2 the operand 2 is a Memory Location 
	jne fixINSTReg1Mem2
    jmp INSTReg1Mem2
    fixINSTReg1Mem2: 
	cmp dh, 00110000b ; if 3 the operand 2 is a Value(16 bit)
	jne fixINSTReg1Val2
	jmp INSTReg1Val2
    fixINSTReg1Val2:

	INSTReg1Reg2:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change ax, bx, cx, dx
	cmp bx, 8   ; mov ax, register
	je INSTAXReg2 
	cmp bx, 9 ; mov bx, register
	je INSTBXReg2 
	cmp bx, 10 ; mov cx, register
	je INSTCXReg2
	cmp bx, 11 ; mov dx, register
	jne fixINSTDXReg2
    jmp INSTDXReg2
    fixINSTDXReg2: 
	mov ah, 0
	mov bx, op2
	mov cl, RegistersArray[bx] ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray or ah = 1 MyMemoryArray ) then call INSTINRegisters1 
	mov bx, op1
	call INSTINRegisters1
	jmp doneLabel
	
	
	INSTAXReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov ax , ax: we will not do anything
	jne fix2DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix2DoneLabel:
	cmp bx, 9 ; mov ax, bx
	jne fixINSTAXBX
    jmp INSTAXBX
    fixINSTAXBX: 
	cmp bx, 10 ; mov ax, cx
	jne fixINSTAXCX
    jmp INSTAXCX
    fixINSTAXCX:
	cmp bx, 11 ; mov ax, dx
	jne fixINSTAXDX
    jmp INSTAXDX
    fixINSTAXDX:
	je fixMinusSize2 ; There is something wrong
    jmp minusSize2
    fixMinusSize2:
	
	INSTBXReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov bx , ax
	jne fixINSTBXAX
    jmp INSTBXAX
    fixINSTBXAX:
	cmp bx, 9 ; mov bx, bx
	jne fix3DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix3DoneLabel: 
	cmp bx, 10 ; mov bx, cx
	jne fixINSTBXCX
    jmp INSTBXAX
    fixINSTBXCX:
	cmp bx, 11 ; mov bx, dx
	jne fixINSTBXDX
    jmp INSTBXDX
    fixINSTBXDX: 
	je fix1MinusSize2 ; There is something wrong
    jmp minusSize2
    fix1MinusSize2:
	
	INSTCXReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov cx , ax
	jne fixINSTCXAX
    jmp INSTCXAX
    fixINSTCXAX:
	cmp bx, 9 ; mov cx, bx
	jne fixINSTCXBX
    jmp INSTCXBX 
    fixINSTCXBX:
	cmp bx, 10 ; mov cx, cx
	jne fix4DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix4DoneLabel:
	cmp bx, 11 ; mov cx, dx
	jne fixINSTCXDX
    jmp INSTCXDX
    fixINSTCXDX: 
	je fix2MinusSize2 ; There is something wrong
    jmp minusSize2
    fix2MinusSize2:
	
	INSTDXReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov dx , ax
	jne fixINSTDXAX
    jmp INSTDXAX
    fixINSTDXAX:
	cmp bx, 9 ; mov dx, bx
	jne fixINSTDXBX
    jmp INSTDXBX
    fixINSTDXBX: 
	cmp bx, 10 ; mov dx, cx
	jne fixINSTDXCX
    jmp INSTDXCX
    fixINSTDXCX:
	cmp bx, 11 ; mov dx, dx
	jne fix5DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix5DoneLabel: 
	je fix3MinusSize2 ; There is something wrong
    jmp minusSize2
    fix3MinusSize2:
	
	INSTAXBX:
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[2]
	mov ch, RegistersArray[3]
	call INSTINRegisters
	jmp doneLabel
	 
	INSTAXCX:
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[4]
	mov ch, RegistersArray[5]
	call INSTINRegisters
	jmp doneLabel
	
	INSTAXDX:  
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[6]
	mov ch, RegistersArray[7]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXAX:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[0]
	mov ch, RegistersArray[1]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXCX:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[4]
	mov ch, RegistersArray[5]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXDX:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[6]
	mov ch, RegistersArray[7]
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXAX: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[0]
	mov ch, RegistersArray[1]
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXBX: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[2]
	mov ch, RegistersArray[3]
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXDX:
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[6]
	mov ch, RegistersArray[7]
	call INSTINRegisters
	jmp doneLabel    
	
	INSTDXAX:    
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[0]
	mov ch, RegistersArray[1]
	call INSTINRegisters
	jmp doneLabel 
	
	INSTDXBX:
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[2]
	mov ch, RegistersArray[3]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDXCX: 
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[4]
	mov ch, RegistersArray[5]
	call INSTINRegisters
	jmp doneLabel 
	
	;;///////////////////////////////
	
	INSTReg1RegI2:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change ax, bx, cx, dx
	cmp bx, 8   ; mov ax, SI OR DI OR SP OR BP
	je INSTAXRegI2 
	cmp bx, 9 ; mov bx, SI OR DI OR SP OR BP
	je INSTBXRegI2 
	cmp bx, 10 ; mov cx, SI OR DI OR SP OR BP
	je INSTCXRegI2
	cmp bx, 11 ; mov dx, SI OR DI OR SP OR BP
	jne fixINSTDXRegI2
    jmp INSTDXRegI2
    fixINSTDXRegI2:
	je fix4MinusSize2 ; There is something wrong
    jmp minusSize2
    fix4MinusSize2:
	
	
	INSTAXRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov ax, SI
	jne fixINSTAXSI
    jmp INSTAXSI
    fixINSTAXSI:
	cmp bx, 1 ; mov ax, DI
	jne fixINSTAXDI
    jmp INSTAXDI
    fixINSTAXDI: 
	cmp bx, 2 ; mov ax, SP
	jne fixINSTAXSP
    jmp INSTAXSP
    fixINSTAXSP:
	cmp bx, 3 ; mov ax, BP
	jne fixINSTAXBP
    jmp INSTAXBP
    fixINSTAXBP:
	je fix5MinusSize2 ; There is something wrong
    jmp minusSize2
    fix5MinusSize2:
	
	INSTBXRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov bx , SI
	jne fixINSTBXSI
    jmp INSTBXSI
    fixINSTBXSI:
	cmp bx, 1 ; mov bx, DI
	jne fixINSTBXDI
    jmp INSTBXDI
    fixINSTBXDI: 
	cmp bx, 2 ; mov bx, SP
	jne fixINSTBXSP
    jmp INSTBXSP
    fixINSTBXSP:
	cmp bx, 3 ; mov bx, BP
	jne fixINSTBXBP
    jmp INSTBXBP
    fixINSTBXBP: 
	je fix6MinusSize2 ; There is something wrong
    jmp minusSize2
    fix6MinusSize2:
	
	INSTCXRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov cx , SI
	jne fixINSTCXSI
    jmp INSTCXSI
    fixINSTCXSI:
	cmp bx, 1 ; mov cx, DI
	jne fixINSTCXDI
    jmp INSTCXDI
    fixINSTCXDI: 
	cmp bx, 2 ; mov cx, SP
	jne fixINSTCXSP
    jmp INSTCXSP
    fixINSTCXSP:
	cmp bx, 3 ; mov cx, BP
	jne fixINSTCXBP
    jmp INSTCXBP
    fixINSTCXBP: 
	je fix7MinusSize2 ; There is something wrong
    jmp minusSize2
    fix7MinusSize2:
	
	INSTDXRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov dx , SI
	jne fixINSTDXSI
    jmp INSTDXSI
    fixINSTDXSI:
	cmp bx, 1 ; mov dx, DI
	jne fixINSTDXDI
    jmp INSTDXDI
    fixINSTDXDI: 
	cmp bx, 2 ; mov dx, SP
	jne fixINSTDXSP
    jmp INSTDXSP
    fixINSTDXSP:
	cmp bx, 3 ; mov dx, BP
	jne fixINSTDXBP
    jmp INSTDXBP
    fixINSTDXBP: 
	je fix8MinusSize2 ; There is something wrong
    jmp minusSize2
    fix8MinusSize2:
	
	INSTAXSI:    
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[8]
	mov ch, RegistersArray[9]
	call INSTINRegisters
	jmp doneLabel
	 
	INSTAXDI:    
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[10]
	mov ch, RegistersArray[11]
	call INSTINRegisters
	jmp doneLabel
	
	INSTAXSP:
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[12]
	mov ch, RegistersArray[13]
	call INSTINRegisters
	jmp doneLabel
	
	INSTAXBP: 
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[14]
	mov ch, RegistersArray[15]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXSI:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[8]
	mov ch, RegistersArray[9]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXDI:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[10]
	mov ch, RegistersArray[11]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXSP:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[12]
	mov ch, RegistersArray[13]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXBP:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[14]
	mov ch, RegistersArray[15]
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXSI:    
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[8]
	mov ch, RegistersArray[9]
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXDI:
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[10]
	mov ch, RegistersArray[11]
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXSP: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[12]
	mov ch, RegistersArray[13]
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXBP: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[14]
	mov ch, RegistersArray[15]
	call INSTINRegisters
	jmp doneLabel    
	
	INSTDXSI: 
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[8]
	mov ch, RegistersArray[9]
	call INSTINRegisters
	jmp doneLabel 
	
	INSTDXDI: 
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[10]
	mov ch, RegistersArray[11]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDXSP:   
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[12]
	mov ch, RegistersArray[13]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDXBP:
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[14]
	mov ch, RegistersArray[15]
	call INSTINRegisters
	jmp doneLabel
	
	;///////////////////////////////// 
	
	INSTReg1Mem2:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change ax, bx, cx, dx(WRONG!!)
	cmp bx, 7
	jbe fix9MinusSize2 ; size mismatch error
    jmp minusSize2
    fix9MinusSize2:
	mov ah, 0
	mov bx, op2
	mov cl, RegistersArray[bx] ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray or ah = 1 MyMemoryArray ) then call INSTINRegisters1 
	mov bx, op1
	call INSTINRegisters1
	jmp doneLabel
	
	;/////////////////////////////////
	
	INSTReg1Val2: 
	mov bx, op1 ; get op1 in bx to know size of register to put the value in
	cmp bx, 7
	ja TwoBytes ; this means he will put in (ax or bx or cx or dx)
	mov bx, op2
	cmp bx, 0FFh ; this means size mismatch (2 bytes in 1 byte)
	jbe fix10MinusSize2 ; size mismatch error
    jmp minusSize2
    fix10MinusSize2:
	mov ah, 0 
	mov cl, bl ; get Lower byte of the Value
	mov bx, op1 ; get the register to put in
	call INSTINRegisters1   ; ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray or ah = 1 MyMemoryArray ) then call INSTINRegisters1
	jmp doneLabel
	
	TwoBytes: 
	cmp bx, 8 ; mov ax, value
	je INSTAXVal
	cmp bx, 9 ; mov bx, value
	je INSTBXVal
	cmp bx, 10 ; mov cx, value
	je INSTCXVal 
	mov cx, op2 ; inst dx, value
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	call INSTINRegisters
	jmp doneLabel
	
	INSTAXVal:
	mov cx, op2 
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	call INSTINRegisters
	jmp doneLabel
	
	INSTBXVal: 
	mov cx, op2 
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	call INSTINRegisters
	jmp doneLabel
	
	INSTCXVal: 
	mov cx, op2 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	call INSTINRegisters
	jmp doneLabel
	
	;///////////////////////////////// 
	
	INSTMem1: 
	mov dh, instruction
	and dh, 00110000b ; get type of operand 2 in dh  
	cmp dh, 00110000b ; if 3 then operand 2 is a value
	je  INSTMem1Val2
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get value from ax, bx, cx, dx(WRONG!)
	cmp bx, 7
	jbe fix11MinusSize2 ; size mismatch error
    jmp minusSize2
    fix11MinusSize2:
	mov ah, 1
	mov cl, RegistersArray[bx] ; get value of chosen register(al,ah,bl,bh,cl,ch,dl,dh)
	mov bx, op1 ; put the value in memory location chosen(BYTE); to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray or ah = 1 MyMemoryArray ) then call INSTINRegisters1 
	call INSTINRegisters1
	jmp doneLabel
	
	;/////////////////////////////////
	
	INSTMem1Val2: 
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get value from 2 byte(WRONG!)
	cmp bx, 0ffh ; bigger than 1 byte(WRONG!)
	jbe fix12MinusSize2 ; size mismatch error
    jmp minusSize2
    fix12MinusSize2:
	mov ah, 1
	mov cl, bl ; get value in al(1 byte)
	mov bx, op1 ; get memory location 
	call INSTINRegisters1 ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray or ah = 1 MyMemoryArray ) then call INSTINRegisters1
	jmp doneLabel 
	
	;/////////////////////////////////
	
	INSTRegI1:
	mov dh, instruction
	and dh, 00110000b ; get type of operand 2 in dh  
	cmp dh, 0         ; if 0 the operand 2 is a register(ax or bx or cx or dx)
	je INSTRegI1Reg2
	cmp dh, 00010000b ; if 1 the operand 2 is a register(SI or DI or SP or BP)
	jne fixINSTRegI1RegI2
    jmp INSTRegI1RegI2
    fixINSTRegI1RegI2:
	cmp dh, 00110000b ; if 3 the operand 2 is a value
	jne fixINSTRegI1Val
    jmp INSTRegI1Val
    fixINSTRegI1Val:
	 
	
	
	;/////////////////////////////////
	INSTRegI1Reg2:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change SI, DI, SP, BP
	cmp bx, 0   ; mov SI, register
	je INSTSIReg2 
	cmp bx, 1 ; mov DI, register
	je INSTDIReg2 
	cmp bx, 2 ; mov SP, register
	je INSTSPReg2
	cmp bx, 3 ; mov BP, register
	jne fixINSTBPReg2
    jmp INSTBPReg2
    fixINSTBPReg2:
	je fix13MinusSize2 ; There is something wrong
	jmp minusSize2
    fix13MinusSize2:
	
	INSTSIReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov SI , ax
	jne fixINSTSIAX
    jmp INSTSIAX
    fixINSTSIAX:
	cmp bx, 9 ; mov SI, bx
	jne fixINSTSIBX
    jmp INSTSIBX
    fixINSTSIBX: 
	cmp bx, 10 ; mov SI, cx
	jne fixINSTSICX
    jmp INSTSICX
    fixINSTSICX:
	cmp bx, 11 ; mov SI, dx
	jne fixINSTSIDX
    jmp INSTSIDX
    fixINSTSIDX:
	je fix14MinusSize2 ; There is something wrong
	jmp minusSize2
    fix14MinusSize2:
	
	INSTDIReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov DI , ax
	jne fixINSTDIAX
    jmp INSTDIAX
    fixINSTDIAX:
	cmp bx, 9 ; mov DI, bx
	jne fixINSTDIBX
    jmp INSTDIBX
    fixINSTDIBX: 
	cmp bx, 10 ; mov DI, cx
	jne fixINSTDICX
    jmp INSTDICX
    fixINSTDICX:
	cmp bx, 11 ; mov DI, dx
	jne fixINSTDIDX
    jmp INSTDIDX
    fixINSTDIDX: 
	je fix15MinusSize2 ; There is something wrong
	jmp minusSize2
    fix15MinusSize2:
	
	INSTSPReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov SP , ax
	jne fixINSTSPAX
    jmp INSTSPAX
    fixINSTSPAX:
	cmp bx, 9 ; mov SP, bx
	jne fixINSTSPBX
    jmp INSTSPBX
    fixINSTSPBX: 
	cmp bx, 10 ; mov SP, cx
	jne fixINSTSPCX
    jmp INSTSPCX
    fixINSTSPCX:
	cmp bx, 11 ; mov SP, dx
	jne fixINSTSPDX
    jmp INSTSPDX
    fixINSTSPDX: 
	je fix16MinusSize2 ; There is something wrong
	jmp minusSize2
    fix16MinusSize2:
	
	INSTBPReg2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov BP , ax
	jne fixINSTBPAX
    jmp INSTBPAX
    fixINSTBPAX:
	cmp bx, 9 ; mov BP, bx
	jne fixINSTBPBX
    jmp INSTBPBX
    fixINSTBPBX: 
	cmp bx, 10 ; mov BP, cx
	jne fixINSTBPCX
    jmp INSTBPCX
    fixINSTBPCX:
	cmp bx, 11 ; mov BP, dx
	jne fixINSTBPDX
    jmp INSTBPDX
    fixINSTBPDX: 
	je fix17MinusSize2 ; There is something wrong
	jmp minusSize2
    fix17MinusSize2:
	
	INSTSIAX: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[0]
	mov ch, RegistersArray[1]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSIBX: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[2]
	mov ch, RegistersArray[3]
	call INSTINRegisters
	jmp doneLabel
	 
	INSTSICX:
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[4]
	mov ch, RegistersArray[5]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSIDX: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[6]
	mov ch, RegistersArray[7]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDIAX: 
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[0]
	mov ch, RegistersArray[1]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDIBX:
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[2]
	mov ch, RegistersArray[3]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDICX: 
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[4]
	mov ch, RegistersArray[5]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDIDX:     
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[6]
	mov ch, RegistersArray[7]
	call INSTINRegisters
	jmp doneLabel 
	
	INSTSPAX:
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[0]
	mov ch, RegistersArray[1]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSPBX:
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[2]
	mov ch, RegistersArray[3]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSPCX:  
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[4]
	mov ch, RegistersArray[5]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSPDX:
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[6]
	mov ch, RegistersArray[7]
	call INSTINRegisters
	jmp doneLabel     
	
	INSTBPAX:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[0]
	mov ch, RegistersArray[1]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBPBX:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[2]
	mov ch, RegistersArray[3]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBPCX:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[4]
	mov ch, RegistersArray[5]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBPDX:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[6]
	mov ch, RegistersArray[7]
	call INSTINRegisters
	jmp doneLabel
	
	;////////////////////////////////////// 
	
	INSTRegI1RegI2:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change SI, DI, SP, BP
	cmp bx, 0   ; mov SI, SI OR DI OR SP OR BP
	je INSTSIRegI2 
	cmp bx, 1 ; mov DI, SI OR DI OR SP OR BP
	je INSTDIRegI2 
	cmp bx, 2 ; mov SP, SI OR DI OR SP OR BP
	je INSTSPRegI2
	cmp bx, 3 ; mov BP, SI OR DI OR SP OR BP
	jne fixINSTBPRegI2
    jmp INSTBPRegI2
    fixINSTBPRegI2:
	je fix18MinusSize2 ; There is something wrong
	jmp minusSize2
    fix18MinusSize2:
	
	
	INSTSIRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov SI , SI
	jne fix6DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix6DoneLabel:
	cmp bx, 1 ; mov SI, DI
	jne fixINSTSIDI
    jmp INSTSIDI
    fixINSTSIDI: 
	cmp bx, 2 ; mov SI, SP
	jne fixINSTSISP
    jmp INSTSISP
    fixINSTSISP:
	cmp bx, 3 ; mov SI, BP
	jne fixINSTSIBP
    jmp INSTSIBP
    fixINSTSIBP:
	je fix19MinusSize2 ; There is something wrong
	jmp minusSize2
    fix19MinusSize2:
	
	INSTDIRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov DI , SI
	jne fixINSTDISI
    jmp INSTDISI
    fixINSTDISI:
	cmp bx, 1 ; mov DI, DI
	jne fix7DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix7DoneLabel:
	cmp bx, 2 ; mov DI, SP
	jne fixINSTDISP
    jmp INSTDISP
    fixINSTDISP:
	cmp bx, 3 ; mov DI, BP
	jne fixINSTDIBP
    jmp INSTDIBP
    fixINSTDIBP: 
	je fix20MinusSize2 ; There is something wrong
	jmp minusSize2
    fix20MinusSize2:
	
	INSTSPRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov SP , SI
	jne fixINSTSPSI
    jmp INSTSPSI
    fixINSTSPSI:
	cmp bx, 1 ; mov SP, DI
	jne fixINSTSPDI
    jmp INSTSPDI
    fixINSTSPDI: 
	cmp bx, 2 ; mov SP, SP
	jne fix8DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix8DoneLabel:
	cmp bx, 3 ; mov SP, BP
	jne fixINSTSPBP
    jmp INSTSPBP
    fixINSTSPBP: 
	je fix21MinusSize2 ; There is something wrong
	jmp minusSize2
    fix21MinusSize2:
	
	INSTBPRegI2:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov BP , SI
	jne fixINSTBPSI
    jmp INSTBPSI
    fixINSTBPSI:
	cmp bx, 1 ; mov BP, DI
	jne fixINSTBPDI
    jmp INSTBPDI
    fixINSTBPDI: 
	cmp bx, 2 ; mov BP, SP
	jne fixINSTBPSP
    jmp INSTBPSP
    fixINSTBPSP:
	cmp bx, 3 ; mov BP, BP
	jne fix9DoneLabel ; Simply Don't do anything :) 
	jmp doneLabel
    fix9DoneLabel:          	
	je fix22MinusSize2 ; There is something wrong
	jmp minusSize2
    fix22MinusSize2:
	
	INSTSIDI: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[10]
	mov ch, RegistersArray[11]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSISP:          
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[12]
	mov ch, RegistersArray[13]
	call INSTINRegisters
	jmp doneLabel
	 
	INSTSIBP:    
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[14]
	mov ch, RegistersArray[15]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDISI:    
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[8]
	mov ch, RegistersArray[9]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDISP: 
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[12]
	mov ch, RegistersArray[13]
	call INSTINRegisters
	jmp doneLabel
	
	INSTDIBP:    
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[14]
	mov ch, RegistersArray[15]
	call INSTINRegisters
	jmp doneLabel 
	
	INSTSPSI:    
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[8]
	mov ch, RegistersArray[9]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSPDI:           
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[10]
	mov ch, RegistersArray[11]
	call INSTINRegisters
	jmp doneLabel
	
	INSTSPBP:  
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[14]
	mov ch, RegistersArray[15]
	call INSTINRegisters
	jmp doneLabel  
	
	INSTBPSI:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[8]
	mov ch, RegistersArray[9]
	call INSTINRegisters
	jmp doneLabel 
	
	INSTBPDI: 
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[10]
	mov ch, RegistersArray[11]
	call INSTINRegisters
	jmp doneLabel
	
	INSTBPSP:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cl, RegistersArray[12]
	mov ch, RegistersArray[13]
	call INSTINRegisters
	jmp doneLabel 
	
	;////////////////////////////////////// 
	
	INSTRegI1Val:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change SI, DI, SP, BP
	cmp bx, 0   ; mov SI, Value
	je INSTSIVal 
	cmp bx, 1 ; mov DI, Value
	je INSTDIVal 
	cmp bx, 2 ; mov SP, Value
	je INSTSPVal 
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cx, op2 ; get value in cx
	call INSTINRegisters
	jmp doneLabel 
	
	INSTSIVal:   
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cx, op2 ; get value in cx
	call INSTINRegisters
	jmp doneLabel
	
	INSTDIVal:   
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cx, op2 ; get value in cx
	call INSTINRegisters
	jmp doneLabel
	
	INSTSPVal:   
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters
	mov cx, op2 ; get value in cx
	call INSTINRegisters
	jmp doneLabel
	
	;//////////////////////////////////////
	
	
	
	minusSize2:
	mov dx, secondScore
    dec dx ; minus second player  
    mov secondScore, dx
    cmp secondScore, 0  ; if lower or equal so player 1 wins
    jbe firstWins3
	;call receiveInput ;////////////WAER///////////////////  
    firstWins3:
    mov al, 0    ;/////// There is a player won
    EndGame firstUsername, firstScore ;//////// First player won
	
	doneLabel: 
	xor user, 00000011b  ; toggle user: if user 1 make it user 2 and vice virsa

	
	exit:   
	popf
	pop dx 
	pop cx 
	pop bx 
	pop ax
	ret
ExecuteInstruction endp	

;//////////////////////////////////

INSTINRegisters proc near 
	push ax 
	push bx 
	push cx 
	push dx
	pushf
	push bx
	mov dh, bh ; keep the higher address
	mov bh, 0  ; Now getting value from lower address in dl 
	mov dl, RegistersArray[bx] 
	mov bl, dh ; Now getting value from higher address in dh
	mov dh, RegistersArray[bx] ; now we have the value of the place to store in, in dx 
	mov al, instruction
	and al, 0fh ; getting instruction code(lower 4 bits)
	cmp al, 1h ; add
	je  addINST
	cmp al, 2h ; adc
	je  adcINST
	cmp al, 3h ; sub
	jne fixSubINST
    jmp subINST
    fixSubINST:
	cmp al, 4h ; sbb
	jne fixSbbINST
    jmp sbbINST
    fixSbbINST:      
	cmp al, 5h ; mov
	jne fixMovINST
    jmp movINST
    fixMovINST:  
	cmp al, 6h ; xor
	jne fixXorINST
    jmp xorINST
    fixXorINST: 
	cmp al, 7h ; and
	jne fixAndINST
    jmp andINST
    fixAndINST: 
	cmp al, 8h ; or
	jne fixOrINST
    jmp orINST
    fixOrINST:
	cmp al, 9h ; shr
	jne fixShrINST
    jmp shrINST
    fixShrINST:
	cmp al, 0ah ; shl
	jne fixShlINST
    jmp shlINST 
    fixShlINST: 
	cmp al, 0bh ; sar
	jne fixSarINST
    jmp sarINST
    fixSarINST:   
	cmp al, 0ch ; ror
	jne  fixRorINST
    jmp rcrINST
    fixRorINST:     
	cmp al, 0dh ; rcl
	jne  fixRclINST
    jmp rclINST
    fixRclINST:    
	cmp al, 0eh ; rcr
	jne fixRcrINST
    jmp rcrINST
    fixRcrINST:
	cmp al, 0fh ; rol
	jne  fixRolINST
    jmp rolINST
    fixRolINST:
	
	je fixExitINSTINRegisters 
    jmp exitINSTINRegisters
    fixExitINSTINRegisters:
	
	addINST:
	add dx, cx
	jnc  fix5SetCarry
    jmp setCarry
    fix5SetCarry: 
	jc fix5DisSetCarry
    jmp disSetCarry
    fix5DisSetCarry:  
	
	adcINST:
	cmp carryFlag, 1
	je setCAdc
	add dx, cx
	jnc  fix4SetCarry
    jmp setCarry
    fix4SetCarry: 
	jc fix4DisSetCarry
    jmp disSetCarry
    fix4DisSetCarry:  
	setCAdc:
	stc
	adc dx, cx
	jnc  fix3SetCarry
    jmp setCarry
    fix3SetCarry: 
	jc fix3DisSetCarry
    jmp disSetCarry
    fix3DisSetCarry:  
	
	subINST:
	sub dx, cx
	jnc  fix2SetCarry
    jmp setCarry
    fix2SetCarry: 
	jc fix2DisSetCarry
    jmp disSetCarry
    fix2DisSetCarry: 
	
	sbbINST:
	cmp carryFlag, 1
	je setCSbb
	sub dx, cx
	jnc  fix1SetCarry
    jmp setCarry
    fix1SetCarry: 
	jc fix1DisSetCarry
    jmp disSetCarry
    fix1DisSetCarry: 
	setCSbb:
	stc
	sbb dx, cx
	jnc  fixSetCarry
    jmp setCarry
    fixSetCarry: 
	jc fixDisSetCarry
    jmp disSetCarry
    fixDisSetCarry:  
	
	movINST:
	pop bx
	mov dh, bh ; keep the higher address
	mov bh, 0  ; Now storing in lower address 
	mov RegistersArray[bx], cl 
	;call updateRegister ;//////////////////REDA///////////////
	mov bl, dh ; Now storing in higher address
	mov RegistersArray[bx], ch 
	;call updateRegister ;//////////////////REDA///////////////
	cmp cx, 0105eh ; if yes then player 2 wins
	je secondWins4
	jmp exitINSTINRegisters
	secondWins4:
        mov al, 0    ;/////// There is a player won
        EndGame secondUsername, secondScore ;//////// Second player won
	
	xorINST:
	xor dx, cx 
	jmp disSetCarry ; xor: makes carry flag = 0  
	
	andINST:
	and dx, cx 
	jmp disSetCarry ; and: makes carry flag = 0
	 
	orINST:
	or dx, cx 
	jmp disSetCarry ; or: makes carry flag = 0  
	
	shrINST:
	shr dx, cl ; shr: shift with just cl
	jc  setCarry
	jnc disSetCarry       
	
	shlINST:
	shl dx, cl ; shl: shift with just cl
	jc  setCarry
	jnc disSetCarry 
	
	sarINST:
	sar dx, cl ; sar: shift with just cl
	jc  setCarry
	jnc disSetCarry
	
	rorINST:
	ror dx, cl ; ror: rotate with just cl
	jc  setCarry
	jnc disSetCarry 
	
	rclINST:   
	cmp carryFlag, 1
	je setCRcl
	rcl dx, cl ; rcl: rotate with just cl
	jc  setCarry
	jnc disSetCarry 
	setCRcl:
	stc
	rcl dx, cl ; rcl: rotate with just cl
	jc  setCarry 
	jnc disSetCarry
	
	rcrINST: 
	cmp carryFlag, 1
	je setCRcr
	rcr dx, cl ; rcr: rotate with just cl
	jc  setCarry
	jnc disSetCarry
	setCRcr:
	stc
	rcr dx, cl ; rcr: rotate with just cl
	jc  setCarry 
	jnc disSetCarry 
	
	rolINST:
	rol dx, cl ; rol: rotate with just cl
	jc  setCarry
	jnc disSetCarry
	
	
	
	setCarry:
	mov carryFlag, 1
	jmp store
	disSetCarry:
	mov carryFlag, 0
	store:
	; Now store new values 
	pop bx
	mov ch, bh ; keep the higher address
	mov bh, 0  ; Now storing in lower address 
	mov RegistersArray[bx], dl  
	;call updateRegister ;//////////////////REDA///////////////
	mov bl, ch ; Now storing in higher address
	mov RegistersArray[bx], dh       
	;call updateRegister ;//////////////////REDA///////////////
	cmp dx, 0105eh ; if yes then player 2 wins
	jne fixSecondWins4
    jmp secondWins4
    fixSecondWins4:
	exitINSTINRegisters:
	popf
	pop dx 
	pop cx 
	pop bx 
	pop ax 
ret   
INSTINRegisters endp

INSTINRegisters2 proc near 
	push ax 
	push bx 
	push cx 
	push dx
	pushf
	push bx
	mov dh, bh ; keep the higher address
	mov bh, 0  ; Now getting value from lower address in dl 
	mov dl, RegistersArray2[bx] 
	mov bl, dh ; Now getting value from higher address in dh
	mov dh, RegistersArray2[bx] ; now we have the value of the place to store in, in dx 
	mov al, instruction
	and al, 0fh ; getting instruction code(lower 4 bits)
	cmp al, 1h ; add
	je  addINST2
	cmp al, 2h ; adc
	je  adcINST2 
	cmp al, 3h ; sub
	jne fixSubINST2
    jmp subINST2
    fixSubINST2:
	cmp al, 4h ; sbb
	jne fixSbbINST2
    jmp sbbINST2  
    fixSbbINST2:    
	cmp al, 5h ; mov
	jne fixMovINST2
    jmp movINST2
    fixMovINST2:  
	cmp al, 6h ; xor
	jne fixXorINST2
    jmp xorINST2
    fixXorINST2: 
	cmp al, 7h ; and
	jne fixAndINST2
    jmp andINST2
    fixAndINST2: 
	cmp al, 8h ; or
	jne fixOrINST2
    jmp orINST2
    fixOrINST2:
	cmp al, 9h ; shr
	jne fixShrINST2
    jmp shrINST2
    fixShrINST2:
	cmp al, 0ah ; shl
	jne fixShlINST2
    jmp shlINST2
    fixShlINST2:  
	cmp al, 0bh ; sar
	jne fixSarINST2
    jmp sarINST2
    fixSarINST2:   
	cmp al, 0ch ; ror
	jne fixRorINST2
    jmp rorINST2
    fixRorINST2:     
	cmp al, 0dh ; rcl
	jne fixRclINST2
    jmp rclINST2
    fixRclINST2:    
	cmp al, 0eh ; rcr
	jne fixRcrINST2
    jmp rcrINST2
    fixRcrINST2: 
	cmp al, 0fh ; rol
	jne fixRolINST2
    jmp rolINST2
    fixRolINST2:
	
	je fixExitINSTINRegisters2 
    jmp exitINSTINRegisters2
    fixExitINSTINRegisters2:
	
	addINST2:
	add dx, cx
	jnc fix6SetCarry2
    jmp setCarry2
    fix6SetCarry2: 
	jc fix6DisSetCarry2
    jmp disSetCarry2
    fix6DisSetCarry2: 
	
	adcINST2:
	cmp carryFlag2, 1
	je setCAdc2
	add dx, cx
	jnc fix5SetCarry2
    jmp setCarry2
    fix5SetCarry2: 
	jc fix5DisSetCarry2
    jmp disSetCarry2
    fix5DisSetCarry2: 
	setCAdc2:
	stc
	adc dx, cx
	jnc fix4SetCarry2
    jmp setCarry2
    fix4SetCarry2: 
	jc fix4DisSetCarry2
    jmp disSetCarry2
    fix4DisSetCarry2:  
	
	subINST2:
	sub dx, cx
	jnc fix3SetCarry2
    jmp setCarry2
    fix3SetCarry2: 
	jc fix3DisSetCarry2
    jmp disSetCarry2
    fix3DisSetCarry2: 
	
	sbbINST2:
	cmp carryFlag2, 1
	je setCSbb2
	sub dx, cx
	jnc  fix2SetCarry2
    jmp setCarry2
    fix2SetCarry2: 
	jc fix2DisSetCarry2
    jmp disSetCarry2
    fix2DisSetCarry2:  
	setCSbb2:
	stc
	sbb dx, cx
	jnc  fixSetCarry2
    jmp setCarry2
    fixSetCarry2: 
	jc fixDisSetCarry2
    jmp disSetCarry2
    fixDisSetCarry2:  
	
	movINST2:
	pop bx
	mov dh, bh ; keep the higher address
	mov bh, 0  ; Now storing in lower address 
	mov RegistersArray2[bx], cl    
	;call updateRegister ;//////////////////REDA///////////////
	mov bl, dh ; Now storing in higher address
	mov RegistersArray2[bx], ch   
	;call updateRegister ;//////////////////REDA///////////////
	cmp cx, 0105eh ; if yes then player 1 wins
	je firstWins4
	jmp exitINSTINRegisters2
	firstWins4:
	mov al, 0    ;/////// There is a player won
        EndGame firstUsername, firstScore ;//////// First player won
	
	xorINST2:
	xor dx, cx 
	jmp disSetCarry2 ; xor: makes carry flag = 0  
	
	andINST2:
	and dx, cx 
	jmp disSetCarry2 ; and: makes carry flag = 0
	 
	orINST2:
	or dx, cx 
	jmp disSetCarry2 ; or: makes carry flag = 0  
	
	shrINST2:
	shr dx, cl ; shr: shift with just cl
	jc  setCarry2
	jnc disSetCarry2       
	
	shlINST2:
	shl dx, cl ; shl: shift with just cl
	jc  setCarry2
	jnc disSetCarry2 
	
	sarINST2:
	sar dx, cl ; sar: shift with just cl
	jc  setCarry2
	jnc disSetCarry2
	
	rorINST2:
	ror dx, cl ; ror: rotate with just cl
	jc  setCarry2
	jnc disSetCarry2 
	
	rclINST2:   
	cmp carryFlag2, 1
	je setCRcl2
	rcl dx, cl ; rcl: rotate with just cl
	jc  setCarry2
	jnc disSetCarry2 
	setCRcl2:
	stc
	rcl dx, cl ; rcl: rotate with just cl
	jc  setCarry2 
	jnc disSetCarry2
	
	rcrINST2: 
	cmp carryFlag2, 1
	je setCRcr2
	rcr dx, cl ; rcr: rotate with just cl
	jc  setCarry2
	jnc disSetCarry2
	setCRcr2:
	stc
	rcr dx, cl ; rcr: rotate with just cl
	jc  setCarry2 
	jnc disSetCarry2 
	
	rolINST2:
	rol dx, cl ; rol: rotate with just cl
	jc  setCarry2
	jnc disSetCarry2
	
	
	
	setCarry2:
	mov carryFlag2, 1
	jmp store2
	disSetCarry2:
	mov carryFlag2, 0
	store2:
	; Now store new values 
	pop bx
	mov ch, bh ; keep the higher address
	mov bh, 0  ; Now storing in lower address 
	mov RegistersArray2[bx], dl 
	;call updateRegister ;//////////////////REDA///////////////
	mov bl, ch ; Now storing in higher address
	mov RegistersArray2[bx], dh                                
	;call updateRegister ;//////////////////REDA///////////////
	cmp dx, 0105eh
	jne fixFirstWins4
    jmp firstWins4
    fixFirstWins4:
	exitINSTINRegisters2:
	popf
	pop dx 
	pop cx 
	pop bx 
	pop ax 
ret   
INSTINRegisters2 endp                

;//////////////////////////

INSTINRegisters1 proc near 
	push ax 
	push bx 
	push cx 
	push dx
	pushf 
	mov bh, 0 ; we have only one address so no need to bh value
	push bx 
	cmp ah, 1
	je takeMem
	mov dl, RegistersArray[bx] ; Now getting value from lower address in dl  
	jmp contINSTINRegisters1
	takeMem: 
	mov dl, MyMemoryArray[bx] ; Now getting value from lower address in dl  
	contINSTINRegisters1:
	mov al, instruction
	and al, 0fh ; getting instruction code(lower 4 bits)
	cmp al, 1h ; add
	je  addINST1
	cmp al, 2h ; adc
	je  adcINST1
	cmp al, 3h ; sub
	jne fixSubINST1
    jmp subINST1
    fixSubINST1:
	cmp al, 4h ; sbb
	jne fixSbbINST1
    jmp sbbINST1
    fixSbbINST1:      
	cmp al, 5h ; mov
	jne fixMovINST1
    jmp movINST1
    fixMovINST1:  
	cmp al, 6h ; xor
	jne fixXorINST1
    jmp xorINST1
    fixXorINST1: 
	cmp al, 7h ; and
	jne fixAndINST1
    jmp andINST1
    fixAndINST1: 
	cmp al, 8h ; or
	jne fixOrINST1
    jmp orINST1
    fixOrINST1:
	cmp al, 9h ; shr
	jne fixShrINST1
    jmp shrINST1
    fixShrINST1:
	cmp al, 0ah ; shl
	jne fixShlINST1
    jmp shlINST1 
    fixShlINST1: 
	cmp al, 0bh ; sar
	jne fixSarINST1
    jmp sarINST1
    fixSarINST1:   
	cmp al, 0ch ; ror
	jne fixRorINST1
    jmp rorINST1
    fixRorINST1:     
	cmp al, 0dh ; rcl
	jne fixRclINST1  
    jmp rclINST1
    fixRclINST1:  
	cmp al, 0eh ; rcr
	jne fixRcrINST1
    jmp rcrINST1
    fixRcrINST1: 
	cmp al, 0fh ; rol
	jne fixRolINST1
    jmp rolINST1
    fixRolINST1:
	
	je fixExitINSTINRegisters1 
    jmp exitINSTINRegisters1
    fixExitINSTINRegisters1:
	
	addINST1:
	add dl, cl
	jnc fix5SetCarry1
    jmp setCarry1
    fix5SetCarry1: 
	jc fix5DisSetCarry1
    jmp disSetCarry1
    fix5DisSetCarry1: 
	
	adcINST1:
	cmp carryFlag, 1
	je setCAdc1
	add dl, cl
	jnc fix4SetCarry1
    jmp setCarry1
    fix4SetCarry1: 
	jc fix4DisSetCarry1
    jmp disSetCarry1
    fix4DisSetCarry1: 
	setCAdc1:
	stc
	adc dl, cl
	jnc fix3SetCarry1
    jmp setCarry1
    fix3SetCarry1: 
	jc fix3DisSetCarry1
    jmp disSetCarry1
    fix3DisSetCarry1: 
	
	subINST1:
	sub dl, cl
	jnc fix2SetCarry1
    jmp setCarry1
    fix2SetCarry1: 
	jc fix2DisSetCarry1
    jmp disSetCarry1
    fix2DisSetCarry1:
	
	sbbINST1:
	cmp carryFlag, 1
	je setCSbb1
	sub dl, cl
	jnc fix1SetCarry1
    jmp setCarry1
    fix1SetCarry1: 
	jc fix1DisSetCarry1
    jmp disSetCarry1
    fix1DisSetCarry1: 
	setCSbb1:
	stc
	sbb dl, cl
	jnc fixSetCarry1
    jmp setCarry1
    fixSetCarry1: 
	jc fixDisSetCarry1
    jmp disSetCarry1
    fixDisSetCarry1:  
	
	movINST1:
	pop bx 
	cmp ah, 1
	jne fixMovINSTMem
    jmp movINSTMem
    fixMovINSTMem:   
	mov RegistersArray[bx], cl ; Now storing in lower address 
	;call updateRegister ;//////////////////REDA///////////////
	mov ah, 0
	mov al, bl ; now AX has the address of storing place
	mov ch, 2
	div ch
	cmp ah, 0  ; if yes so this is even(al or bl or cl or dl), no so this is odd(ah or bh or ch or dh)
	jne fixEvenAddress
    jmp evenAddress
    fixEvenAddress:
	dec bx 
	mov ch, RegistersArray[bx]  ; get the lower
	ror cx, 8   ; now cl has the lower and ch has the higher
	cmp cx, 0105eh  ; if yes then player 2 wins
	je secondWins5
	jmp exitINSTINRegisters1
	secondWins5:
	mov ah, 0  ; There is a player won
	EndGame secondUsername, secondScore ; player 2 won
	evenAddress: 
	inc bx
	mov ch, RegistersArray[bx]  ; get the higher // now cx has the value
	cmp cx, 0105eh ; if yes player 2 wins
	jne fix2SecondWins5
    jmp secondWins5
    fix2SecondWins5:
	jmp exitINSTINRegisters1

	movINSTMem:
	mov MyMemoryArray[bx], cl ; Now storing in lower address   
	;call updateMemory ;//////////////////REDA///////////////
	jmp exitINSTINRegisters1
	
	xorINST1:
	xor dl, cl 
	jmp disSetCarry1 ; xor: makes carry flag = 0  
	
	andINST1:
	and dl, cl 
	jmp disSetCarry1 ; and: makes carry flag = 0
	 
	orINST1:
	or dl, cl 
	jmp disSetCarry1 ; or: makes carry flag = 0  
	
	shrINST1:
	shr dl, cl ; shr: shift with just cl
	jc  setCarry1
	jnc disSetCarry1       
	
	shlINST1:
	shl dl, cl ; shl: shift with just cl
	jc  setCarry1
	jnc disSetCarry1 
	
	sarINST1:
	sar dl, cl ; sar: shift with just cl
	jc  setCarry1
	jnc disSetCarry1
	
	rorINST1:
	ror dl, cl ; ror: rotate with just cl
	jc  setCarry1
	jnc disSetCarry1 
	
	rclINST1:   
	cmp carryFlag, 1
	je setCRcl1
	rcl dl, cl ; rcl: rotate with just cl
	jc  setCarry1
	jnc disSetCarry1 
	setCRcl1:
	stc
	rcl dl, cl ; rcl: rotate with just cl
	jc  setCarry1 
	jnc disSetCarry1
	
	rcrINST1: 
	cmp carryFlag, 1
	je setCRcr1
	rcr dl, cl ; rcr: rotate with just cl
	jc  setCarry1
	jnc disSetCarry1
	setCRcr1:
	stc
	rcr dl, cl ; rcr: rotate with just cl
	jc  setCarry1 
	jnc disSetCarry1 
	
	rolINST1:
	rol dl, cl ; rol: rotate with just cl
	jc  setCarry1
	jnc disSetCarry1
	
	
	
	setCarry1:
	mov carryFlag, 1
	jmp store1
	disSetCarry1:
	mov carryFlag, 0
	store1: 
	pop bx  ; Now store new values
	cmp ah, 1 ; if 1 store in memory 
	je storeMem
	mov RegistersArray[bx], dl ; Now storing in lower address  
	;call updateRegister ;//////////////////REDA///////////////
	mov ah, 0
	mov al, bl ; now AX has the address of storing place
	mov ch, 2
	div ch
	cmp ah, 0  ; if yes so this is even(al or bl or cl or dl), no so this is odd(ah or bh or ch or dh)
	je evenAddress1
	dec bx 
	mov dh, RegistersArray[bx]  ; get the lower
	ror dx, 8   ; now dl has the lower and dh has the higher
	cmp dx, 0105eh  ; if yes then player 2 wins
	jne fix1SecondWins5
    jmp secondWins5
    fix1SecondWins5:
	jmp exitINSTINRegisters1
	evenAddress1: 
	inc bx
	mov dh, RegistersArray[bx]  ; get the higher // now dx has the value
	cmp dx, 0105eh ; if yes player 2 wins
	jne fixSecondWins5
    jmp secondWins5
    fixSecondWins5:
	jmp exitINSTINRegisters1
	storeMem:
	mov MyMemoryArray[bx], dl ; Now storing in lower address 
	;call updateMemory ;//////////////////REDA///////////////
	exitINSTINRegisters1:
	popf
	pop dx 
	pop cx 
	pop bx 
	pop ax 
ret
INSTINRegisters1 endp 

INSTINRegisters12 proc near 
	push ax 
	push bx 
	push cx 
	push dx
	pushf 
	mov bh, 0 ; we have only one address so no need to bh value
	push bx 
	cmp ah, 1
	je takeMem2
	mov dl, RegistersArray2[bx] ; Now getting value from lower address in dl  
	jmp contINSTINRegisters12
	takeMem2: 
	mov dl, MyMemoryArray2[bx] ; Now getting value from lower address in dl  
	contINSTINRegisters12:
	mov al, instruction
	and al, 0fh ; getting instruction code(lower 4 bits)
	cmp al, 1h ; add
	je  addINST12
	cmp al, 2h ; adc
	je  adcINST12
	cmp al, 3h ; sub
	jne fixSubINST12
    jmp subINST12
    fixSubINST12:
	cmp al, 4h ; sbb
	jne fixSbbINST12
    jmp sbbINST12
    fixSbbINST12:      
	cmp al, 5h ; mov
	jne fixMovINST12
    jmp movINST12
    fixMovINST12:  
	cmp al, 6h ; xor
	jne fixXorINST12
    jmp xorINST12
    fixXorINST12: 
	cmp al, 7h ; and
	jne fixAndINST12
    jmp andINST12
    fixAndINST12: 
	cmp al, 8h ; or
	jne fixOrINST12
    jmp orINST12
    fixOrINST12:
	cmp al, 9h ; shr
	jne fixShrINST12
    jmp shrINST12
    fixShrINST12:
	cmp al, 0ah ; shl
	jne fixShlINST12
    jmp shlINST12
    fixShlINST12:  
	cmp al, 0bh ; sar
	jne fixSarINST12
    jmp sarINST12
    fixSarINST12:   
	cmp al, 0ch ; ror
	jne fixRorINST12
    jmp rorINST12
    fixRorINST12:     
	cmp al, 0dh ; rcl
	jne fixRclINST12
    jmp rclINST12
    fixRclINST12:    
	cmp al, 0eh ; rcr
	jne fixRcrINST12
    jmp rcrINST12
    fixRcrINST12: 
	cmp al, 0fh ; rol
	jne fixRolINST12
    jmp rolINST12
    fixRolINST12:
	
	je fixExitINSTINRegisters12
    jmp exitINSTINRegisters12
    fixExitINSTINRegisters12: 
	
	addINST12:
	add dl, cl
	jnc fix5SetCarry12
    jmp setCarry12
    fix5SetCarry12: 
	jc fix5DisSetCarry12
    jmp disSetCarry12
    fix5DisSetCarry12: 
	
	adcINST12:
	cmp carryFlag2, 1
	je setCAdc12
	add dl, cl
	jnc fix4SetCarry12
    jmp setCarry12
    fix4SetCarry12: 
	jc fix4DisSetCarry12
    jmp disSetCarry12
    fix4DisSetCarry12: 
	setCAdc12:
	stc
	adc dl, cl
	jnc fix3SetCarry12
    jmp setCarry12
    fix3SetCarry12: 
	jc fix3DisSetCarry12
    jmp disSetCarry12
    fix3DisSetCarry12: 
	
	subINST12:
	sub dl, cl
	jnc fix2SetCarry12
    jmp setCarry12
    fix2SetCarry12: 
	jc fix2DisSetCarry12
    jmp disSetCarry12
    fix2DisSetCarry12:
	
	sbbINST12:
	cmp carryFlag2, 1
	je setCSbb12
	sub dl, cl
	jnc fix1SetCarry12
    jmp setCarry12
    fix1SetCarry12: 
	jc fix1DisSetCarry12
    jmp disSetCarry12
    fix1DisSetCarry12:
	setCSbb12:
	stc
	sbb dl, cl
	jnc fixSetCarry12
    jmp setCarry12
    fixSetCarry12: 
	jc fixDisSetCarry12
    jmp disSetCarry12
    fixDisSetCarry12:  
	
	movINST12:
	pop bx 
	cmp ah, 1
	jne fixMovINSTMem2
    jmp movINSTMem2
    fixMovINSTMem2:   
	mov RegistersArray2[bx], cl ; Now storing in lower address
	;call updateRegister ;//////////////////REDA/////////////// 
	mov ah, 0
	mov al, bl ; now AX has the address of storing place
	mov ch, 2
	div ch
	cmp ah, 0  ; if yes so this is even(al or bl or cl or dl), no so this is odd(ah or bh or ch or dh)
	jne fixEvenAddress2
    jmp evenAddress2
    fixEvenAddress2:
	dec bx 
	mov ch, RegistersArray2[bx]  ; get the lower
	ror cx, 8   ; now cl has the lower and ch has the higher
	cmp cx, 0105eh  ; if yes then player 1 wins
	je firstWins5
	jmp exitINSTINRegisters12
	firstWins5:
	mov ah, 0  ; There is a player won
	EndGame firstUsername, firstScore ; player 1 won
	evenAddress2: 
	inc bx
	mov ch, RegistersArray2[bx]  ; get the higher // now cx has the value
	cmp cx, 0105eh ; if yes player 1 wins
	jne fix2FirstWins5
    jmp firstWins5
    fix2FirstWins5:
	jmp exitINSTINRegisters12
	
	movINSTMem2:
	mov MyMemoryArray2[bx], cl ; Now storing in lower address 
	;call updateMemory ;//////////////////REDA///////////////
	jmp exitINSTINRegisters12
	
	xorINST12:
	xor dl, cl 
	jmp disSetCarry12 ; xor: makes carry flag = 0  
	
	andINST12:
	and dl, cl 
	jmp disSetCarry12 ; and: makes carry flag = 0
	 
	orINST12:
	or dl, cl 
	jmp disSetCarry12 ; or: makes carry flag = 0  
	
	shrINST12:
	shr dl, cl ; shr: shift with just cl
	jc  setCarry12
	jnc disSetCarry12       
	
	shlINST12:
	shl dl, cl ; shl: shift with just cl
	jc  setCarry12
	jnc disSetCarry12 
	
	sarINST12:
	sar dl, cl ; sar: shift with just cl
	jc  setCarry12
	jnc disSetCarry12
	
	rorINST12:
	ror dl, cl ; ror: rotate with just cl
	jc  setCarry12
	jnc disSetCarry12 
	
	rclINST12:   
	cmp carryFlag2, 1
	je setCRcl12
	rcl dl, cl ; rcl: rotate with just cl
	jc  setCarry12
	jnc disSetCarry12 
	setCRcl12:
	stc
	rcl dl, cl ; rcl: rotate with just cl
	jc  setCarry12 
	jnc disSetCarry12
	
	rcrINST12: 
	cmp carryFlag2, 1
	je setCRcr12
	rcr dl, cl ; rcr: rotate with just cl
	jc  setCarry12
	jnc disSetCarry12
	setCRcr12:
	stc
	rcr dl, cl ; rcr: rotate with just cl
	jc  setCarry12 
	jnc disSetCarry12 
	
	rolINST12:
	rol dl, cl ; rol: rotate with just cl
	jc  setCarry12
	jnc disSetCarry12
	
	
	
	setCarry12:
	mov carryFlag2, 1
	jmp store12
	disSetCarry12:
	mov carryFlag2, 0
	store12: 
	pop bx  ; Now store new values
	cmp ah, 1 ; if 1 store in memory 
	je storeMem2
	mov RegistersArray2[bx], dl ; Now storing in lower address
	;call updateRegister ;//////////////////REDA/////////////// 
	mov ah, 0
	mov al, bl ; now AX has the address of storing place
	mov ch, 2
	div ch
	cmp ah, 0  ; if yes so this is even(al or bl or cl or dl), no so this is odd(ah or bh or ch or dh)
	je evenAddress3
	dec bx 
	mov dh, RegistersArray2[bx]  ; get the lower
	ror dx, 8   ; now dl has the lower and dh has the higher
	cmp dx, 0105eh  ; if yes then player 1 wins
	jne fix1FirstWins5
    jmp firstWins5
    fix1FirstWins5:
	jmp exitINSTINRegisters12
	evenAddress3: 
	inc bx
	mov dh, RegistersArray2[bx]  ; get the higher // now dx has the value
	cmp dx, 0105eh ; if yes player 1 wins
	jne fixFirstWins5
    jmp firstWins5
    fixFirstWins5:
	jmp exitINSTINRegisters12
	storeMem2:
	mov MyMemoryArray2[bx], dl ; Now storing in lower address
	;call updateMemory ;//////////////////REDA///////////////
	exitINSTINRegisters12:
	popf
	pop dx 
	pop cx 
	pop bx 
	pop ax 
ret
INSTINRegisters12 endp

;////////////////////////////

ExecuteInstruction2 proc near
	push ax 
	push bx 
	push cx 
	push dx
	pushf       
	mov ch, instruction
	and ch, 0Fh ; ch now has 0000xxxx, the lower half byte represents the instruction
	
	cmp ch, 0  ; 0000 is NOP
	jne fixDoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fixDoneLabel2:
	
	INST1: 
	mov dh, instruction
	and dh, 11000000b ; get type of operand 1 in dh    
	cmp dh, 0 ; if 0 the operand 1 is a register between ax, bx, cx, dx, al, ah, bl, bh, cl, ch, dl, dh
	je INSTReg12
	cmp dh, 01000000b ; if 1 the operand 1 is a register between SI, DI, SP, BP
	jne fixINSTRegI12
    jmp INSTRegI12
    fixINSTRegI12:
	cmp dh, 10000000b ; if 2 the operand 1 is a memory location
	jne fixINSTMem12
    jmp INSTMem12
    fixINSTMem12:
	
	
	;////////////////////////////////
	
	INSTReg12:
	mov dh, instruction
	and dh, 00110000b ; get type of operand 2 in dh  
	cmp dh, 0 ; if 0 the operand 2 is a register between ax, bx, cx, dx, al, ah, bl, bh, cl, ch, dl, dh
	je INSTReg12Reg22
	cmp dh, 00010000b ; if 1 the operand 2 is a register between SI, DI, SP, BP 
	jne fixINSTReg12RegI22
    jmp INSTReg12RegI22
    fixINSTReg12RegI22:
	cmp dh, 00100000b ; if 2 the operand 2 is a Memory Location 
	jne fixINSTReg12Mem22
    jmp INSTReg12Mem22
    fixINSTReg12Mem22: 
	cmp dh, 00110000b ; if 3 the operand 2 is a Value(16 bit)
	jne fixINSTReg12Val22
    jmp INSTReg12Val22
    fixINSTReg12Val22:
	
	INSTReg12Reg22:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change ax, bx, cx, dx
	cmp bx, 8   ; mov ax, register
	je INSTAX2Reg22 
	cmp bx, 9 ; mov bx, register
	je INSTBX2Reg22 
	cmp bx, 10 ; mov cx, register
	je INSTCX2Reg22
	cmp bx, 11 ; mov dx, register
	jne fixINSTDX2Reg22
    jmp INSTDX2Reg22
    fixINSTDX2Reg22: 
	mov ah, 0
	mov bx, op2
	mov cl, RegistersArray2[bx] ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray2 or ah = 1 MyMemoryArray ) then call INSTINRegisters12 
	mov bx, op1
	call INSTINRegisters12
	jmp doneLabel2
	
	
	INSTAX2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov ax , ax: we will not do anything
	jne fix1DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix1DoneLabel2:
	cmp bx, 9 ; mov ax, bx
	jne fixINSTAX2BX2
    jmp INSTAX2BX2
    fixINSTAX2BX2: 
	cmp bx, 10 ; mov ax, cx
	jne fixINSTAX2CX2
    jmp INSTAX2CX2
    fixINSTAX2CX2:
	cmp bx, 11 ; mov ax, dx
	jne fixINSTAX2DX2
    jmp INSTAX2DX2
    fixINSTAX2DX2:
	je fixMinusSize1 ; size mismatch error
    jmp minusSize1
    fixMinusSize1:
	
	INSTBX2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov bx , ax
	jne fixINSTBX2AX2
    jmp INSTBX2AX2
    fixINSTBX2AX2:
	cmp bx, 9 ; mov bx, bx
	jne fix2DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix2DoneLabel2:
	cmp bx, 10 ; mov bx, cx
	jne fixINSTBX2CX2
    jmp INSTBX2CX2
    fixINSTBX2CX2:
	cmp bx, 11 ; mov bx, dx
	jne fixINSTBX2DX2
    jmp INSTBX2DX2
    fixINSTBX2DX2: 
	je fix1MinusSize1 ; size mismatch error
    jmp minusSize1
    fix1MinusSize1:
	
	INSTCX2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov cx , ax
	jne fixINSTCX2AX2
    jmp INSTCX2AX2
    fixINSTCX2AX2:
	cmp bx, 9 ; mov cx, bx
	jne fixINSTCX2BX2
    jmp INSTCX2BX2
    fixINSTCX2BX2: 
	cmp bx, 10 ; mov cx, cx
	jne fix3DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix3DoneLabel2:
	cmp bx, 11 ; mov cx, dx
	jne fixINSTCX2DX2
    jmp INSTCX2DX2
    fixINSTCX2DX2: 
	je fix2MinusSize1 ; size mismatch error
    jmp minusSize1
    fix2MinusSize1:
	
	INSTDX2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov dx , ax
	jne fixINSTDX2AX2
    jmp INSTDX2AX2
    fixINSTDX2AX2:
	cmp bx, 9 ; mov dx, bx
	jne fixINSTDX2BX2
    jmp INSTDX2BX2
    fixINSTDX2BX2: 
	cmp bx, 10 ; mov dx, cx
	jne fixINSTDX2CX2
    jmp INSTDX2CX2
    fixINSTDX2CX2:
	cmp bx, 11 ; mov dx, dx
	jne fix4DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix4DoneLabel2: 
	je fix3MinusSize1 ; size mismatch error
    jmp minusSize1
    fix3MinusSize1:
	
	INSTAX2BX2:
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[2]
	mov ch, RegistersArray2[3]
	call INSTINRegisters2
	jmp doneLabel2
	 
	INSTAX2CX2:
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[4]
	mov ch, RegistersArray2[5]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTAX2DX2:  
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[6]
	mov ch, RegistersArray2[7]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2AX2:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[0]
	mov ch, RegistersArray2[1]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2CX2:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[4]
	mov ch, RegistersArray2[5]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2DX2:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[6]
	mov ch, RegistersArray2[7]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2AX2: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[0]
	mov ch, RegistersArray2[1]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2BX2: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[2]
	mov ch, RegistersArray2[3]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2DX2:
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[6]
	mov ch, RegistersArray2[7]
	call INSTINRegisters2
	jmp doneLabel2    
	
	INSTDX2AX2:    
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[0]
	mov ch, RegistersArray2[1]
	call INSTINRegisters2
	jmp doneLabel2 
	
	INSTDX2BX2:
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[2]
	mov ch, RegistersArray2[3]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDX2CX2: 
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[4]
	mov ch, RegistersArray2[5]
	call INSTINRegisters2
	jmp doneLabel2 
	
	;;///////////////////////////////
	
	INSTReg12RegI22:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change ax, bx, cx, dx
	cmp bx, 8   ; mov ax, SI OR DI OR SP OR BP
	je INSTAX2RegI22 
	cmp bx, 9 ; mov bx, SI OR DI OR SP OR BP
	je INSTBX2RegI22 
	cmp bx, 10 ; mov cx, SI OR DI OR SP OR BP
	je INSTCX2RegI22
	cmp bx, 11 ; mov dx, SI OR DI OR SP OR BP
	jne fixINSTDX2RegI22
    jmp INSTDX2RegI22
    fixINSTDX2RegI22:
	je fix4MinusSize1 ; size mismatch error
    jmp minusSize1
    fix4MinusSize1:
	
	
	INSTAX2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov ax, SI
	jne fixINSTAX2SI2
    jmp INSTAX2SI2
    fixINSTAX2SI2:
	cmp bx, 1 ; mov ax, DI
	jne fixINSTAX2DI2
    jmp INSTAX2DI2
    fixINSTAX2DI2: 
	cmp bx, 2 ; mov ax, SP
	jne fixINSTAX2SP2
    jmp INSTAX2SP2
    fixINSTAX2SP2:
	cmp bx, 3 ; mov ax, BP
	jne fixINSTAX2BP2
    jmp INSTAX2BP2
    fixINSTAX2BP2:
	je fix5MinusSize1 ; There is something wrong
    jmp minusSize1
    fix5MinusSize1:
	
	INSTBX2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov bx , SI
	jne fixINSTBX2SI2
    jmp INSTBX2SI2
    fixINSTBX2SI2:
	cmp bx, 1 ; mov bx, DI
	jne fixINSTBX2DI2
    jmp INSTBX2DI2
    fixINSTBX2DI2: 
	cmp bx, 2 ; mov bx, SP
	jne fixINSTBX2SP2
    jmp INSTBX2SP2
    fixINSTBX2SP2:
	cmp bx, 3 ; mov bx, BP
	jne fixINSTBX2BP2
    jmp INSTBX2BP2
    fixINSTBX2BP2: 
	je fix6MinusSize1 ; There is something wrong
    jmp minusSize1
    fix6MinusSize1:
	
	INSTCX2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov cx , SI
	jne fixINSTCX2SI2
    jmp INSTCX2SI2
    fixINSTCX2SI2:
	cmp bx, 1 ; mov cx, DI
	jne fixINSTCX2DI2
    jmp INSTCX2DI2
    fixINSTCX2DI2: 
	cmp bx, 2 ; mov cx, SP
	jne fixINSTCX2SP2
    jmp INSTCX2SP2
    fixINSTCX2SP2:
	cmp bx, 3 ; mov cx, BP
	jne fixINSTCX2BP2
    jmp INSTCX2BP2
    fixINSTCX2BP2: 
	je fix7MinusSize1 ; There is something wrong
    jmp minusSize1
    fix7MinusSize1:
	
	INSTDX2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov dx , SI
	jne fixINSTDX2SI2
    jmp INSTDX2SI2
    fixINSTDX2SI2:
	cmp bx, 1 ; mov dx, DI
	jne fixINSTDX2DI2 
    jmp INSTDX2DI2
    fixINSTDX2DI2:
	cmp bx, 2 ; mov dx, SP
	jne fixINSTDX2SP2
    jmp INSTDX2SP2
    fixINSTDX2SP2:
	cmp bx, 3 ; mov dx, BP
	jne fixINSTDX2BP2
    jmp INSTDX2BP2
    fixINSTDX2BP2: 
	je fix8MinusSize1 ; There is something wrong
    jmp minusSize1
    fix8MinusSize1:
	
	INSTAX2SI2:    
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[8]
	mov ch, RegistersArray2[9]
	call INSTINRegisters2
	jmp doneLabel2
	 
	INSTAX2DI2:    
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[10]
	mov ch, RegistersArray2[11]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTAX2SP2:
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[12]
	mov ch, RegistersArray2[13]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTAX2BP2: 
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[14]
	mov ch, RegistersArray2[15]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2SI2:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[8]
	mov ch, RegistersArray2[9]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2DI2:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[10]
	mov ch, RegistersArray2[11]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2SP2:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[12]
	mov ch, RegistersArray2[13]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2BP2:
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[14]
	mov ch, RegistersArray2[15]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2SI2:    
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[8]
	mov ch, RegistersArray2[9]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2DI2:
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[10]
	mov ch, RegistersArray2[11]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2SP2: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[12]
	mov ch, RegistersArray2[13]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2BP2: 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[14]
	mov ch, RegistersArray2[15]
	call INSTINRegisters2
	jmp doneLabel2    
	
	INSTDX2SI2: 
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[8]
	mov ch, RegistersArray2[9]
	call INSTINRegisters2
	jmp doneLabel2 
	
	INSTDX2DI2: 
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[10]
	mov ch, RegistersArray2[11]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDX2SP2:   
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[12]
	mov ch, RegistersArray2[13]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDX2BP2:
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[14]
	mov ch, RegistersArray2[15]
	call INSTINRegisters2
	jmp doneLabel2
	
	;///////////////////////////////// 
	
	INSTReg12Mem22:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change ax, bx, cx, dx(WRONG!!)
	cmp bx, 7
	jbe fix9MinusSize1 ; size mismatch error
    jmp minusSize1
    fix9MinusSize1:
	mov ah, 0
	mov bx, op2
	mov cl, RegistersArray2[bx] ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray2 or ah = 1 MyMemoryArray ) then call INSTINRegisters12 
	mov bx, op1
	call INSTINRegisters12
	jmp doneLabel2
	
	;/////////////////////////////////
	
	INSTReg12Val22: 
	mov bx, op1 ; get op1 in bx to know size of register to put the value in
	cmp bx, 7
	ja TwoBytes2 ; this means he will put in (ax or bx or cx or dx)
	mov bx, op2
	cmp bx, 0FFh ; this means size mismatch (2 bytes in 1 byte)
	jbe fix10MinusSize1 ; size mismatch error
    jmp minusSize1
    fix10MinusSize1:
	mov ah, 0 
	mov cl, bl ; get Lower byte of the Value
	mov bx, op1 ; get the register to put in
	call INSTINRegisters12   ; ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray2 or ah = 1 MyMemoryArray ) then call INSTINRegisters12
	jmp doneLabel2
	
	TwoBytes2: 
	cmp bx, 8 ; mov ax, value
	je INSTAX2Val2
	cmp bx, 9 ; mov bx, value
	je INSTBX2Val2
	cmp bx, 10 ; mov cx, value
	je INSTCX2Val2 
	mov cx, op2 ; INST1 dx, value
	mov bx, 0706h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTAX2Val2:
	mov cx, op2 
	mov bx, 0100h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBX2Val2: 
	mov cx, op2 
	mov bx, 0302h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTCX2Val2: 
	mov cx, op2 
	mov bx, 0504h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	call INSTINRegisters2
	jmp doneLabel2
	
	;///////////////////////////////// 
	
	INSTMem12: 
	mov dh, instruction
	and dh, 00110000b ; get type of operand 2 in dh  
	cmp dh, 00110000b ; if 3 then operand 2 is a value
	je  INSTMem12Val22
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get value from ax, bx, cx, dx(WRONG!)
	cmp bx, 7
	jbe fix11MinusSize1 ; size mismatch error
    jmp minusSize1
    fix11MinusSize1:
	mov ah, 1
	mov cl, RegistersArray2[bx] ; get value of chosen register(al,ah,bl,bh,cl,ch,dl,dh)
	mov bx, op1 ; put the value in memory location chosen(BYTE); to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray2 or ah = 1 MyMemoryArray ) then call INSTINRegisters12 
	call INSTINRegisters12
	jmp doneLabel2
	
	;/////////////////////////////////
	
	INSTMem12Val22: 
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get value from 2 byte(WRONG!)
	cmp bx, 0ffh ; bigger than 1 byte(WRONG!)
	jbe fix12MinusSize1 ; size mismatch error
    jmp minusSize1
    fix12MinusSize1:
	mov ah, 1
	mov cl, bl ; get value in al(1 byte)
	mov bx, op1 ; get memory location 
	call INSTINRegisters12 ; to execute instruction put the addresses in bx and values in cl and which to process with( ah = 0 RegistersArray2 or ah = 1 MyMemoryArray ) then call INSTINRegisters12
	jmp doneLabel2 
	
	;/////////////////////////////////
	
	INSTRegI12:
	mov dh, instruction
	and dh, 00110000b ; get type of operand 2 in dh  
	cmp dh, 0         ; if 0 the operand 2 is a register(ax or bx or cx or dx)
	je INSTRegI12Reg22
	cmp dh, 00010000b ; if 1 the operand 2 is a register(SI or DI or SP or BP)
	jne fixINSTRegI12RegI22
    jmp INSTRegI12RegI22
    fixINSTRegI12RegI22:
	cmp dh, 00110000b ; if 3 the operand 2 is a value
	jne fixINSTRegI12Val2
    jmp INSTRegI12Val2
    fixINSTRegI12Val2:
	 
	
	
	;/////////////////////////////////
	INSTRegI12Reg22:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change SI, DI, SP, BP
	cmp bx, 0   ; mov SI, register
	je INSTSI2Reg22 
	cmp bx, 1 ; mov DI, register
	je INSTDI2Reg22 
	cmp bx, 2 ; mov SP, register
	je INSTSP2Reg22
	cmp bx, 3 ; mov BP, register
	jne fixINSTBP2Reg22
    jmp INSTBP2Reg22
    fixINSTBP2Reg22:
	je fix13MinusSize1 ; There is something wrong
    jmp minusSize1
    fix13MinusSize1:
	
	
	INSTSI2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov SI , ax
	jne fixINSTSI2AX2
    jmp INSTSI2AX2
    fixINSTSI2AX2:
	cmp bx, 9 ; mov SI, bx
	jne fixINSTSI2BX2
    jmp INSTSI2BX2
    fixINSTSI2BX2: 
	cmp bx, 10 ; mov SI, cx
	jne fixINSTSI2CX2
    jmp INSTSI2CX2
    fixINSTSI2CX2:
	cmp bx, 11 ; mov SI, dx
	jne fixINSTSI2DX2
    jmp INSTSI2DX2
    fixINSTSI2DX2:
	je fix14MinusSize1 ; There is something wrong
    jmp minusSize1
    fix14MinusSize1:
	
	INSTDI2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov DI , ax
	jne fixINSTDI2AX2
    jmp INSTDI2AX2
    fixINSTDI2AX2:
	cmp bx, 9 ; mov DI, bx
	jne fixINSTDI2BX2        
    jmp INSTDI2BX2
    fixINSTDI2BX2:
	cmp bx, 10 ; mov DI, cx
	jne fixINSTDI2CX2
    jmp INSTDI2CX2
    fixINSTDI2CX2:
	cmp bx, 11 ; mov DI, dx
	jne fixINSTDI2DX2 
    jmp INSTDI2DX2
    fixINSTDI2DX2:
	je fix15MinusSize1 ; There is something wrong
    jmp minusSize1
    fix15MinusSize1:
	
	INSTSP2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov SP , ax
	jne fixINSTSP2AX2
    jmp INSTSP2AX2
    fixINSTSP2AX2:
	cmp bx, 9 ; mov SP, bx
	jne fixINSTSP2BX2
    jmp INSTSP2BX2
    fixINSTSP2BX2: 
	cmp bx, 10 ; mov SP, cx
	jne fixINSTSP2CX2
    jmp INSTSP2CX2
    fixINSTSP2CX2:
	cmp bx, 11 ; mov SP, dx
	jne fixINSTSP2DX2
    jmp INSTSP2DX2
    fixINSTSP2DX2: 
	je fix16MinusSize1 ; There is something wrong
    jmp minusSize1
    fix16MinusSize1:
	
	INSTBP2Reg22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from ax, bx, cx, dx
	cmp bx, 8   ; mov BP , ax
	jne fixINSTBP2AX2
    jmp INSTBP2AX2
    fixINSTBP2AX2:
	cmp bx, 9 ; mov BP, bx
	jne fixINSTBP2BX2
    jmp INSTBP2BX2
    fixINSTBP2BX2: 
	cmp bx, 10 ; mov BP, cx
	jne fixINSTBP2CX2
    jmp INSTBP2CX2
    fixINSTBP2CX2:
	cmp bx, 11 ; mov BP, dx
	jne fixINSTBP2DX2
    jmp INSTBP2DX2 
    fixINSTBP2DX2:
	je fix17MinusSize1 ; There is something wrong
    jmp minusSize1
    fix17MinusSize1:
	
	INSTSI2AX2: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[0]
	mov ch, RegistersArray2[1]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSI2BX2: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[2]
	mov ch, RegistersArray2[3]
	call INSTINRegisters2
	jmp doneLabel2
	 
	INSTSI2CX2:
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[4]
	mov ch, RegistersArray2[5]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSI2DX2: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[6]
	mov ch, RegistersArray2[7]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2AX2: 
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[0]
	mov ch, RegistersArray2[1]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2BX2:
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[2]
	mov ch, RegistersArray2[3]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2CX2: 
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[4]
	mov ch, RegistersArray2[5]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2DX2:     
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[6]
	mov ch, RegistersArray2[7]
	call INSTINRegisters2
	jmp doneLabel2 
	
	INSTSP2AX2:
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[0]
	mov ch, RegistersArray2[1]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSP2BX2:
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[2]
	mov ch, RegistersArray2[3]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSP2CX2:  
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[4]
	mov ch, RegistersArray2[5]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSP2DX2:
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[6]
	mov ch, RegistersArray2[7]
	call INSTINRegisters2
	jmp doneLabel2     
	
	INSTBP2AX2:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[0]
	mov ch, RegistersArray2[1]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBP2BX2:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[2]
	mov ch, RegistersArray2[3]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBP2CX2:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[4]
	mov ch, RegistersArray2[5]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBP2DX2:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[6]
	mov ch, RegistersArray2[7]
	call INSTINRegisters2
	jmp doneLabel2
	
	;////////////////////////////////////// 
	
	INSTRegI12RegI22:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change SI, DI, SP, BP
	cmp bx, 0   ; mov SI, SI OR DI OR SP OR BP
	je INSTSI2RegI22 
	cmp bx, 1 ; mov DI, SI OR DI OR SP OR BP
	je INSTDI2RegI22 
	cmp bx, 2 ; mov SP, SI OR DI OR SP OR BP
	je INSTSP2RegI22
	cmp bx, 3 ; mov BP, SI OR DI OR SP OR BP
	jne fixINSTBP2RegI22
    jmp INSTBP2RegI22
    fixINSTBP2RegI22:
	je fix18MinusSize1 ; There is something wrong
    jmp minusSize1
    fix18MinusSize1:
	
	
	INSTSI2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov SI , SI
	jne fix5DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix5DoneLabel2:
	cmp bx, 1 ; mov SI, DI
	jne fixINSTSI2DI2
    jmp INSTSI2DI2
    fixINSTSI2DI2: 
	cmp bx, 2 ; mov SI, SP
	jne fixINSTSI2SP2
    jmp INSTSI2SP2
    fixINSTSI2SP2:
	cmp bx, 3 ; mov SI, BP
	jne fixINSTSI2BP2
    jmp INSTSI2BP2
    fixINSTSI2BP2:
	je fix19MinusSize1 ; There is something wrong
    jmp minusSize1
    fix19MinusSize1:
	
	INSTDI2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov DI , SI
	jne fixINSTDI2SI2
    jmp INSTDI2SI2
    fixINSTDI2SI2:
	cmp bx, 1 ; mov DI, DI
	jne fix6DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix6DoneLabel2: 
	cmp bx, 2 ; mov DI, SP
	jne fixINSTDI2SP2
    jmp INSTDI2SP2
    fixINSTDI2SP2:
	cmp bx, 3 ; mov DI, BP
	jne fixINSTDI2BP2
    jmp INSTDI2BP2
    fixINSTDI2BP2: 
	je fix20MinusSize1 ; There is something wrong
    jmp minusSize1
    fix20MinusSize1:
	
	INSTSP2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov SP , SI
	jne fixINSTSP2SI2
    jmp INSTSP2SI2
    fixINSTSP2SI2:
	cmp bx, 1 ; mov SP, DI
	jne fixINSTSP2DI2
    jmp INSTSP2DI2
    fixINSTSP2DI2: 
	cmp bx, 2 ; mov SP, SP
	jne fix7DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix7DoneLabel2:
	cmp bx, 3 ; mov SP, BP
	jne fixINSTSP2BP2
    jmp INSTSP2BP2
    fixINSTSP2BP2: 
	je fix21MinusSize1 ; There is something wrong
    jmp minusSize1
    fix21MinusSize1:
	
	INSTBP2RegI22:
	mov bx, op2 ; get operand 2 in bx then compare to know if he wants to get values from SI OR DI OR SP OR BP
	cmp bx, 0   ; mov BP , SI
	jne fixINSTBP2SI2
    jmp INSTBP2SI2
    fixINSTBP2SI2:
	cmp bx, 1 ; mov BP, DI
	jne fixINSTBP2DI2
    jmp INSTBP2DI2
    fixINSTBP2DI2: 
	cmp bx, 2 ; mov BP, SP
	jne fixINSTBP2SP2
    jmp INSTBP2SP2
    fixINSTBP2SP2:
	cmp bx, 3 ; mov BP, BP
	jne fix8DoneLabel2 ; Simply Don't do anything :) 
    jmp doneLabel2
    fix8DoneLabel2:          	
	je fix22MinusSize1 ; There is something wrong
    jmp minusSize1
    fix22MinusSize1:
	
	INSTSI2DI2: 
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[10]
	mov ch, RegistersArray2[11]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSI2SP2:          
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[12]
	mov ch, RegistersArray2[13]
	call INSTINRegisters2
	jmp doneLabel2
	 
	INSTSI2BP2:    
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[14]
	mov ch, RegistersArray2[15]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2SI2:    
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[8]
	mov ch, RegistersArray2[9]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2SP2: 
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[12]
	mov ch, RegistersArray2[13]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2BP2:    
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[14]
	mov ch, RegistersArray2[15]
	call INSTINRegisters2
	jmp doneLabel2 
	
	INSTSP2SI2:    
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[8]
	mov ch, RegistersArray2[9]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSP2DI2:           
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[10]
	mov ch, RegistersArray2[11]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSP2BP2:  
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[14]
	mov ch, RegistersArray2[15]
	call INSTINRegisters2
	jmp doneLabel2  
	
	INSTBP2SI2:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[8]
	mov ch, RegistersArray2[9]
	call INSTINRegisters2
	jmp doneLabel2 
	
	INSTBP2DI2: 
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[10]
	mov ch, RegistersArray2[11]
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTBP2SP2:    
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cl, RegistersArray2[12]
	mov ch, RegistersArray2[13]
	call INSTINRegisters2
	jmp doneLabel2 
	
	;////////////////////////////////////// 
	
	INSTRegI12Val2:
	mov bx, op1 ; get operand 1 in bx then compare to know if he wants to change SI, DI, SP, BP
	cmp bx, 0   ; mov SI, Value
	je INSTSI2Val2 
	cmp bx, 1 ; mov DI, Value
	je INSTDI2Val2 
	cmp bx, 2 ; mov SP, Value
	je INSTSP2Val2 
	mov bx, 0f0eh ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cx, op2 ; get value in cx
	call INSTINRegisters2
	jmp doneLabel2 
	
	INSTSI2Val2:   
	mov bx, 0908h ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cx, op2 ; get value in cx
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTDI2Val2:   
	mov bx, 0b0ah ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cx, op2 ; get value in cx
	call INSTINRegisters2
	jmp doneLabel2
	
	INSTSP2Val2:   
	mov bx, 0d0ch ; to execute instruction put the addresses in bx and values in cx then call INSTINRegisters2
	mov cx, op2 ; get value in cx
	call INSTINRegisters2
	jmp doneLabel2
	
	;//////////////////////////////////////
	
	
	
	minusSize1:
	mov dx, firstScore
    dec dx ; minus first player  
    mov firstScore, dx
    cmp firstScore, 0  ; if lower or equal so player 2 wins
    jbe secondWins3
	;call receiveInput ;////////////WAER///////////////////
    secondWins3:
    mov al, 0    ;/////// There is a player won
    EndGame secondUsername, secondScore ;//////// Second player won  
	
	doneLabel2: 
	xor user, 00000011b  ; toggle user: if user 1 make it user 2 and vice virsa
	
	exitExecuteInstruction2:   
	popf
	pop dx 
	pop cx 
	pop bx 
	pop ax
	ret
ExecuteInstruction2 endp 