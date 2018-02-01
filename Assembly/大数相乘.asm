.386
.model flat, stdcall
option casemap:none

include kernel32.inc
includelib kernel32.lib
includelib	msvcrt.lib

printf		PROTO C :ptr sbyte, :VARARG
scanf		PROTO C :ptr sbyte, :VARARG

.data
Msg		byte	"%s",0ah,0		;输出格式
Msgs	byte	"0",0ah,0		;结果为0
ssIn	byte	"%s %s",0		;输入格式
ss1		byte	100 dup(0)		;数1
ss2		byte	100 dup(0)		;数2
ss3		byte	1000 dup(0)		;结果
sslen1	dd		0				;数1长度
sslen2	dd		0				;数2长度
sslen3	dd		0				;结果长度

.code
main proc
	invoke 	scanf, offset ssIn,offset ss1, offset ss2
		
	mov		esi, offset ss1		;记录数1的地址
	mov		edi, offset ss2		;记录数2的地址
	
findtail1:						;寻找数1的尾地址
	mov		bl, [esi]		
	cmp		bl, 0
	jz		findtail2
	inc		esi
	jmp		findtail1
	
findtail2:						;寻找数2的尾地址
	mov		bl, [edi]
	cmp		bl, 0
	jz		jisuan
	inc		edi
	jmp		findtail2
	
jisuan:					
	dec		edi			
	mov		edx,edi				;记录数2的尾地址
	dec		esi
	mov		ebx,0				;清空进位

l1:								;一位数和多位数的乘法
	mov		al,	[esi]			
	sub		al,	30H				;取出数1当前位
	mov		bl,	[edi]
	sub		bl,	30H				;取出数2当前位
	mul		bl					;乘法
	aam							;进位值在AH，当前位在AL
	add		al,	bh				;处理上次进位
	mov		bh, ah				;记录这次进位
	cmp		al, 10		
	jb		l11					;无再次进位跳转
	add		bh,	1
	sub		al,	10				;向前进一位本位减10
	
l11:					
	mov		ecx, sslen1			;取出数1当前长度
	add		al,	ss3[ecx]		;本次计算出的结果和已经在结果中的相对位置的值相加
	cmp		al,	10		
	jb		l12					;若无进位跳转
	add		bh,	1
	sub		al,	10				;向前进一位本位减10
	
l12:
	mov		ss3[ecx], al		;保存当前位
	inc		sslen1				;数1指向下一位
	mov		ecx, sslen1			
	mov		sslen3,	ecx			;保存结果长度
	mov		ecx, offset ss2		
	cmp		ecx, edi			
	jz		l2					;内层循环结束（乘数的一位和被乘数的所有位都乘完）
	dec		edi
	jmp		l1					;继续循环

l2:								;外层循环
	cmp		bh,	0		
	jbe		l21					;若无进位，跳转
	mov		ecx,	sslen3		;处理进位
	mov		ss3[ecx],bh
	inc		sslen3

l21:
	mov		ecx, offset ss1		
	cmp		ecx, esi
	jz		l3					;外层循环结束（被乘数已经到结尾）
	
	mov		edi, edx			;数1重置尾地址
	dec		esi
	inc		sslen2				;数2指向下一位
	mov		ecx, sslen2
	mov		sslen1,	ecx
	mov		ebx, 0
	jmp		l1					;继续内层循环
	
l3:								;倒着乘的，所以最后要倒转
	mov		esi, offset ss3
	mov		edi, offset ss3
	mov		ecx, sslen3
	mov		al,	40H
	mov		ss3[ecx],al			;标记
	
l4:				
	mov		bl,	[esi]			;寻找标记
	cmp		bl,	40H
	jz		l5
	inc		esi
	jmp		l4

l5:
	mov		bl,	0
	mov		[esi], bl
	
l6:								;首尾互换
	dec		esi					;结果第一位的地址
	cmp		esi, edi		
	jb		l7					;准备输出
	mov		al,	[esi]
	add		al,	30H
	mov		bl,	[edi]
	add		bl,	30H
	mov		[edi], al
	mov		[esi], bl
	inc		edi
	jmp		l6

l7:
	mov		esi, offset ss3
	mov		al,	30H		
	cmp		al,	[esi]			;判断首位是否为0，如果为0，则整个结果为0
	jz		l9
	
l8:
	invoke	printf,	offset	Msg, esi
	invoke	ExitProcess, 0
	
l9:								;结果为0
	inc		esi
	cmp		al,	[esi]
	jnz		l8
	invoke	printf,	offset	Msgs
	
	invoke	ExitProcess, 0
main endp
end	main