;文件内容比对

.386
.model flat, stdcall
option casemap:none

includelib		msvcrt.lib
includelib		kernel32.lib
include			kernel32.inc

printf			PROTO C :dword, :VARARG
scanf			PROTO C :dword, :vararg
fopen			PROTO C :dword, :vararg
fclose			PROTO C :dword
fgets			PROTO C :dword, :dword, :dword
strcmp			PROTO C :dword, :dword
feof			PROTO C :dword					;检测文件结束符

.data
szMsg1			byte	"文件内容一致", 0ah,0
szMsg2			byte	"文件对比完毕", 0ah, 0
szInt			byte	"第 %d 行不同", 0ah, 0

n				byte	100			;一行最多读取100个字符
line			dword	0			;查找行号
mark			byte	0			;某行不相等用来记录
modestr			byte	"rb", 0		;文件只读

f1				byte	"1.txt", 0	;要打开的文件名
f2				byte	"2.txt", 0

fp1				dword	?			;流
fp2				dword	?

buf1			dword	100 dup(0)	;缓冲区
buf2			dword	100 dup(0)


.code
main proc

	invoke	fopen, offset f1, offset modestr
	mov		fp1, eax							;返回值都存在eax中
	invoke	fopen, offset f2, offset modestr
	mov		fp2, eax

l1:
	invoke	fgets, offset buf1, offset n, fp1	;按行读取两文件里的内容
	invoke	fgets, offset buf2, offset n, fp2

	invoke	strcmp, offset buf1, offset buf2

	inc		line								;对比下一行	

	cmp		eax, 0								;相等就继续
	jz		l2

	invoke	printf, offset szInt, line			;不相等就输出行号
	inc		mark
	
l2:
	invoke	feof, fp1							;检查是否读到文件尾
	cmp		eax, 0
	jnz		l0
	jmp		l1

l0:
	cmp		mark, 0								;检查标记为，如果为零输出“文件内容一致”，否则关闭文件
	jz		l3
	invoke	printf, offset szMsg2
	jmp		l4

l3:
	invoke	printf, offset szMsg1

l4:
	invoke	fclose, fp1
	invoke	fclose, fp2

	invoke	ExitProcess, 0
main endp
end main