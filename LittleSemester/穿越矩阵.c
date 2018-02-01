#include <stdio.h>
int main()
{
	int dp[15][110], map[15][110];
	int m, n;
	while (scanf("%d%d", &m, &n) != EOF)
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &dp[i][j]);

		for (int j = n - 2; j >= 0; j--)
		{
			for (int i = 0; i < m; i++)
			{
				int mark = 0x7f7f7f7f;
				map[i][j] = 0x7f7f7f7f;

				int t = (i - 1 + m) % m;
				if (dp[t][j + 1] < mark)
				{
					mark = dp[t][j + 1];
					map[i][j] = t;
				}
				else if (dp[t][j + 1] == mark)
				{
					map[i][j] = map[i][j] < t ? map[i][j] : t;
				}

				t = i;
				if (dp[t][j + 1] < mark)
				{
					mark = dp[t][j + 1];
					map[i][j] = t;
				}
				else if (dp[t][j + 1] == mark)
				{
					map[i][j] = map[i][j] < t ? map[i][j] : t;
				}

				t = (i + 1) % m;
				if (dp[t][j + 1] < mark)
				{
					mark = dp[t][j + 1];
					map[i][j] = t;
				}
				else if (dp[t][j + 1] == mark)
				{
					map[i][j] = map[i][j] < t ? map[i][j] : t;
				}

				dp[i][j] += mark;
			}
		}

		int mini = -1;
		for (int i = 0; i < m; i++)
			if (mini == -1 || dp[i][0] < dp[mini][0]) mini = i;

		printf("%d", mini + 1);
		int i = mini;
		for (int j = 0; j < n - 1; j++)
		{
			printf(" %d", map[i][j] + 1);
			i = map[i][j];
		}
		printf("\n");
		printf("%d\n", dp[mini][0]);
	}
}