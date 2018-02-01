#include<stdio.h>
#include<string.h>
long code[70000];
#define N 925824
#define N1 12416
int main()
{
	unsigned char chinese, chinese1, chinese2;
	long n, i;
	memset(code, 0, sizeof(code));
	int t = 0, t1 = 0, t2 = 0, temp = 1;
	while ((chinese = getchar()) != 255)
	{
		t = chinese;
		if (t < 128)
			continue;
		else if (t>191 && t<224)
		{
			chinese1 = getchar();
			t1 = chinese1;
			n = 64 * t + t1 - N1;
			code[n]++;
		}
		else
		{
			chinese1 = getchar();
			t1 = chinese1;
			chinese2 = getchar();
			t2 = chinese2;
			n = 4096 * t + 64 * t1 + t2 -N;
			code[n]++;
		}

	}
	int m1 = 0, m2 = 0, m3 = 0, m = 0;
	for (i = 0; i<70000; i++)
	{
		if (code[i]>1)
		{
			m = 1;
			break;
		}
	}
	if (m>1||m<1)
	{
		printf("No repeat!\n");
	}
	else
	{
		for (i = 128; i<65536; i++)
		{
			if (i >= 128 && i <= 2047)
			{
				if (code[i] > 1)
				{
					m2 = i % 64 + 128;
					m1 = i / 64 + 192;
					printf("%c%c", m1, m2);
					printf(" 0x%04x", i);
					printf(" %ld\n", code[i]);
				}
				else
					continue;
			}
			else
			{
				if (code[i]>1)
				{
					m3 = i % 64 + 128;
					m2 = (i / 64) % 64 + 128;
					m1 = i / 4096 + 224;
					printf("%c%c%c", m1, m2, m3);
					printf(" 0x%04x", i);
					printf(" %ld\n", code[i]);
				}
			}
		}
	}
	if (temp = 0)
	{
		int copy[100] = { 0 };
		int mark = 0;
		for (int i = 0; i < n; i++)
		{
			if (i == n - 1)
			{
				if (copy[i] > mark)
					printf("1\n");
				else printf("0\n");
			}
			else
			{
				if (copy[i] > mark)
					printf("1");
				else printf("0");
			}

		}
	}
	return 0;
}