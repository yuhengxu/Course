#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct record
{
	int s;
	int w;
	int step;
	int bank;
}form;
form now;
form list[40005];
int save[2][205][205];
int x, y, n, h, t;
int bfs()
{
	memset(save, 0, sizeof(save));
	h = t = 1;
	list[1].s = x;
	list[1].w = y;
	list[1].step = 0;
	list[1].bank = 0;
	save[0][x][y] = 1;
	t++;
	while (h != t)
	{
		if (list[h].s == x&&list[h].w == y&&list[h].bank == 1) return list[h].step;
		if (list[h].bank == 1) now.bank = 0;
		else now.bank = 1;
		for (int i = 0; i <= (list[h].s>n ? n : list[h].s); i++)
		{
			for (int j = 0; j <= (list[h].w>n ? n : list[h].w); j++)
			{
				if ((list[h].s - i)<(list[h].w - j) && list[h].s - i != 0)   continue;
				if ((i < j && i != 0) || (i + j == 0) || (i + j > n)) continue;
				now.s = x - list[h].s + i;
				now.w = y - list[h].w + j;
				now.step = list[h].step + 1;//交换位置
				if (save[now.bank][now.s][now.w] == 1) continue;
				if ((now.s<now.w) && now.s != 0) continue;
				else
				{
					save[now.bank][now.s][now.w] = 1;
					list[t].s = now.s;
					list[t].w = now.w;
					list[t].step = now.step;
					list[t++].bank = now.bank;
				}
			}
		}
		h++;
	}
	return 0;
}
int main()
{
	int T, col = 0;
	scanf("%d", &T);
	while (T--)
	{
		if (col == 0)col == 1;
		scanf("%d%d%d", &x, &y, &n);
		if (n == 0 && col == 1)
		{
			printf("-1\n");
			continue;
		}
		if (x < y&&col == 0)
		{
			printf("-1\n");
			continue;
		}
		if (x < y&&col == 1)
		{
			printf("-1\n");
			continue;
		}
		int k = bfs();//广度搜索
		if (k) printf("%d\n", k);
		else printf("-1\n");
	}
	return 0;
}



