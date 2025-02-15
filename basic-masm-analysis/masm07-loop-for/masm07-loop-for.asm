; for loops Assembly x86
; for (int i = 0; num1 < num2; i++)
;	num1 = num1 + 1;

.386
.model flat, stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
num1 dword 3
num2 dword 6
num3 dword 8

.code
main proc
	mov eax, num1
	mov ebx, num2

start:
	cmp eax, ebx		; check loop condition
	jae exit			; false ? exit loop
	inc eax				; body of loop
	jmp start			; repeat the loop

exit:
	mov eax, num3

	invoke ExitProcess, 0

main endp
end main
