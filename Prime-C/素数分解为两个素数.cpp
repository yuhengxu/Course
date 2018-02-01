#include<stdio.h>
int isprime (int n)
{
	int i;
	for(i=2;i<=n/2;i++)
		if(n%i==0)
		return 0;
		return 1;
}
int main()
{
	int sum,i;
	scanf("%d",&sum);
	for(i=2;i<=sum/2;i++)
		if(isprime(i)&&isprime(sum-i))
		printf("%d=%d+%d\n",sum,i,sum-i);
}
