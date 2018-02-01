#include<stdio.h>
int main()
{
	float N, H, h, R, r,d,w,s;
	int i, j, k;
	int volume, surface, density;
	scanf_s("%f", &N);
	int number[20][5] = { 0 };
	for (i = 0; i < N; i++)
	{
		scanf_s("%f%f%f%f%f",&R, &r, &d, &w, &s);
		H = R + (R*R - r*r + d*d) / (2 * d);
		h = r + d - (R*R - r*r + d*d) / (2 * d);
		volume = (3.1415 / 3)*(3 * R - H)*H*H + (3.1415 / 3)*(3 * r - h)*h*h;
		surface = 2 * 3.1415*R*H + 2 * 3.1415*r*h;
		density = w / volume;
		printf("%.4f %.4f\n", volume, surface);
			if (density <= s)
			{
				printf("The Paired-Sphere Floats.\n");
			}
			else
			{
				printf("The Paired-Sphere Sinks.\n");
			}
	}

	return 0;
}
