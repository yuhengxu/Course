#include<stdio.h>
#include<string.h>
int main()
{
	int a[100],b[100],c[100];
	int i,j,k,q,x,figure,counter,sum,dragon,hero;
	scanf_s("%d %d",&dragon,&hero);
	for(i=0;i<dragon;i++)
	{
		scanf_s("%d",&figure);
		a[i]=figure;
	}
	for(i=dragon,j=0;i<hero+dragon;i++,j++)
	{
		scanf_s("%d",&figure);
		b[j]=figure;
	}
	if(dragon>hero)
	{
		printf("bit is doomed!\n");
	}
	else
	{
		for(i=0;i<dragon;i++)
		{
			for(k=i+1;k<dragon;k++)
			{
				if(a[i]>a[k])
				{
					x=a[i];
					a[i]=a[k];
					a[k]=x;
				}
			}
		}
		a[i]=0;
		for(i=0;i<hero;i++)
		{
			for(k=i+1;k<hero;k++)
			{
				if(b[i]>b[k])
				{
					x=b[i];
					b[i]=b[k];
					b[k]=x;
				}
			}
		}
		b[i]=0;
		for(i=0,j=0,q=0;i<dragon;i++,j++)
		{
			for(;j<hero;j++)
			{
				if(a[i]<=b[j])
				{
					c[q]=b[j];
					q++;
					break;
				}
			}
			if(q==0||i!=dragon-1&&j==hero-1)
			{
				printf("bit is doomed!\n");
				return 0;
			}
		}
		counter=q;
		c[q]=0;
		for(q=0,sum=0;q<=counter;q++)
		{
			sum=sum+c[q];
		}
		printf("%d\n",sum);
	}
	return 0;
}
