#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int change(char a[])
{
	if (strlen(a) != strlen(key[0]))
	{
		return 0;
	}
	else
	{
		int i, j;
		for (i = 0; i<strlen(a); i++)
		{
			if (key[0][i] == ' '&&a[i] != ' ')
			{
				return 0;
			}
			else if (key[0][i] == ' '&&a[i] == ' ')
			{
				continue;
			}
			for (j = 0; j<i; j++)
			{
				if (a[j] == a[i] && key[0][j] != key[0][i]) return 0;
				if (key[0][j] == key[0][i] && a[i] != a[j]) return 0;
			}
			key[1][i] = a[i];
		}
	}
	return 1;
}
void translate(char a)
{
	if (a == ' ')
		printf(" ");
	else
	{
		int i;
		for (i = 0; i<strlen(key[0]); i++)
		{
			if (a == key[1][i])
			{
				printf("%c", key[0][i]);
				break;
			}
		}
	}
}
int num;
char secret[101][201], key[2][201], lock[201];
int main()
{
	int T;
	scanf("%d", &T);
	getchar();
	gets_s(key[0]);
	gets_s(lock);
	while (T--)
	{
		memset(secret, '\0', sizeof(secret));
		num = 0;
		gets_s(secret[num++]);
		while (strlen(secret[num - 1]) != 0)
			gets(secret[num++]);
		num--;
		int i;
		int jud = 0;
		for (i = 0; i<num; i++)
		{
			jud = change(secret[i]);
			if (jud)
			{
				break;
			}
		}
		if (!jud)
			printf("No solution.\n");
		else
		{
			int j;
			for (i = 0; i<num; i++)
			{
				for (j = 0; j<strlen(secret[i]); j++)
				{
					translate(secret[i][j]);
				}
				printf("\n");
			}
		}
		if (T != 0)
			printf("\n");
	}
}
