#include<stdio.h>
int main()
{
	int foot,head,chicken,rabbit;
	scanf("%d %d",&foot,&head);
	if(foot>head*4||head/2>foot)
	{
		printf("error\n"); 
	}
	for(rabbit=0;rabbit<=foot/4;rabbit++)
		for(chicken=head-rabbit;chicken>=0;chicken--)
		{
			if(rabbit+chicken==head&&4*rabbit+2*chicken==foot)
			printf("º¶”–%d,Õ√”–%d\n",chicken,rabbit);
		}

		
}
