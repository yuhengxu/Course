#include<stdio.h>
int main()
{
	int a[20]={1,1};
	int j;
	for(j=2;j<20;++j)
	{
		a[j]=a[j-1]+a[j-2];
	}
	for(j=0;j<20;j++)
	{
		printf("%10d",a[j]);
	}
	

}
