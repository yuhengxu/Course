#include<stdio.h>
void prt_sequence(int *begin,int *end)
{
	for (; begin < end; begin+=1)
		printf("%c",*begin);
	
}
int main()
{
	char str[100];
	char *begin, *end;
	int a, b;
	gets(str);
	scanf("%d %d", &a, &b);
	begin = &str[a];
	end = &str[b];
	prt_sequence(begin, end);
}
