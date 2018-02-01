#include<stdio.h>
int main()
{
	int  yuer[] = { 1,2,3,4 };
	int  *name[4] = { &yuer[1],&yuer[2],&yuer[3],&yuer[0] }; 
	int i,**p;
	p = name;
	for (i = 0; i < 4; i++)
	{
		printf("%d\n", **p);
		p++;
	}

	return 0;
}