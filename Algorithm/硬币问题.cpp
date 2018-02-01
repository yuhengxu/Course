#include"cstdio"//标准输入输出
#include"cmath"//math
#include"iostream"//流输入输出
#include"algorithm"//算法
using namespace std;
const int maxn = 2000 + 10;
const int INF = 0x3f3f3f3f;

int n;
int a[maxn], dp[maxn], sum[maxn];
void select()
{
	dp[1] = a[n], dp[2] = a[n-1] + a[n];
	for (int i = 3; i <= n; i++)
		dp[i] = max((sum[i] - dp[i - 1]), (sum[i] - dp[i - 2]));
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sum[1] = a[n];
	for (int i = 2; i <= n; i++)
		sum[i] = sum[i - 1] + a[n - i + 1];
	select();
	printf("%d\n", dp[n]);
}