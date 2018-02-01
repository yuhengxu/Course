#include<stdio.h>
 int facto(int n)
 {
 	int r;
 	if(n==0)  r=1;
 	else      r=n*facto(n-1);
 	return r;
  } 
int main()
{
	int n,p;
	printf("N=?\n");
	scanf("%d",&n);
	p = facto(n);
	printf("%d!=%d\n",n,p);
 } 

