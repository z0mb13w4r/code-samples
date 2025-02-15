; subtract two 32-bit integers

.386
.model flat, stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data

res DWORD ?

.code
main proc
	mov eax, 7
	sub eax, 4
	mov res, eax

	invoke ExitProcess, 0

main endp
end main
