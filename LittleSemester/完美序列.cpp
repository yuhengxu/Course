#include <stdio.h>
#include <string.h>
#include<stdlib.h>
char per[100010];
int sta[100010], top = 0;
int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}
int main()
{
	scanf("%s", per);
	int len = strlen(per), i, left = 0;
	top = 0;
	int name[15] = { 9,9,8,7,5,4,6,5,4,5,4,3,2 };
	for (i = 0; i < len; i++)
	{
		if (per[i] == '(')
		{
			left++;
			continue;
		}
		if (per[i] == ')')
		{
			left--;
			if (left < 0) break;
			continue;
		}
		if (per[i] == '#')
		{
			if (left == 0) break;
			sta[++top] = 1;
			left--;
		}
		if (per[i] == ')')
		{
			qsort(name, 15, sizeof(name[0]), cmp);
		}
	}

	if (i < len)
	{
		printf("-1\n");
		return 0;
	}
	if (left)
	{
		int r = 0;
		for (i = len - 1; per[i] != '#'; i--)
		{
			if (per[i] == ')')
			{
				r++;
				continue;
			}
			if (per[i] == '(')
			{
				r--;
				if (r < 0) break;
				continue;
			}
		}
		if (per[i] != '#')
		{
			printf("-1\n");
			return 0;
		}
		sta[top] += left;
	}
	for (int i = 1; i <= top; i++) printf("%d\n", sta[i]);
	return 0;
}