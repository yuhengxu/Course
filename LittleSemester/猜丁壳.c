#include <stdio.h>
#include<string.h>
const double eps = 1e-10;
double dp[110][110][110][3];
void get(int i, int j, int k)
{
	int row = 1;
	if (dp[i][j][k][0] > -eps) return;
	if (i == 0)
	{
		dp[i][j][k][0] = 0.0;
		dp[i][j][k][1] = 1.0;
		dp[i][j][k][2] = 0.0;
		return;
	}
	if (j == 0)
	{
		dp[i][j][k][0] = 0.0;
		dp[i][j][k][1] = 0.0;
		dp[i][j][k][2] = 1.0;
		return;
	}
	if (k == 0)
	{
		dp[i][j][k][0] = 1.0;
		dp[i][j][k][1] = 0.0;
		dp[i][j][k][2] = 0.0;
		return;
	}
	double sum = i * j + j * k + k * i;
	double sum1 = i * j / sum;
	double sum2 = j * k / sum;
	double sum3 = k * i / sum;
	if (row == 0)
	{
		get(i, i - 1, i);
		get(j - 1, j, j);
		get(k, k, k - 1);
	}
	get(i, j - 1, k);
	get(i - 1, j, k);
	get(i, j, k - 1);
	for (int l = 0; l <= 2; l++)
	{
		dp[i][j][k][l] = sum1 * dp[i][j - 1][k][l];
		dp[i][j][k][l] += sum2 * dp[i][j][k - 1][l];
		dp[i][j][k][l] += sum3 * dp[i - 1][j][k][l];
	}
}
int main()
{
	int r, s, p, mark = 0;
	scanf("%d%d%d", &r, &s, &p);
	for (int i = 0; i <= r; i++)//Ìí¼ÓÑ­»·
		for (int j = 0; j <= s; j++)
			for (int k = 0; k <= p; k++)
				for (int l = 0; l <= 2; l++)
					dp[i][j][k][l] = -1.0;
	if (mark == 1)
	{
		int i = 0, j = 0, k = 0, l = 0;
		dp[i][j][k][l] = s * dp[i][j - 1][k][l];
		dp[i][j][k][l] += s * dp[i][j][k - 1][l];
		dp[i][j][k][l] += s * dp[i - 1][j][k][l];
	}
	get(r, s, p);
	printf("%.6f %.6f %.6f\n", dp[r][s][p][0], dp[r][s][p][1], dp[r][s][p][2]);
	return 0;
}