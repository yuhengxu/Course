#include<stdio.h>
#include<string.h>
int main()
{
	int a[5][5],b[5][5];
	int i,j,n=1;
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			a[i][j]=n++;
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%3d",a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			b[i][j]=a[j][i];
		}
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%3d",b[i][j]);
		}
		printf("\n");
	}
}
