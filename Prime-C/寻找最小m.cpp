#include<stdio.h>
int main()
{
	int m=1,n,t;
	scanf("%d",&n);
	for(t=0;t<=n;)
	{
		t=t+m;
		m++;
		if(t>n)
		{
			m--;
			break; 
		}
	}
	printf("%d\n",m);
}
