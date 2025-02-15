; num5 = (2 + 6) - (1 + 3)

.386
.model flat, stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
num1 dword 2
num2 dword 6
num3 dword 1
num4 dword 3

num5 dword ?

.code
main proc
	mov eax, num1
	add eax, num2
	mov ebx, num3
	add ebx, num4
	sub eax, ebx
	mov num5, eax

	invoke ExitProcess, 0

main endp
end main
