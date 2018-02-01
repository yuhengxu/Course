#include<stdio.h>
struct date
{
	int year, month, day;
};
struct person
{
	char name[30], sex;
	struct date birthday;
};
struct person xu = { "Xu yuheng" ,'M',{1996,8,7} };
int main()
{
	static struct person luo = { "louriu",'W',{2222,2,2} };
	static struct person lv = { "lvyonfshuai",'W',{2222,2,22} };
	printf("name             sex     birthday");
	printf( "%-14s%-4c%4d.%2d.%2d.\n",xu.name,xu.sex,xu.birthday.year, xu.birthday.month, xu.birthday.day);
	printf("%-14s%-4c%4d.%2d.%2d.\n", luo.name, luo.sex, luo.birthday.year, luo.birthday.month, luo.birthday.day);
	printf("%-14s%-4c%4d.%2d.%2d.\n", lv.name, lv.sex, lv.birthday.year, lv.birthday.month, lv.birthday.day);
}
