#include<stdio.h>
struct date
	{
		int year,month,day;
	};
	struct date today;
	
	int main()
{
	
	struct date today ;
	printf("Enter today date");
	scanf("%d%d%d",&today.year,&today.month,&today.day);
	printf("%d.%d.%d",today.year,today.month,today.day);
} 
