#include<stdio.h>
    int  swap(int *p, int *q)
	{
		int t = *p;
		*p = *q;
		*q = t;
	}
	int main()
	{
		int m=1, n=2;
		//scanf_s("%d %d", &m, &n);
		printf("m=%d,n=%d\n",m,n);
		swap( m, n);
		printf("m=%d,n=%d\n",m,n);
	}
