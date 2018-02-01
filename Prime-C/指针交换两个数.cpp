#include<stdio.h>
int main()
{
	void swap(int a,int b);
	int a,b;
	scanf("%d %d",&a,&b);
	swap(a,b);
	printf("%d,%d\n",a,b);
}
void swap(int a,int b)
{
	int t;
	t=a;
	a=b;
	b=t;
	printf("%d %d\n",a,b);
}

