#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a,const void *b)
{
	return *(int*)a - *(int*)b;
}
long long townx[100005], towny[100005];
int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0;i<n;i++)
		scanf("%lld %lld", &townx[i], &towny[i]);
	qsort(townx, n, sizeof(townx[0]), cmp);
	qsort(towny, n, sizeof(towny[0]), cmp);

	long long sumx = 0, sumy = 0, sum = 0, midx = 0, midy = 0;  
	long long sum1, sum2, sum3, sum4;

	midx = townx[n / 2 - 1], midy = towny[n / 2 - 1];
	for (int i = 0; i < n; i++)
	{
		sumx += abs(midx - townx[i]);
		sumy += abs(midy - towny[i]);
	}
	sum1 =sumx+ sumy;
	sum = sum1;

	sumy = 0, sumx = 0;
	midx = townx[n / 2], midy = towny[n / 2 - 1];
	for (int i = 0; i < n; i++)
	{
		sumx += abs(midx - townx[i]);
		sumy += abs(midy - towny[i]);
	}
	sum2 = sumx + sumy;
	if (sum2 < sum)sum = sum2;

	sumy = 0, sumx = 0;
	midx = townx[n / 2 - 1], midy = towny[n / 2];
	for (int i = 0; i < n; i++)
	{
		sumx += abs(midx - townx[i]);
		sumy += abs(midy - towny[i]);
	}
	sum3 = sumx + sumy;
	if (sum3 < sum)sum = sum2;

	sumy = 0, sumx = 0;
	midx = townx[n / 2], midy = towny[n / 2];
	for (int i = 0; i < n; i++)
	{
		sumx += abs(midx - townx[i]);
		sumy += abs(midy - towny[i]);
	}
	sum4 = sumx + sumy;
	if (sum4 < sum)sum = sum4;

	printf("%lld\n", sum);
}