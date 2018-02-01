.586
.model flat, stdcall
option casemap :none

include		kernel32.inc
includelib	kernel32.lib
includelib	msvcrt.lib

printf		PROTO C :ptr sbyte, :VARARG
scanf		PROTO C :ptr sbyte, :VARARG

.data
num1	dd		0
num2	dd		2147483648
sec1	dd		2
sec2	dd		5
Msg		byte	"时间为：%d ns",0ah,0
array1	byte	1024	dup(15)			;原地址
array2	byte	1024	dup(0)			;目标地址

.code
main	proc
	rdtsc								;当前CPU周期数导入edx:eax
	mov	num1,	eax						;记录
	
	xor	edx,	edx						;置零
	
l4:
	cmp	edx,	1000					;判断是否结束
	jnb	l3
	mov	ebx,	dword ptr array1[edx]	;4个字节转移
	mov	dword ptr array2[edx],	ebx
	add	edx,	4
	jmp	l4
	
l3:
	rdtsc								;获得当前当前CPU周期数
	sub	eax, 	num1
	cmp	eax,	0						;判断是否有借位
	jnl	l2
	add	eax,	num2
	
l2:	
	xor	edx,	edx
	mul	sec1								;2.5GHz,一个周期0.4ns
	div	sec2
	cmp	edx,	0							;检查是否超过eax的范围
	jz	l1
	inc	eax
	
l1:
	invoke	printf,	offset Msg, eax
	invoke	ExitProcess, 0
main endp
end	main