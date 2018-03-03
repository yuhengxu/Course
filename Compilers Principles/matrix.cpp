#include<cstdio>
#include<cstdlib>
#include<ctime>

const int maxn = 300;

//随机数组arr1，arr2，结果数组arr3
int arr1[maxn][maxn], arr2[maxn][maxn], arr3[maxn][maxn];

int main()
{
	//计时
	clock_t start, end;
	start = clock();

	//初始化随机数组
	for (int i = 0; i < maxn; i++)
	{
		for (int j = 0; j < maxn; j++)
		{
			arr1[i][j] = rand() % 101;
			arr2[i][j] = rand() % 101;
		}
	}
	
	//初始化结果数组
	for (int i = 0; i < maxn; i++)
		for (int j = 0; j < maxn; j++)
			arr3[i][j] = 0;
	
	//矩阵乘法
	for (int i = 0; i < maxn; i++)
	{
		for (int j = 0; j < maxn; j++)
		{
			for (int k = 0; k < maxn; k++)
			{
				arr3[i][j] += arr1[i][k] * arr2[k][j];
			}
		}
	}

	/*
	//输出
	for (int i = 0; i < maxn; i++)
	{
		for (int j = 0; j < maxn; j++)
		{
			printf("%d ", arr3[i][j]);
		}
		printf("\n");
	}
	//getchar();
	*/

	end = clock();
	printf("C运行时间：%lfms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000.0);
	
	return 0;
}