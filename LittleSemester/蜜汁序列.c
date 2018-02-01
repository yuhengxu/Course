#include<stdio.h>
int a[1000005] = { 0 };
int main()
{
	int n;
	while (scanf_s("%d", &n) != EOF)
	{
		long long sum = 0;
		for (int i = 0; i < n; i++)
		{
			scanf_s("%d", &a[i]);
		}
		int mizhi = 0;

		for (int i = n - 1; i > -1; i--)
		{
			if (a[i] >= 0)
			{
				mizhi++;
			}
			if (a[i] < 0)
			{
				sum = 0;
				for (; sum <= 0; i--)
				{
					sum += a[i];
					if (sum >= 0)
					{
						mizhi++;
						//i++;
						break;	
					}
				}
			}
		}
		printf("%d\n", mizhi);
	}
}