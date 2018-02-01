#include<stdio.h>
int main()
{
	int n,isPrime=1;
	scanf("%d",&n);
	for(int i=2;i<n;i++)
	{
		if(n%i==0)
		{
		isPrime=0;
		}	
	}
	if(isPrime)
	{
		printf("%d是素数\n",n);
	 } 
	 else
	 {
	 	printf("%d不是素数\n",n);
	 }
}
