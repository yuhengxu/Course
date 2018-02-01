#include<stdio.h>
int main()
{
	int i, j;
	int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int (*p)[4];
	scanf("%d %d", &i, &j);
	p = a;
	printf("a[%d][%d]=%d\n", i, j, *(*(p + i) + j));
}
