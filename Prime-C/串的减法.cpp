#include<stdio.h>
#include<string.h>
int main()
{
	char s[80],t[80],u[80];
	int i,j,k,m,n;
	gets(s);
	gets(t);
	n=strlen(s);
	m=strlen(t);
	if(m==0)
	{
		puts(s);
		return 0;
	}
	for(i=0,k=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(s[i]==t[j])
			{
				break;
			}
			if(s[i]!=t[j])
			{
				if(j==m-1)
				{
					u[k]=s[i];
					k++;
				}
			
			}
		} 
	}
	u[k]=0;
	puts(u);
	return 0;
}
