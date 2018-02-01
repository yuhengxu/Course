#include<stdio.h>
#include<math.h>
int main()
{
	float a,b;
	char op;
	scanf("%f %f %c",&a,&b,&op);
	switch(op)
	{
		case'+':
		printf("%.2f+%.2f=%.2f\n",a,b,a+b);break;
		case'-':
		printf("%.2f-%.2f=%.2f\n",a,b,a-b);break;
		case'*':
		printf("%.2f*%.2f=%.2f\n",a,b,a*b);break;
		case'/':
			if(b==0)
			printf("你是狗咩，这都算错\n");
			else
			printf("%.2f/%.2f=%.2f\n",a,b,a/b);break;
		default:
			printf("比比啥，再逼逼削你\n");break;
	}
 } 
