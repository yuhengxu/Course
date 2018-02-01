#include<stdio.h>
int main()
{
	int a,b,c;
	scanf("%d %d %d",&a,&b,&c);
	if(a>b)
		if(b>c)
		printf("这三个数的大小关系是%d>%d>%d\n",a,b,c);
		else if(a>c)
			printf("这三个数的大小关系是%d>%d>%d\n",a,c,b);
			else
			printf("这三个数的大小关系是%d>%d>%d\n",c,a,b);
	else 
		if(a>c)
		printf("这三个数的大小关系是%d>%d>%d\n",b,a,c);
		else
			if(b<c)
			printf("这三个数的大小关系是%d>%d>%d\n",c,b,a);
			else
			printf("这三个数的大小关系是%d>%d>%d\n",b,c,a);
} 

