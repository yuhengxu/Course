#include<stdio.h>
int gcd(int a, int b)
{
	return b ? gcd(b, a%b) : a;
}
int main()
{
	long long s, n, m;
	while (scanf("%lld%lld%lld", &s, &n, &m) != EOF)
	{
		if (s & 1)
		{
			printf("ZGQ drinks off !\n");
			continue;
		}
		if (s / gcd(n, m) & 1)
		{
			printf("ZGQ drinks off !\n");
			continue;
		}
		printf("%d\n", s / gcd(n, m) - 1);
	}
}