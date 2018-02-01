#include"cstdio"//标准输入输出
#include"algorithm"//算法
#include"cstring"//字符串函数
#include"string"//串的各种东西

using namespace std;
typedef long long ll;
const int maxn = 1500+10;
const int INF = 0x3f3f3f3f;

int n, f, d, p;
int father[maxn], dp[maxn][2], vis[maxn];
void init()
{
	memset(father, INF, sizeof(father));
	memset(vis, 0, sizeof(vis));
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < n; i++)
		dp[i][1] = 1;
}
void Bulid_Tree()
{
	for (int i = 0; i < n; i++)//录入每个节点的子节点
	{
		scanf("%d:(%d)",&f, &d);
		if (d == 0)continue;
		for (int j = 0; j < d; j++)
		{
			scanf("%d", &p);
			father[p] = f;
		}
	}
}
void dfs(int node)
{
	vis[node] = 1;
	for (int i = 0; i < n; i++)
		if (!vis[i]&&father[i] == node)
		{
			dfs(i);
			dp[node][1] += min(dp[i][0], dp[i][1]);//如果node放，则i放可不放，求最小
			dp[node][0] += dp[i][1];//如果node部放，则i必须放，否则会漏掉一条边
		}
}
int main()
{
	while (~scanf("%d", &n))//第一组用例
	{
		init();
		Bulid_Tree();
		int root;
		for (int i = 0; i < n; i++)
			if (father[i] == INF)
			{
				root = i;
				break;
			}

		dfs(root);
		printf("%d\n", min(dp[root][1], dp[root][0]));
	}

	return 0;
}