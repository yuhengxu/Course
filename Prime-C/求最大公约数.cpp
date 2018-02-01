#include<stdio.h>
int main()
{
	int n,m,i,r;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n&&i<=m;i++)
	{
		if(n%i==0)
		{
			if(m%i==0)
			{
				r=i;
			}
		}
	}
	printf("%d\n",r);
}
