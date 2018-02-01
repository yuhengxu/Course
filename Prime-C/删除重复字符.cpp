void repeat(char a[100])
{
	char b[100];
	int n,i,j,k=1;
	n=strlen(a); 
	for(i=0;i<n;i++)
	{
		b[0]=a[0];
		for(j=0;j<=i;j++)
		{
			if(j<i&&a[i]==b[j])
			{
				break;
			}
			if(a[i]!=b[j]&&i!=j)
			{
				continue;
			}
			if(j==i&&a[i]!=b[j])
			{
				b[k]=a[i];
				k++;
			}
		}
	}
	b[k]=0;
	for(i=0;i<n;i++)
	{
		a[i]=b[i];
	}
} 
