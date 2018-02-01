#include<stdio.h>
#include<string.h>
char key[205], scode[100][205] = { 0 }, ans[205], lock[205];
int i = 0;
int compare(char a[205], char b[205])
{
	for (int row = 0; row < strlen(a); row++)
	{
		if (a[row] == ' '&&b[row] != ' ')return 0;
		else if (a[row] != ' '&&b[row] == ' ')return 0;
	}
	for (int row = 0; row < strlen(a); row++)
	{
		if (a[row] == ' '&&b[row] == ' ')continue;
		if (ans[b[row]] != '\0')return 0;
		if(ans[b[row]]== '\0')ans[b[row]] = a[row];
	}
	return 1;
}
void translate(char s[205])
{
	for (int t = 0; t < strlen(s); t++)
	{
		if (s[t] == ' ')
			printf(" ");
		else printf("%c", ans[s[t]]);
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	getchar();
	gets_s(key);
	gets_s(lock);
	while (T--)
	{
		int tip = 1;
		memset(scode, '\0', sizeof(scode));
		memset(ans, '\0', sizeof(ans));
		gets_s(scode[i++]);
		while (strlen(scode[i-1]) != 0)
		{
			gets_s(scode[i++]);
			tip++;
		}
		i--;
		int row;
		for (row = 0; row < i; row++)
		{
			int mark = 0;
			if (strlen(scode[row]) == strlen(key))
				mark = compare(key, scode[row]);
			if (mark == 1)break;
		}
		if (row == i)printf("No solution.\n");
		else
		{
			for (row = 0; row < tip-1; row++)
			{
				translate(scode[row]);
				printf("\n");
			}
		}
		if (T > 1)printf("\n");
	}
	return 0;
}