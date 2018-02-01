#include<stdio.h>
int main()
{
	int fruit[10005] = { 0 }, a[10005] = { 0 };
	int sum = 0, type, temp;
	scanf_s("%d", &type);//输入果子的种类数 
	for (int i = 0; i < type; i++)
	{
		scanf_s("%d", &fruit[i]);
	} //每种果子的数量

	int i, j;
	for (j = type - 1; j>0; j--)
	{
		for (i = 1; i<j; i++)
		{
			if (fruit[0]>fruit[i])//如果第i项比第一项小，就交换两项的位置，及搜索所有的数最小的放在第一项 
			{
				temp = fruit[0];
				fruit[0] = fruit[i];
				fruit[i] = temp;
			}
		}
		for (i = 1; i<j; i++)//如果第i+1项比第二项小，就交换两项的位置，及搜索所有的数第二小的放在第二项 
		{
			if (fruit[1]>fruit[i + 1])
			{
				temp = fruit[1];
				fruit[1] = fruit[i + 1];
				fruit[i + 1] = temp;
			}
		}
		fruit[0] = fruit[0] + fruit[1];//最小两项合并 
		fruit[1] = fruit[j];//把最后一项的值给第一项；
		sum = sum + fruit[0];
	}
	printf("%d", sum);
}
