#include<stdio.h>
int i = 1;
void main()
{
	int movedisc(unsigned n, char fromneedle, char toneedle, char usingneedle);
	unsigned n;
	printf("Please enter the number of the discs");
	scanf_s("%d", &n);
	movedisc(n, 'a', 'b', 'c');
	printf("\t Total: %d\n", i);
}

int  movedisc(unsigned n, char fromneedle, char toneedle, char usingneedle)/*将fromneedle上的盘子通过usingneedle移动到toneedle上*/
{
	if (n == 1)
		printf("%2d - %2d: %c= = >%c\n", ++i, n, fromneedle, toneedle);
	else
	{
		movedisc(n - 1, fromneedle, usingneedle, toneedle);
		printf("%2d - %2d: %c= = >%c\n", ++i, n, fromneedle, toneedle);
		movedisc(n - 1, usingneedle, toneedle, fromneedle);
	}
}