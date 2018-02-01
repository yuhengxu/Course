#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a, const void *b)
{
	return *(long long*)a - *(long long*)b;
}
long long number[50005], dp[50005];
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lld", &number[i]);
		qsort(number, n, sizeof(number[0]), cmp);
		long long max = 0;
		dp[0] = 0, dp[1] = number[1];
		for (int i = 0; i < n; ++i)
		{
			max = (max > (number[i] - dp[i])) ? max : (number[i] - dp[i]);
			dp[i + 1] = max;
		}
		printf("%lld\n", dp[n]);
	}
}