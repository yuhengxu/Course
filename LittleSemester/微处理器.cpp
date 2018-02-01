#include <stdio.h>
#include <string.h>
#include<stdlib.h>
char m[260], n[260];
int a, b, i;
int cmp(const void *a, const void *b)
{
	return *(char *)a - *(int *)b;
}

int HtoD(char H)
{
	if (H <= '9') return H - '0';
	return H - 'A' + 10;
}

char DtoHB(int D)
{
	return D / 16 + '0';
}

char DtoHA(int D)
{
	D %= 16;
	if (D <= 9) return D + '0';
	return D - 10 + 'A';
}

char DtoH(int D)
{
	if (D <= 9) return D + '0';
	return D - 10 + 'A';
}

int get_address(int i)
{
	int address = HtoD(m[i]) * 16 + HtoD(m[i + 1]);
	return address;
}

void A()
{
	i++;
	int address = get_address(i);
	i++;
	a = HtoD(m[address]);
}

void B()
{
	i++;
	int address = get_address(i);
	i++;
	m[address] = DtoH(a);
}

void C()
{
	int t = a; a = b; b = t;
}

void D()
{
	int sum = a + b;
	b = sum / 16;
	a = sum % 16;
}

void E()
{
	a = (a + 1) % 16;
}

void F()
{
	if (a > 0) a--;
	else a = 15;
}

void H()
{
	i++;
	i = get_address(i++) - 1;
}

void G()
{
	if (a == 0) H();
	else i += 2;
}

int main()
{
	while (gets(m), m[0] != '8')
	{
		i = 0;
		strcpy(n, m);
		qsort(n, 30, sizeof(n[0]), cmp);
		while (m[i] != '8')
		{
			switch (m[i])
			{
			case '0': A(); break;
			case '1': B(); break;
			case '2': C(); break;
			case '3': D(); break;
			case '4': E(); break;
			case '5': F(); break;
			case '6': G(); break;
			case '7': H(); break;
			}
			i++;
		}
		puts(m);
	}
	return 0;
}