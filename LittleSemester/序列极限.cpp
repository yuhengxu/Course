#include <stdio.h>
#include <string.h>
int str[500010], n;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &str[i]);
	int len = 1, ans = 0, i = 0;
	for (i = 2; i <= n; i++)
	{
		if (str[i] != str[i - 1])
		{
			len++;
		}
		else
		{
			ans = ans > (len / 2 + len % 2 - 1) ? ans : (len / 2 + len % 2 - 1);
			if (len & 1)for (int j = i - 2; j > i - len; j--) str[j] = str[i - 1];
			else
			{
				int t = len / 2;
				for (int j = i - 2; j >= i - t; j--) str[j] = str[i - 1];
				for (int j = i - len + 1; j < i - t; j++) str[j] = str[i - len];
			}
			len = 1;
		}
	}
	ans = ans >(len / 2 + len % 2 - 1) ? ans : (len / 2 + len % 2 - 1);
	if (len & 1)for (int j = i - 2; j > i - len; j--) str[j] = str[i - 1];
	else
	{
		int t = len / 2;
		for (int j = i - 2; j >= i - t; j--) str[j] = str[i - 1];
		for (int j = i - len + 1; j < i - t; j++) str[j] = str[i - len];
	}
	printf("%d\n", ans);
	for (int i = 1; i < n; i++) printf("%d ", str[i]);
	printf("%d\n", str[n]);
}