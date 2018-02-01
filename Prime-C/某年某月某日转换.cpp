#include<stdio.h>
int a(int day_tab,int year,int mouth,int day)
    int *day_tab;
	int year,mouth,day;
{
	int i,j;
	i=(year%4==0&&year%100!=0)||year%400==0;
	for(j=1;j<mouth;j++)
	{
		day+=*(day_tab+i+13+j);
	}
	return day;
}  
int main()
{
	static int day_tab[][13]={ 
	                  {0,31,28,31,30,31,30,31,31,30,31,30,31},
	                  {0,31,28,31,30,31,30,31,31,30,31,30,31} } ;
	int y,m,d,b;
	scanf("%d %d %d",&y,&m,&d);
	b=a(day_tab,y,m,d);
	printf("%d\n",b);													                                   
}

