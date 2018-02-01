#include<stdio.h>
int main()
{
	int a,i;
	scanf("%d",&a);
	for(i=2;a!=1;)
	{
		if(a%i==0)
		{
			a=a/i;
			printf("%d",i);
		}
		else
		{
			i++;
		}
	}
 } 
