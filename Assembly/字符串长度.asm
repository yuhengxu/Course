;字符串长度

.386
.model flat, stdcall
option casemap:none

includelib		msvcrt.lib
includelib		kernel32.lib
include			kernel32.inc
printf			PROTO C :ptr sbyte, :VARARG
scanf			PROTO C :ptr sbyte, :VARARG

.data
inputString		db		"请输入字符串：", 0
outputString	db		"%d", 0ah, 0
scanfString		db		"%s", 0

string			byte	50 dup(0), 0

.code
main proc

	invoke printf, offset inputString
	invoke scanf, offset scanfString, offset string
	
	mov esi, offset string		;指向字符串的头
	xor ecx, ecx				;设置字符串初始长度为0

strlen:
	mov al, [esi]
	cmp al, 0				;如果是0 就说明到结尾了
	jz output
	inc esi					;没有到结尾就向后以一位，并且将计数ecx加1
	inc ecx
	jmp strlen
	
output:
	invoke printf, offset outputString, ecx
	invoke ExitProcess, 0

main endp
end main