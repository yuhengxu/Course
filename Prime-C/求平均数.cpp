#include<stdio.h>
int main()
{
	int num,count,total,n;
	count=1;
	total=0;
	do
	{
		printf("请输入参加考试人数%d_\b",n);
		scanf("%d",&n);
		printf("请输入第%d个同学的成绩_\b",count);
		scanf("%d",&num);
		if(num>100||num<=0)
		{
			printf("你是狗咩，哪有负分"); 
		}
		else
		{
	 	count++;
		total+=num;
		}
	}
	while(count<n);
	printf("这10位同学的平均成绩是%d\n",total/10);
	return 0;
}
