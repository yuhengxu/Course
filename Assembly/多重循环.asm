;多重循环

.386
.model flat, stdcall
option casemap:none

includelib		msvcrt.lib
includelib		kernel32.lib
include			kernel32.inc
printf			PROTO C :ptr sbyte, :VARARG
scanf			PROTO C :ptr sbyte, :VARARG

.data
inputString		db		"请输入外层和内层循环次数：", 0
outputString	db		"%d, %d, %d, %d", 0ah, 0
scanfString		db		"%d%d%d", 0

num1			dword	?	;最外层循环
num2			dword	?	;第二层循环
num3			dword	?	;最内层循环
num				dword	0

.code
main proc

	invoke printf, offset inputString
	invoke scanf, offset scanfString, offset num1, offset num2, offset num3
	
	mov eax, num1
	mov ebx, num2
	mov ecx, num3
	 
l1:
	cmp eax, 0		;最外层循环
	ja l2
	jmp output

l2:
	cmp ebx, 0		;第二层循环
	ja l3
	mov ebx, num2
	dec eax
	jmp l1
	
l3:
	cmp ecx, 0		;最内层循环
	ja l4
	mov ecx, num3
	dec ebx
	jmp l2

l4:
	inc num			;自加
	dec ecx
	jmp l3

output:
	invoke printf, offset outputString, num1, num2, num3, num
	invoke ExitProcess, 0

main endp
end main