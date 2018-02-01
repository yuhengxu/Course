#include<stdio.h>
int main()
{
	int a,b,c,t;
	scanf("%d %d %d",&a,&b,&c);
	if(a<b)
	{t=a;a=b;b=t;
		if(b<c)
		{t=b;b=c;c=t;
			if(a<b)
			{t=a;a=b;b=t;
			}
		}	
	}
	else if(b<c)
	{t=b;b=c;c=t;
		if(a<b)
		{t=a;a=b;b=t;
		}
	}
	printf("这三个数由大到小的顺序是%d>%d>%d",a,b,c);
}
