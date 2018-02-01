#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	struct shalu
	{
		int t;
		int val;
	}stu[10005];


	int n; scanf("%d", &n);
	int i = 0, m = 0, j = 0, temp = 0, max = 0, flag = 0;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &stu[i].val);
	}
	for (i = 0; i < n; i++)
	{
		scanf("%d", &stu[i].t);
		if (stu[i].t > m) m = stu[i].t;
	}

	for (; m > 0; m--)
	{
		max = 0;  flag = -1;
		for (j = 0; j < n; j++)
		{
			if (stu[j].t == m)
			{
				stu[j].t = m - 1;
				if (stu[j].val > max)
				{
					max = stu[j].val;
					flag = j;
				}
			}
		}
		if (flag != -1)stu[flag].t = m;
		temp = temp + max;
	}
	printf("%d\n", temp);
}