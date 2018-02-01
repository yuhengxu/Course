#include <stdio.h>
#include <stdlib.h>
#define N 10005

int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;//从小到大排序
}

int main()
{
	int n, ans = 0;
	int a[N] = { 0 };
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf_s("%d", &a[i]);
	qsort(a + 1, n, sizeof(a[1]), cmp);

	int i, j;

	for (i = 1; i < n; i++)//总共合并n-1次
	{
		a[i] += a[i + 1];//合并前两个，把和赋值给前边那个
		ans += a[i];//累加
		for (j = i + 2; j <= n && a[j] < a[i]; j++)//从当前位置后两个位置开始比较，找到比当前位置大的数位置
		{
			a[j - 1] = a[j];//前移
		}
		a[j - 1] = a[i];//把当前数插入
	}

	printf("%d\n", ans);

	return 0;
}
