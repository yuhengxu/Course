#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main()
{
	int n;
	int txm[100] = { 0 }, copy[100] = { 0 };
	double min[100] = { 0 }, max[100] = { 0 };
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &txm[i]);
	for (int i = 0; i < n; i++)
		copy[i] = txm[i];

	qsort(txm, n, sizeof(txm[0]), cmp);//快速排序

	int i = 0, j = 0, M1 = 0, M2 = 0;
	for (int row = 0; row < n; row++)//分大小
	{
		if (txm[row] < txm[0] * 1.5)
		{
			min[i] = txm[row];
			M1 = i;
			i++;
		}
		else
		{
			max[j] = txm[row];
			M2 = j;
			j++;
		}
	}

	if (j == 0)
	{
		for (int row = 0; row <= M1; row++)
		{
			if (row == M1)
				printf("1\n");
			else printf("1");
		}
		return 0;
	}
	if (min[M1] - (21.0 / 19.0 * min[0]) > 0 || max[M2] - (21.0 / 19.0 * max[0]) > 0 || max[M2] - (42.0 / 19.0 * min[0]) > 0 || min[M1] - (21.0 / 38.0 * max[0]) > 0)
	{
		printf("Bad Barcodes");
		return 0;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (i == n - 1)
			{
				if (copy[i] > txm[0] * 1.5)
					printf("1\n");
				else printf("0\n");
			}
			else
			{
				if (copy[i] > txm[0] * 1.5)
					printf("1");
				else printf("0");
			}

		}
	}
	return 0;
}