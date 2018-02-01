#include<stdio.h>
int main()
{
	int i,j,n,temp,isPrime=0;
	scanf("%d",&n);
	for(j=3;j<n;j++)
	{

		for(i=2;i<j;i++)
		{
			isPrime=j%i;	
			if(isPrime==0)
			{
				break;
			}
		}
		if(isPrime!=0)
		{
			temp=j;
		}
	}
	printf("The max prime number is %d.\n",temp);
}
