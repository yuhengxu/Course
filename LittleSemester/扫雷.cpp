#include<stdio.h>
int main()
{
	int i, j, num=0;
	for (; 1;)
	{
		
		char map[50][50] = { 0 }, ans[50][50] = { 0 };
		int row, col;
		scanf("%d%d", &row, &col);
		if (row == 0 && col == 0)
			break;
		else
			num++;

		for (i = 0; i < row;i++)
			scanf("%s",&map[i]); 

		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
			{
				if (map[i][j] == '*')
					ans[i][j] = '*';
				else
				{
					int cont = 0;
					if (map[i - 1][j - 1] == '*')
						cont++;
					if (map[i - 1][j] == '*')
						cont++;
					if (map[i - 1][j + 1] == '*')
						cont++;
					if (map[i][j - 1] == '*')
						cont++;
					if (map[i][j + 1] == '*')
						cont++;
					if (map[i][j + 1] == '*')
						cont++;
					if (map[i + 1][j - 1] == '*')
						cont++;
					if (map[i + 1][j] == '*')
						cont++;
					if (map[i + 1][j + 1] == '*')
						cont++;
					ans[i][j] = cont;
				}
			}

		printf("Field #%d:\n", num);
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
			{
				if(ans[i][j]=='*')
				{
					if(j==col-1)
					{
						printf("%c\n",ans[i][j]);
					}
					else
						printf("%c",ans[i][j]);
				}
				else
				{
					if(j==col-1)
					{
						printf("%d\n",ans[i][j]);
					}
					else
						printf("%d",ans[i][j]);
				}
			}
	}
}
