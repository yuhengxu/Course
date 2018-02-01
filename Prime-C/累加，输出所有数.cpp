#include<stdio.h>
int main()
{
	int n,s,t,a1=1,a2=1;
	scanf("%d",&n);
	printf("%d\t%d\t",a1,a2);
	for(int i=3;i<=n;i++)
	{
	t=a1+a2;
	s=s+t;
	printf("%d\t",s);
	a1=a2;
	a2=t;
	}
	printf("%d\n",s);
} 
