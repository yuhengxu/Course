/***************************************************************************************
情况一：假设只有一颗棋子，先手必输
情况二：假设有两颗棋子，先手只需要拿走一颗，则后手面对的就是情况一，后手必输
情况三：假设有三颗棋子，先手只要拿走两颗棋子，则后手面对的还是情况一，后手必输
情况四：假设有四颗棋子，先手无论拿走1颗还是两颗棋子，后手面对的及为情况二三，先手必输
如此往复，得到规律，假设有n个棋子，限制每次取k个棋子，n mod（k+1）即可
******************************************************************************************/


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


int main()
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		int ans;
		scanf("%d", &ans);
		if (ans % 3 == 1)printf("0\n");
		else if (ans % 3 == 2)printf("1\n");
		else printf("2\n");
	}
	return 0;
}