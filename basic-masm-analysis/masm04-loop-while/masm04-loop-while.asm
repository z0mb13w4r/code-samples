; while (num1 < num2)
; num1 = num1 + 1

.386
.model flat, stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
num1 dword 2
num2 dword 5
num3 dword 8

.code
main proc
	mov eax, num1
	mov ebx, num2

	top:

	cmp eax, ebx			; check loop condition (num1 < num2)
	jae next				; if false exit loop and execute next statement
	inc eax					; incrementing eax which is num1
	jmp top					; repeat the loop

	next:
	mov eax, num3

	invoke ExitProcess, 0

main endp
end main
