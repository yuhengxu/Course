#include<stdio.h>
#include<string.h>
int find(char c[])
{
	int flag = 0;
	for (int i = 0; c[i] != '\0'&&flag == 0; i++)
		if (c[i] == '.')	flag = 1;
	return(flag);
}
int find2(char c[])
{
	int num = 0, flag = 0;
	for (int i = 0; c[i] != '\0'&&flag == 0; i++)
		if (c[i] == '.')	num = i, flag = 1;
	return(num);
}
int main()
{
	int i, l1, l2, flag1, flag2, temp1, temp2, max;
	char a[1000], b[1000];
	scanf_s("%s", a);
	scanf_s("%s", b);
	l1 = strlen(a);
	l2 = strlen(b);
	flag1 = find(a), flag2 = find(b);
	if (flag1 == 0)
	{
		a[l1] = '.';
		a[l1 + 1] = '\0';
		l1++;
	}
	if (flag2 == 0)
	{
		b[l2] = '.';
		b[l2 + 1] = '\0';
		l2++;
	}//²¹. 
	temp1 = find2(a), temp2 = find2(b);
	if (temp1>temp2)
	{
		for (i = l2 - 1; i >= 0; i--)
			b[i + temp1 - temp2] = b[i];
		for (i = 0; i<temp1 - temp2; i++)
			b[i] = '0';
		l2 = l2 + temp1 - temp2;
	}
	if (temp2>temp1)
	{
		for (i = l1 - 1; i >= 0; i--)
			a[i + temp2 - temp1] = a[i];
		for (i = 0; i<temp2 - temp1; i++)
			a[i] = '0';
		l1 = l1 + temp2 - temp1;
	}//¶ÔÆë. 
	if (l1>l2)
	{
		for (i = l2; i<l1; i++)
			b[i] = '0';
		max = l1;
	}
	else
	{
		for (i = l1; i<l2; i++)
			a[i] = '0';
		max = l2;
	}//²¹È«0 
	for (i = max; i>0; i--)
		a[i] = a[i - 1], b[i] = b[i - 1];
	a[i] = '0', b[i] = '0';
	max += 1;//ºóÒÆ£¬·ÀÖ¹Òç³ö 
	for (i = 0; i<max; i++)
		a[i] += b[i];
	for (i = max - 1; i >= 0; i--)
	{
		if (a[i] == 92) a[i] = '.';
		else if (a[i] - 96 >= 10)
		{
			if (a[i - 1] == 92)
			{
				a[i] -= 10;
				a[i - 2]++;
			}
			else
			{
				a[i] -= 10;
				a[i - 1] += 1;
			}
		}
	}
	for (i = max - 1; i >= 0; i--)
		if (a[i] >= 96) a[i] -= 48;
	for (i = 0; a[i] == 48; i++);
	if (a[i] == '.')
	{
		a[i - 1] = '0';
		i--;
	}
	int x = i;
	for (i = max - 1; a[i] == 48; i--);
	if (a[i] == '.') i--;
	int y = i;
	for (i = x; i <= y; i++)	printf("%c", a[i]);
	printf("\n");
	return(0);
}
