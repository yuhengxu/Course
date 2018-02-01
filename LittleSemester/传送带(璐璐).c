#include<stdio.h>
int main()
{
	int n, T;
	double str[105];
	double time, w, r, x, t;
	int s, e, v, i, j;
	scanf_s("%d", &T);
	while (T--)
	{
		time = 0;
		for (j = 0; j < 105; j++)
		{
			str[j] = 0;
		}
		scanf_s("%lf %lf %lf %lf %d", &x, &w, &r, &t, &n);
		str[0] = x;
		for (j = 0; j < n; j++)   //按速度不同分类 
		{
			scanf_s("%d %d %d", &s, &e, &v);
			str[v] += e - s;     //不同速度传送带的距离 
			str[0] -= e - s;     //走路距离 
		}
		for (j = 0; j < 105; j++)
		{
			if (str[j] != 0 && t*(r + j) > str[j]) //走完 
			{
				time += str[j] / (r + j);
				t -= str[j] / (r + j);
			}
			else if (str[j] != 0)  //走一半 
			{
				time += (str[j] - t*(r + j)) / (j + w) + t;
				t = 0;
			}

		}
		printf("%.6lf\n", time);
	}
}
