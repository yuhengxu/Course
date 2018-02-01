#include <stdio.h>
int dp[1000010][2][2], p;
int top = 2;
int math(int i)
{
	i=(dp[p][0][0] + dp[p][0][1] + dp[p][1][0] + dp[p][1][1]) % 666;
	return i;
}
int main()
{
	int T;
	scanf("%d", &T);
	dp[2][0][0] = dp[2][0][1] = dp[2][1][0] = dp[2][1][1] = 1;
	while (T--)
	{
		scanf("%d", &p);
		if (p == 1)
		{
			printf("2\n");
			continue;
		}
		if (p < top)
		{
			int ans = math(p);
			printf("%d\n", ans);
			continue;
		}
		for (int i = top + 1; i <= p; i++)
		{
			dp[i][0][0] = (dp[i - 1][0][0] + dp[i - 1][0][1]) % 666;
			dp[i][0][1] = (dp[i - 1][1][0] + dp[i - 1][1][1]) % 666;
			dp[i][1][0] = dp[i - 1][0][0];
			dp[i][1][1] = dp[i - 1][1][0];
		}
		int ans = (dp[p][0][0] + dp[p][0][1] + dp[p][1][0] + dp[p][1][1]) % 666;
		printf("%d\n", ans);
		top = p;
	}
	return 0;
}