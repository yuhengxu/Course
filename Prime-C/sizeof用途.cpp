#include<stdio.h>
int main()
{
	char str[20];
	struct date
	{
		int year, mounth, day;
	}today;
	struct address
	{
		char name[30], street[40], city[20], state[2]
			;
		unsigned long int zip;
	}wang;
	printf("char: %d\t", sizeof(char));
	printf("int: %d\t", sizeof(int));
	printf("long: %d\t", sizeof(long));
	printf("double: %d\t", sizeof(double));
	printf("str: %d\t", sizeof(str));
	printf("date: %d\t", sizeof(date));
	printf("today: %d\t", sizeof(today));
	printf("wang: %d\t", sizeof(wang));
}
