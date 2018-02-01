#include<stdio.h>
int main()
{
	int n1 = 0, n2 = 0;
	int r1[105] = { 0 }, r2[105] = { 0 };
	int dp[105][105] = { 0 };
	int temp = 1;
	for (; 1;)
	{
		scanf("%d%d", &n1, &n2);
		if (n1 == 0 && n2 == 0)break;
		for (int row = 1; row <= n1; row++) scanf("%d", &r1[row]);
		for (int row = 1; row <= n2; row++) scanf("%d", &r2[row]);
		for (int i = 1; i <= n1; i++)
		{
			for (int j = 1; j <= n2; j++)
			{
				if (r1[i] == r2[j])dp[i][j] = dp[i - 1][j - 1] + 1;
				else dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
			}
		}
		printf("Twin Towers #%d\n", temp++);
		printf("Number of Tiles : %d\n", dp[n1][n2]);
	}
}