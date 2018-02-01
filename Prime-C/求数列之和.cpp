#include<stdio.h>
#include<math.h>
int main()
{
	int n,i;
	double j,sum=1;
	scanf("%d",&n);
	if(n==1)
	{
		printf("1\n");
		return 0;
	}
	for(i=2;i<=n;i++)
	{
		j=i;
		sum=sum+pow(-1,i)*(1/j);
	}
	printf("%lf",sum);
	return 0;
}
