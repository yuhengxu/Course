#include<cstdio>//标准输入输出
#include<cmath>//math
#include<iostream>//流输入输出
#include<algorithm>//算法
#include<stack>//栈
#include<functional>
#include<cstring>//字符串函数
#include<string>//串的各种东西
#include<vector>
#include<queue>//队列
#include<map>//映射,关联容器，一对一
#include<set>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const double esp = 1e-6;
#define maxn 1000
#define INF 0x3f3f3f3f
#define con 5
map<string, string>::iterator it;//迭代器 

int dui[maxn];
int main()
{
	int n;
	while (scanf("%d", &n))
	{
		if (n == 0)break;
		scanf("%d", &dui[1]);
		int ans = dui[1];
		for (int i = 2; i <= n; i++)
		{
			scanf("%d", &dui[i]);
			ans ^= dui[i];
		}
		if (ans != 0)
		{
			int tip = 0, sum = 0;
			while (ans >= 1)
			{
				ans /= 2;
				tip++;
			}


			int temp = 1 << (tip - 1);
			for (int i = 1; i <= n; i++)
				if (temp&dui[i])
					sum++;

			printf("%d\n", sum);

		}
		else printf("0\n");
	}


	return 0;
}