#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 1000000;
struct book
{
	int number;
	int tel;
}Node[2005];
char tip(char c)
{
	switch (c)
	{
	case '0': return '0';
	case '1': return '1';
	case '2':
	case 'A':
	case 'B':
	case 'C': return '2';
	case '3':
	case 'D':
	case 'E':
	case 'F': return '3';
	case '4':
	case 'G':
	case 'H':
	case 'I': return '4';
	case '5':
	case 'J':
	case 'K':
	case 'L': return '5';
	case '6':
	case 'M':
	case 'N':
	case 'O': return '6';
	case '7':
	case 'P':
	case 'R':
	case 'S': return '7';
	case '8':
	case 'T':
	case 'U':
	case 'V': return '8';
	case '9':
	case 'W':
	case 'X':
	case 'Y': return '9';
	default: return '#';
	}
}
int search(char s[])
{
	int len = strlen(s), i = 0;
	while (i < len && s[i] == '-') i++;
	char c = tip(s[i]);
	if (c != '3' && c != '6') return 0;

	int sum = 1;
	for (i++; i < len; i++)
	{
		if (s[i] == '-') continue;
		if (tip(s[i]) == '#') return 0;
		sum++;
	}
	if (sum != 7) return 0;
	return 1;
}
void trans(char s[])
{
	int len = strlen(s), t[10] = { 0 }, p = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '-') continue;
		t[p++] = tip(s[i]);
	}

	for (int i = 0; i <= 6; i++) s[i] = t[i];
	s[7] = '\0';
}
int cmp(const void*a, const void*b)
{
	return((struct book*)a)->number - ((struct book*)b)->number;
}
void chachong(char a)
{
	int leng = strlen(a);
}
unsigned char tel[2][125010];
int sum = 0;
int main()
{
	memset(tel, 0, sizeof(0));
	int error = 0;
	char ch[25];
	printf("Error:\n");
	while (~scanf("%s", ch))
	{
		if (!search(ch))
		{
			printf("%s\n", ch);
			error = 1;
			continue;
		}
		trans(ch);
		int number = atoi(ch);
		int head = number / N;
		head = (head == 3) ? 0 : 1;
		int body = number%N;
		if ((tel[head][body / 8] & (1 << (body % 8))) == 0)
		{
			tel[head][body / 8] |= (1 << (body % 8));
			continue;
		}
		int row = 0;
		while (row < sum&&number != Node[row].number)
			row++;
		if (row >= sum)
		{
			Node[sum].number = number;
			Node[sum].tel = 1;
			sum++;
		}
		else Node[row].tel++;
	}
	if (!error)printf("Not found.\n");
	printf("\n");

	printf("Duplication:\n");
	if (sum == 0)
	{
		printf("Not found.\n");
		return 0;
	}
	qsort(Node, sum, sizeof(Node[0]), cmp);
	for (int i = 0; i < sum; i++)
		printf("%03d-%04d %d\n", Node[i].number / 10000, Node[i].number % 10000, Node[i].tel + 1);
	return 0;
}