#include<stdio.h>

int main()
{
	int C=0;
	double F;
	while (C <= 300)
	{
		F = C * 9 / 5.0 + 32.0;
		printf("C=%d,F=%f\n", C, F);
		C = C + 20;
	}

	return 0;
}