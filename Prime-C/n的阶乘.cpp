#include<stdio.h>
float fact(int n)
{
	float f;
	if(n<0)
	{
		printf("error!");
	}
	if(n==1)
	{
		return 1;
	}
	else if(n>1)
	{
		return f=n*fact(n-1);
	}
}
int main()
{
	float n;
	scanf("%f",&n);
	printf("%f\n",fact(n));
}
