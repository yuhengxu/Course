#include<stdio.h>
int main()
{
	 int i,j,n;
	 scanf("%d",&n);
	 for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
		if(j==n)
		printf("%3d\n",n*(i-1)+j);
		else printf("%3d",n*(i-1)+j);
		}
	}
	return 0;
}
	
	

