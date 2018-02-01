#include<stdio.h>
int main()
{
	int a,b,c,d,t,x,y,z,op; 
	for(;1;)
	{
		scanf("%d %d",&a,&t);
		if(a==0||t==0)
		{
			break;
		}
		if(a!=0&&a<1000||t>9999||a>t)
		{
			printf("Error\n");
			continue;
		}
		else
		{
			op=0; 
			for(;a>999&&a<t&&t<10000;a++)
			{
				if(a%2==0)
					{
			 			x=a%10;
						b=a/10;
						y=b%10;
						c=b/10;
						z=c%10;
						d=c/10;
						if(x!=y&&x!=z&&x!=d&&y!=z&&y!=d&&z!=d)
						{
							printf("%-6d",a);
							op++;
						}	
					}
			}
			printf("\ncounter=%d\n",op);
		}
		
	}	
}
