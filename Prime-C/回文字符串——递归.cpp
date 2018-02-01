#include<stdio.h>
#include<string.h>
int main()
{
	char str[100];
	int start,end,t;
	gets(str);
	scanf("%d %d",&start,&end);
	for(;start<=end;start++,end--)
	{
		t=str[start];
		str[start]=str[end];
		str[end]=t;
	}
	puts(str);
}
