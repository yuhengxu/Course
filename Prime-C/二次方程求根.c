#include<stdio.h>
#include<math.h>
int main()
{
	void root(double a, double b, double c);
	double a, b, c;
	scanf_s("%lf %lf %lf", &a, &b, &c);
	root(a, b, c);

	return 0;
}

void root(double a, double b, double c)
{
	if (b*b - 4 * a*c == 0)
	{
		printf("%lf\n", -b / (2 * a));
	}
	else if (b*b - 4 * a*c > 0)
	{
		printf("%lf %lf", (-b + sqrt(b*b - 4 * a*c) )/ (2 * a), (-b - sqrt(b*b - 4 * a*c)) / (2 * a));
	}
	else
	{
		printf("No real root!\n");
	}
}