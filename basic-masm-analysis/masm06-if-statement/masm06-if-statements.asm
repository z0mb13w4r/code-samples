; if statement Assembly x86
; if (num1 == num2)
; x = 1
; else
; x = 2

.386
.model flat, stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
num1 dword 3
num2 dword 3
num3 dword ?

.code
main proc
	mov eax, num1
	cmp eax, num2
	jne label1
	mov num3, 1
	jmp label2

label1:
	mov num3, 2
label2:
	invoke ExitProcess, 0

main endp
end main
