#include<stdio.h>
#include<string.h>
int main()
{
	char a[10],b[10],c[20];
	int i,j,k,n,m;
	gets(a);
	n=strlen(a);
	gets(b);
	m=strlen(b);
	for(i=0,j=0,k=0;i<n&&j<m;k++)
	{
		if(a[i]>b[j])
		{
			c[k]=b[j];
			j++;
		}
		else
		{
			c[k]=a[i];
			i++;
		}
	}
	for(;i<n;k++)
	{
		c[k]=a[i];
		i++;
	}
	for(;j<m;k++)
	{
		c[k]=b[j];
		j++;
	}
	puts(c);
return 0;
}
