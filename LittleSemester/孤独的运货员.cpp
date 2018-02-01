#include <stdio.h>
#include <string.h>
#include<stdlib.h>
int quick[110][1010], front[110], rear[110], Q;
int n = 0, sum = 0, ans = 0, top = 0, max = 0;
int s[110];
int cmp(const void *a, const void *b)
{
	return *(int  *)a - *(int *)b;
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d", &n, &max, &Q);
		sum = 0;
		for (int row = 1; row <= n; row++)
		{
			int total;
			scanf("%d", &total);
			sum += total;
			front[row] = rear[row] = 0;
			for (int j = 1; j <= total; j++) scanf("%d", &quick[row][rear[row]++]);
		}
		ans = 0, top = 0;
		int i = 0;
		if (top == 0)
		{
			int a[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1,0 };
			qsort(a, 10, sizeof(a[0]), cmp);
		}
		while (sum)
		{
			if (i == n) i = 1;
			else i++;
			ans += 2;
			while (top && rear[i] - front[i] < Q)
			{
				if (s[top] == i) top--, sum--;
				else quick[i][rear[i]++] = s[top--];
				ans++;
			}
			while (top && s[top] == i) top--, sum--, ans++;
			while (top < max && front[i] < rear[i])
			{
				s[++top] = quick[i][front[i]++];
				ans++;
			}
		}
		printf("%d\n", ans - 2);
	}
	return 0;
}