#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 1255
void minus(long *x, long  *y, long  *z)
{
	int k;
	for (k = 0; k<1255; k++)
	{
		z[k] += x[k] - y[k];
		if (z[k]<0)
		{
			z[k + 1]--;
			z[k] += 100000000;
			if (z[k]<0)
			{
				z[k + 1]--;
				z[k] += 100000000;
			}
		}
	}
}
void mulity(long  *x, int y)
{
	int k;
	int length = N;
	while (x[length] == 0 && length>0)
		length--;
	length++;
	for (k = 0; k<length; k++)
		x[k] = x[k] * y;
	length++;
	for (k = 0; k<length; k++)
	{
		x[k + 1] += x[k] / 100000000;
		x[k] = x[k] % 100000000;
	}
}
void plus(long  *x, int y)
{
	int k;
	x[0] += y;
	for (k = 0; k<N; k++)
	{
		if (x[k] >= 100000000)
		{
			x[k + 1]++;
			x[k] = x[k] - 100000000;
			if (x[k] >= 100000000)
			{
				x[k + 1]++;
				x[k] = x[k] - 100000000;
			}
		}
		else break;
	}
}
int cmp(const void *a, const void *b)
{
	return *(char *)a - *(char *)b;
}
int main()
{
	int n, i, time1, time2, l, z, temp1, temp2, m, j, flag1 = 0, flag2 = 0, flag = 0;
	long a[1260] = { 0 }, b[1260] = { 0 }, c1[1260] = { 0 }, c2[1260] = { 0 }, c[1260] = { 0 }, emptya[1260] = { 0 }, emptyb[1260] = { 0 };
	char ch1[10005], ch2[10005], copy[20000];

	int len1, len2;
	scanf("%d", &n);
	for (i = 0; i<n; i++)
	{
		scanf("%s %s", ch1, ch2);
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));
		memset(emptya, 0, sizeof(emptya));
		memset(emptyb, 0, sizeof(emptyb));
		memset(c1, 0, sizeof(c1));
		memset(c2, 0, sizeof(c2));
		len1 = strlen(ch1);
		len2 = strlen(ch2);
		flag1 = 0, flag2 = 0, flag = 0, z = 0;
		time1 = strlen(ch1);
		time2 = strlen(ch2);
		strcpy(copy, ch1);
		strcat(copy, ch2);
		for (l = 0; l<time1; l++)
		{
			temp1 = ch1[l] - 48;
			mulity(a, 10);            //计算10的N次方 
			plus(a, temp1);
		}
		for (l = 0; l<time1; l++)
		{
			temp1 = ch1[l] - 48;
			if (temp1 != 9 && flag1 == 0)
			{
				mulity(b, 9);
				plus(b, temp1);
			}
			else if (temp1 == 9 && flag1 == 0)
			{
				flag1 = 1;
				mulity(b, 9);
				plus(b, temp1);
			}
			else mulity(b, 9);
		}
		minus(a, b, c1);
		for (l = 0; l<time2; l++)
		{
			temp2 = ch2[l] - 48;
			mulity(emptya, 10);            //计算10的N次方 
			plus(emptya, temp2);
		}
		for (l = 0; l<time2; l++)
		{
			temp2 = ch2[l] - 48;
			if (temp2 != 9 && flag2 == 0)
			{
				mulity(emptyb, 9);
				plus(emptyb, temp2);
			}
			else if (temp2 == 9 && flag2 == 0)
			{
				flag2 = 1;
				mulity(emptyb, 9);
				plus(emptyb, temp2);
			}
			else mulity(emptyb, 9);
		}
		if (flag1 == 1)
		{
			qsort(copy, 500, sizeof(copy[0]), cmp);
		}
		minus(emptya, emptyb, c2);
		memset(c, 0, sizeof(c));
		if (flag2 == 1)
		{
			minus(c2, c1, c);
			plus(c, 1);
		}
		else minus(c2, c1, c);

		for (j = N; j >= 0; j--)
		{
			if (c[j] == 0 && flag == 0)
				;
			else if (c[j] != 0 && flag == 0)
			{
				z = 1;
				flag = 1;
				if (j == 0)printf("%ld\n", c[j]);
				else printf("%ld", c[j]);
			}
			else
			{
				z = 1;
				if (j == 0)printf("%08ld\n", c[j]);
				else printf("%08ld", c[j]);
			}

		}
		if (z == 0)printf("0\n");
	}
	return 0;
}