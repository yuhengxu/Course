.586
.model flat, stdcall
option casemap :none

include		kernel32.inc
includelib	kernel32.lib
includelib	msvcrt.lib

printf		PROTO C :ptr sbyte, :VARARG
scanf		PROTO C :ptr sbyte, :VARARG

.data
;矩阵
arr1	dword	1000000	dup(?)
arr2	dword	1000000	dup(?)
arr3	dword	1000000	dup(0)
num		dword	1000000			;元素个数
row		dword	1000
col		dword	1000

;线性同余参数
a		dword	9973
b		dword	17
d		dword	101
m		dword	1000000007

i		dword	0
j		dword	0
k		dword	0

t1		dword	0
t2		dword	0
t3		dword	0

tipa	dword	0
tipb	dword	0
tipc	dword	0

temp	dword	4

;输入输出
outputTime		db	"汇编运行时间：%d ms", 0ah, 0
outputString	db	"%d ", 0
outputn			db	" ", 0ah, 0

;计算时间
starttime	dword	0
endtime		dword	0


.code
main	proc

;*******计算初始时间**********
invoke	GetTickCount
mov starttime,	eax

;*******初始化随机数组arr1******
	mov ecx,	num
	mov edx,	0
	mov i,		edx
l1:
	rdtsc				;获取CPU当前时钟周期作为种子
	mul a				;线性同余算法 edx=(a*eax+b)%m
	add eax,	b
	div m
	mov eax,	edx
	mov edx,	0
	div d

	mov esi,	i
	add i,		4
	mov arr1[esi],	edx
	loop l1

;*******初始化随机数组arr2******
	mov ecx,	num
	mov edx,	0
	mov i,		edx
l2:
	rdtsc				;获取CPU当前时钟周期作为种子
	mul a				;线性同余算法 edx=(a*eax+b)%m
	add eax,	b
	div m
	mov eax,	edx
	mov edx,	0
	div d

	mov esi,	i
	add i,		4
	mov arr2[esi],	edx
	loop l2

;***********矩阵乘法***********
	mov eax,	row		;row - i
	mov ebx,	row		;row - j
	mov ecx,	row		;row - k

l3:
	cmp eax,	0
	ja	l4
	jmp output

l4:
	cmp ebx,	0
	ja	l5
	mov	edx,	row
	dec eax
	jmp l3

l5:
	cmp ecx,	0
	ja	l6
	mov ecx,	row
	dec ebx
	jmp l4

l6:
	mov tipa,	eax		;保存eax的值
	mov tipb,	ebx		;保存ebx的值
	mov tipc,	ecx		;保存ecx的值
	
	mov esi,	row		;i
	mov col,	esi
	sub col,	eax
	mov eax,	col
	mov i,		eax

	mov esi,	row		;j
	mov col,	esi
	sub col,	ebx
	mov ebx,	col
	mov j,		ebx

	mov esi,	row		;k
	mov col,	esi
	sub col,	ecx
	mov ecx,	col
	mov k,		ecx

	;arr3[i][j] +=arr1[i][k] * arr2[k][j]
	mov eax,	i
	mul row
	add eax,	k
	mul temp
	mov t1,		eax		;arr1的角标

	mov eax,	k
	mul row
	add eax,	j
	mul temp
	mov t2,		eax		;arr2的角标

	mov eax,	i
	mul row
	add eax,	j
	mul temp
	mov t3,		eax		;arr3的角标

	mov ebx,	t1
	mov eax,	arr1[ebx]
	mov ebx,	t2
	mul arr2[ebx]
	mov ebx,	t3
	add arr3[ebx], eax

	;invoke printf, offset outputString, eax

	mov ecx,	tipc	;恢复ecx的值
	mov ebx,	tipb	;恢复ebx的值
	mov eax,	tipa	;恢复eax的值


	dec ecx
	jmp l5

output:
	invoke	GetTickCount
	mov endtime,	eax

	mov eax,	endtime
	sub eax,	starttime
	invoke printf, offset outputTime, eax

	invoke ExitProcess, 0

main endp
end main