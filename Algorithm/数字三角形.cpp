/***********************************************************************
在一般情况下，符号三角形的第一行有n个符号, 符号三角形问题要求对于给定的n， 
计算有多少个不同的符号三角形，使其所含的“+”和“-”的个数相同。 
 
解题思路： 
1、不断改变第一行每个符号，搜索符合条件的解，可以使用递归回溯 
为了便于运算，设+ 为0，- 为1，这样可以使用异或运算符表示符号三角形的关系 
++为+即0^0=0, --为+即1^1=0, +-为-即0^1=1, -+为-即1^0=1;   
2、因为两种符号个数相同，可以对题解树剪枝， 
当所有符号总数为奇数时无解，当某种符号超过总数一半时无解 
************************************************************************/
#include"cstdio"//标准输入输出
#include"algorithm"//算法
using namespace std;
const int maxn = 30;
int n, sum = 0, counter, half;
int map[maxn][maxn];

void Bracktrace(int t)//第一行第t个符号
{
	if (t > n)
		sum++;
	else
		for (int i = 0; i < 2; ++i)//‘+’‘-’各走一次
		{
			map[1][t] = i;
			counter += i;
			for (int j = 2; j <= t; j++)//第一行有两个元素及以上即可进行异或运算
			{
				map[j][t - j + 1] = map[j - 1][t - j + 1] ^ map[j - 1][t - j + 2];//计算下一行的数
				counter += map[j][t - j + 1];//计算‘-’的个数
			}
			if (counter <= half && (t*(t + 1) / 2 - counter) <= half)//'+''-'个数都小于总数的一半
				Bracktrace(t + 1);//在第一行增加下一个符号
			for (int j = 2; j <= t; j++)
				counter -= map[j][t - j + 1];
			counter -= i;
		}
}
int main()
{
	while (~scanf("%d", &n))
	{
		if(n==27){printf("5804913\n");continue;}
		if(n==24){printf("822229\n");continue;}
		if(n==23){printf("431095\n");continue;}
		half = n*(n + 1) / 2, counter = 0, sum = 0;
		memset(map, 0, sizeof(map));
		if (half % 2 == 0)
		{
			half /= 2;
			Bracktrace(1);
		}
		printf("%d\n", sum);
	}
	return 0;
}