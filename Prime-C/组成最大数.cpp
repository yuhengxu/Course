#include<stdio.h>
#include<string.h>
int main()
{
	char a[100];
	int n,i,k,t;
	gets(a);
	n=strlen(a);
	for(i=0;i<n;i++)
	{
		for(k=i+1;k<n;k++)
		{
			if(a[i]<=a[k])
			{
				t=a[k];
				a[k]=a[i];
				a[i]=t;
			}
		}
	}
	a[i]=0;
	puts(a);
 } 
