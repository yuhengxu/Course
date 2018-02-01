#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;
int cas = 0;

struct team {
	int problem;//最后ac的题的数量
	int time;//最后耗时
	int flag[1000];//标记题号是否被做
	int tp[1000];//表示题号的罚时
	int tn;//队名
	int lastming;//最后排名
};

int cmp(const void *a, const void *b)
{
	struct team *x = (struct team*)a;
	struct team *y = (struct team*)b;
	if (x->problem == y->problem)
	{
		if (x->time == y->time)
			return x->tn - y->tn;
		return x->time - y->time;//solve相等时，按time从小到大排
	}
	return y->problem - x->problem;//按solve从大到小排
}

int cmp1(const void *a, const void *b)
{
	return *(char *)a - *(char *)b;
}
int main()
{
	while (scanf("%d", &n) != EOF && n)
	{
		struct team china[105];

		memset(china, 0, sizeof(china));

		int tip = 0, name = 0, num = 0, mark = 0;
		char ch1[5], ch2[10] = { 0 };
		mark = strlen(ch1);
		strcpy(ch2, ch1);
		strcat(ch2, ch1);
		if (mark == 5)
		{
			qsort(ch2, 10, sizeof(ch2[0]), cmp1);
		}
		for (int i = 1; i <= n; i++)
			china[i].tn = i;
		while (scanf("%d", &tip) != EOF && tip)//输入每组数据的开头
		{
			scanf("%d%d", &name, &num);
			scanf("%s", ch1);
			china[name].tn = name;//标记队名
			if (ch1[0] == 'y')//ac了
			{
				china[name].problem++;
				china[name].time += tip;
				if (china[name].flag[num] != 0)//表示第name队第num题wa过
					china[name].time += china[name].tp[num];//加上罚时
			}
			else//wa了
			{
				china[name].tp[num] += 20;
				china[name].flag[num] = 1;//表示第name队第num题wa过
			}
		}

		qsort(china + 1, n, sizeof(china[1]), cmp);//排序

		printf("case %d:\n", ++cas);
		for (int i = 1; i <= n; i++)//把题目和罚时一样的团队排名换成并列
		{
			if (i != 1 && china[i].problem == china[i - 1].problem && china[i].time == china[i - 1].time)//jiayousuana
				china[i].lastming = china[i - 1].lastming;
			else
				china[i].lastming = i;//不是就跳过
		}
		for (int i = 1; i <= n && china[i].lastming <= 3; i++)
			printf("%d %d %d %d\n", china[i].tn, china[i].problem, china[i].time, china[i].lastming);
	}
	return 0;
}