#include<stdio.h>
#include<string.h>
int main()
{
	int a[10][10];
	int i,j,x;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(j>=i)
			{
				a[i][j]=1;
			}
			else
			{
				a[i][j]=i-j+1;
			}
		}
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%2d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
} 
