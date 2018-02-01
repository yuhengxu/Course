#include<stdio.h>
int main()
{
	int m, n,i,j,k,t;
	scanf("%d%d", &m, &n);
	int grass[105][105];
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &grass[i][j]);
			
	for(i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			int row = 1;
			for (k = 0; k < m; k++)
				if (grass[i][k] > grass[i][j])
				{
					row = 0;
					break;	
				}
				
			if (row) continue;
			
			int col = 1;
			for (k = 0; k < n; k++)
				if (grass[k][j] > grass[i][j])
				{
					col = 0;
					break;		
				}
					
			if (!col)
			{
				printf("NO\n");
				return 0;
			}
			
		}
	}
	printf("YES\n");
	
	return 0;
}
