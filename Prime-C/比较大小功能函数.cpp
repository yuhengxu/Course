#include<stdio.h>
int main()
{
	int a,b,c;
	int max(float,float);
	scanf("%d %d",&a,&b);
	c=max(a,b);
	printf("%d\n",c); 
}
int max(float x,float y)
{
	int n;
	n=x>y?x:y;
	return n;
}
