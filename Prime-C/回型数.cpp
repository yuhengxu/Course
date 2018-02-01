#include<stdio.h> 
int main() 
{ 
	
	int a[20][20],i,j,n,m=1,l,k=0; 
	scanf("%d",&n); 
	l=n; 
	for(i=1;i<=(n+1)/2;i++) 
	{ 
    for(j=0;j<l;j++) 
	{a[k][j+k]=j+m; 
	a[n-1-k][j+k]=3*l-3+m-j; 
	} 
	for(j=1;j<=l-1;j++) 
	{a[j+k][k]=4*l-4-j+m; 
	a[j+k][n-1-k]=l+j+m-1; 
	} 
	m=m+4*l-4; 
	l=l-2; 
	k=k+1; 
	} 
	for(i=0;i<=n-1;i++) 
	{ 
	for(j=0;j<=n-1;j++)
	{ 
	printf("%3d",a[i][j]); 
	printf("\n"); 
	} 
	} 
} 
