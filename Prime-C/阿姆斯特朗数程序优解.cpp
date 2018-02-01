#include<stdio.h>
#include<math.h>
int main()
{
	int n,s,temp,num;
	scanf("%d",&n);
	for(num=pow(10,n-1);num<pow(10,n);num++)
	{
		for(temp=num,s=0;;)
		{
			s=s+pow(temp%10,n);
			temp=temp/10;
			if(temp==0)
			break;
		}
		if(s==num)
		{
			printf("%d\n",s);
		}
	}
}
