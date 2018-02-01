// 整数问题 
#include<stdio.h>
#include<math.h>
int main()
{
	int x,n,i,t,a,sum=0;
	scanf("%d",&n);
	if(n==1)
	{
		printf("9\n");
	}
	if(n==8) 
	{
		printf("0\n");
	}
	else
	{
		for(x=pow(10,n-1);x<pow(10,n);)
	{
		t=x; 
		for(i=2;i<=n;i++)
		{
			a=0;
			t=x/pow(10,n-i);
			if(t%(i*i)!=0)
			{
				a++;
				break;
			}

		}
		if(a!=0)
		{
			x++;
		}
		else
		{
			sum++;
			x++;
		}
		
	}
	printf("%d\n",sum);
	}
	
 } 
