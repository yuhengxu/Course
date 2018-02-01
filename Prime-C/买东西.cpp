#include <stdio.h>
int main()
 {
    int i,j,k;
	float m,n;
	scanf("%f%f",&m,&n);
	for(i=1;i<n-1;i++)
	{
		for(j=1;j<=n-1-i;j++)
		{
			for(k=1;k<=n-i-j;k++)
				if((i*5+j*3+k*1.0/3)==m&&i+j+k==n)
					printf("%d,%d,%d\n",i,j,k);
		}
	}
	return 0;
 }

