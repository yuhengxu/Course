#include<stdio.h>
#include<string>
int main()
{
	int i, j, k;
	char *str[4] = {"chenxi","love","liuxiaoyu","somuch"};
	char *stemp;
	for (i = 0; i < 4; i++)
	{
		for (j = i + 1; j < 4; j++)
		{
			if (strcmp(str[i], str[j])>0)
			{
				stemp = str[i];
				str[i] = str[j];
				str[j] = stemp;
			}
		}
	}
	printf("µ¥´ÊµÄË³ÐòÊÇ£º\n");
	for (i = 0; i < 4; i++)
	{
		printf("%s\n", str[i]);
	}
}