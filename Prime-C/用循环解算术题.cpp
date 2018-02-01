#include<stdio.h>
int main()
{
	int min=9,max=0;
	int op;

	for(;1;)
	{
		char c;
		scanf("%c",&c);
		if(c>='0'&&c<='9')
		{
			if(c-'0'>max)
			{
				max=c-'0';
			}
			if(c-'0'<min)
			{
				min=c-'0';
			}
		}
		else if(c=='+')
		{
			op=2;
		}
		else if(c=='-')
		{
			op=3;
		}
		else if(c=='*')
		{
			op=4;
		}
		else if(c=='/')
		{
			op=5;
		}
		else if(c=='%')
		{
			op=6;
		}
		else if(c=='=')
		{
			break;
		}
		else if(c==',')
		{
			continue;
		}
	}

	switch(op)
	{
		case 2:
		{
			printf("%d+%d=%d\n",max,min,max+min);break;
		}
		case 3:
		{
			printf("%d-%d=%d\n",max,min,max-min);break;
		}
		case 4:
		{
			printf("%d*%d=%d\n",max,min,max*min);break;
		}
		case 5:
		{
			if(min==0)
			{
			printf("Error!\n");break;
			}
			else
			{
			printf("%d/%d=%d\n",max,min,max/min);break;
			}
		}
			case 6:
		{
			if(min==0)
			{
			printf("Error!\n");break;
			}
			else
			{
			printf("%d%%%d=%d\n",max,min,max%min);break;
			}
		}
		
	}
}
