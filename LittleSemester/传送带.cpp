#include<stdio.h>
int main()
{
	int T, i, n;
	double X=0, W=0, R=0, t=0, time=0;
	double speed[105] = { 0 };
	scanf_s("%d", &T);
	for (i = 0; i < T; i++)
	{
		scanf_s("%lf%lf%lf%lf%d",&X,&W,&R,&t,&n);
		int row, b, e, v;
		speed[0] = X;
		for (row = 0; row < n; row++)
		{
			scanf_s("%d%d%d", &b, &e, &v);
			speed[v] += e - b;
			speed[0] -= e - b;
		}
		for (v = 0; v < 105; v++)
		{
			if (speed[v] = !0 && t*(R + v)>speed[v])
			{
				time += speed[v] / (R + v);
				t-= speed[v] / (R + v);
			}
			else if (speed[v] = !0)
			{
				time += (speed[v] - t*(R + v)) / (v + W) + t;
				t = 0;
			}
		}
		printf("%.6lf\n",time);
	}
}