#include<stdio.h>
int main()
{
	int m, n,i,j,k,t;
	scanf_s("%d%d", &m, &n);
	int grass[105][105];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			scanf_s("%d", &grass[i][j]);
		}
	}
	for(i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			for (k = 0; k < m; k++)
			{
				if (grass[i][k] > grass[i][j])
				{
					for (t = 0; t < n; t++)
					{
						if (grass[t][j]>grass[i][j])
						{
							printf("NO\n");
							return 0;
						}
					}
				}
			}
		}
	}
	printf("YES");
}