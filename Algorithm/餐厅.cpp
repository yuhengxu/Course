#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
const int maxn = 200+10;
int main()
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		char ch[maxn];
		int ans = 0;
		int in = 0, out= 0;
		scanf("%s", ch);
		for (int i = 0; i < strlen(ch); i++)
		{
			if (ch[i] == '+')
			{
				if (out)
				{	
					out--;
					in++;
				}
				else
				{
					in++;
					ans++;
				}
			}
			else
			{
				if (in)
				{
					in--;
					out++;
				}
				else
				{
					out++;
					ans++;
				}
			}
		}
		
		printf("%d\n", ans);
	}
	return 0;
}