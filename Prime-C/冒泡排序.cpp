#include<stdio.h>
void swap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
int main()
{
	int a[10];
	int i,j,t;
	for(i=0;i<10;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<10;i++)
	{
		for(j=i+1;j<10;j++)
		{
			if(a[j]>a[i])
			{
				swap(&a[i],&a[j]);
			}
		}
	}
	for(i=0;i<10;i++)
	{
		printf("%3d",a[i]);
	}
}
