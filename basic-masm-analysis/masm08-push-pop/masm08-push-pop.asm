; Loops Assembly x86
; Reverse HELLO

.386
.model flat, stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
msg db "HELLO", 0

.code
main proc
	mov		ecx, lengthof msg - 1
	mov		esi, offset   msg

loop1:
	mov		al, byte ptr [esi]
	push	eax
	inc		esi
	loop	loop1

	mov		ecx, lengthof msg - 1
	mov		esi, offset   msg

loop2:
	pop		eax
	mov		[esi], al
	inc		esi
	loop	loop2

	invoke ExitProcess, 0

main endp
end main
