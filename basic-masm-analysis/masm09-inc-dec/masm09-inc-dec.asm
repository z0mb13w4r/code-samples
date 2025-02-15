; INC & DEC

.386
.model flat, stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
num1 dword 3
num2 dword ?
num3 dword ?

.code
main proc
	mov eax, num1
	inc eax
	mov num2, eax
	dec eax
	dec eax
	mov num3, eax

	invoke ExitProcess, 0

main endp
end main
