#include<cstdio>
#include<cmath>
#include<queue>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 100 + 10;

int n, m;
int startx, starty, endx, endy;
int map[maxn][maxn];
int dx[4] = { 0,-1,0,1 }, dy[4] = { -1,0,1,0 };
bool vis[maxn][maxn];
struct NODE
{
	int x, y, step;
	NODE() {};
	NODE(int _x, int _y, int step) :x(_x), y(_y), step(step) {};
};
int bfs()
{
	queue<NODE>que;
	while (!que.empty())que.pop();
	que.push(NODE(startx, starty, 0));
	vis[startx][starty] = true;
	while (!que.empty())//队列不为空就继续
	{
		NODE temp = que.front();
		que.pop();//队首元素出队
		if (temp.x == endx&&temp.y == endy)return temp.step;//到达终点就退出
		for (int i = 0; i < 4; i++)//朝四个方向走
		{
			int nx = temp.x + dx[i];
			int ny = temp.y + dy[i];
			if (nx<1 || nx>n || ny<1 || ny>m)continue;//越界就退出
			if (vis[nx][ny])continue;//重复点退出
			if (map[nx][ny])//弹簧
			{
				int nnx = nx, nny = ny;
				if (i == 0)
				{
					while (1)
					{
						nny -= map[nx][ny];//向下走
						if (nny < 1)//越界
						{
							nny = 1;
							break;
						}
						nx = nnx;
						ny = nny;
						if (!map[nx][ny])break;
					}
				}
				else if (i == 1)
				{
					while (1)
					{
						nnx -= map[nx][ny];
						if (nnx < 1)
						{
							nnx = 1;
							break;
						}
						nx = nnx;
						ny = nny;
						if (!map[nx][ny])break;
					}
				}
				else if (i == 2)
				{
					while (1)
					{
						nny += map[nx][ny];
						if (nny > m)
						{
							nny = m;
							break;
						}
						nx = nnx;
						ny = nny;
						if (!map[nx][ny])break;
					}
				}
				else
				{
					while (1)
					{
						nnx += map[nx][ny];
						if (nnx > n)
						{
							nnx = n;
							break;
						}
						nx = nnx;
						ny = nny;
						if (!map[nx][ny])break;
					}
				}
				que.push(NODE(nnx, nny, temp.step + 1));
				continue;
			}
			vis[nx][ny] = true;
			que.push(NODE(nx, ny, temp.step + 1));
		}
	}
	return INF;
}
int main()
{
	while (~scanf("%d %d", &n, &m))
	{
		memset(map, 0, sizeof(map));
		memset(vis, false, sizeof(vis));
		int x, a, b, p;
		scanf("%d", &x);
		while (x--)
		{
			scanf("%d %d %d", &a, &b, &p);
			map[a][b] = p;
		}
		scanf("%d %d", &startx, &starty);
		scanf("%d %d", &endx, &endy);
		int ans = bfs();
		if (ans == INF)printf("impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}
