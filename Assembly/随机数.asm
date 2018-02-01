.586
.model flat, stdcall
option casemap :none

include kernel32.inc
includelib kernel32.lib
includelib msvcrt.lib

printf			PROTO C :ptr sbyte, :VARARG
scanf			PROTO C :ptr sbyte, :VARARG

.data
outputString	db		"%d", 0ah, 0
a				dword	9973
b				dword	17
m				dword	1000000007


.code
main proc
	rdtsc		;获取CPU当前时钟周期作为种子
	mul a		;线性同余算法 edx=(a*eax+b)%m
	add eax, b
	div m
	invoke printf, offset outputString, edx
	invoke ExitProcess, 0
main endp
end main 
	