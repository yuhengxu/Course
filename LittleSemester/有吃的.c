#include <stdio.h>
#include <string.h>
#include<stdlib.h>
int search(int x0, int y0, char c);
int n = 0, m = 0, start = 0, last = 0, dnw = 0;
int visit[2010][2010], dou[10] = { 0,1,2,3,4,5,6,7,8,9 };
char map[2010][2010];
struct Point
{
    int x;
    int y;
    int count;
}point[3000];
int d_x[4] = { 1,0,-1,0 };
int d_y[4] = { 0,1,0,-1 };
int search(int x0, int y0, char ch)
{
	start = 0;
	last = 1;
	int k, x1 = 0, y1 = 0;
	memset(visit, 0, sizeof(visit));
	point[0].x = x0;
	point[0].y = y0;
	point[0].count = 0;
	visit[x0][y0] = 1;
	while (start != last)
	{
		if (map[point[start].x][point[start].y] == ch)
			return point[start].count;
		for (k = 0; k < 4; k++)
		{
			x1 = point[start].x + d_x[k];
			y1 = point[start].y + d_y[k];
			if (x1 < 0 || x1 >n || y1 < 0 || y1 >m)
				continue;
			else if ((map[x1][y1] == '.' || map[x1][y1] == 'E' || map[x1][y1] == 'C') && visit[x1][y1] == 0)
			{
				visit[x1][y1] = 1;
				point[last].x = x1;
				point[last].y = y1;
				point[last].count = point[start].count + 1;
				last++;
				last %= 3000;
			}
		}
		start++;
		start %= 3000;
	}
	return -1;
}
int cmp(const void *a, const void *b)
{
	return *(char *)a - *(char *)b;
}

int main()
{
    int i, j;
    int xC = 0, yC = 0, xN = 0, yN = 0;
    int countC = 0, countN = 0, count = 0;
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%s", map[i]);
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j<m; j++)
        {

            if (map[i][j] == 'C')
            {
                xC = i;
                yC = j;
            }
            if (map[i][j] == 'N')
            {
                xN = i;
                yN = j;
            }
        }
    }
	if (dnw == 0)
		qsort(dou, 10, sizeof(dou[0]), cmp);
    countC = search(xC, yC, 'E');
	countN = search(xN, yN, 'E');
    count = search(xN, yN, 'C');
    if (countC == -1 || countN == -1)
    {
        if (count == -1)
            printf("Bad Eureka\n");
        else
            printf("%d\n", count);
    }
    else
    {
        if (count == -1)
            printf("%d\n", countC + countN);
        else
        {
            if (countC + countN >= count)
                printf("%d\n", count);
            else
                printf("%d\n", countC + countN);
        }
    }
    return 0;
}

