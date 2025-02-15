; Hello World Program

.386
.model flat, stdcall, c
.stack 4096

.data
mymsg BYTE ' Hello World in Assembly x86', 0

.code
includelib libucrt.lib
includelib legacy_stdio_definitions.lib
includelib libcmt.lib
includelib libvcruntime.lib

extrn printf:near
extrn exit:near

public main
main proc
	push	offset mymsg
	call	printf
	push	0
	call	exit

main endp
end
