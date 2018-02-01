#include<stdio.h>
int fib(int n)
{
	int a;
	if(n<=2)
	{
		return 1;
	}
	else
	{
		return fib(n-1)+fib(n-2);
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	printf("%d\n",fib(n));
}
