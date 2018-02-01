 #include<stdio.h>
int main()
{ 
	float a,b,c;
	scanf("%f %f",&a,&b);
	if ((b/5-a)>0) 
	{
		c=(b/5-a)*30-b/2;
		printf("At %d:%02d the angle is %.1f degrees.\n",(int)a,(int)b,c);
	}
	else if((b/5-a)<0)
	{
		c=-(b/5-a)*30-b/2;
		if (c==360) {
		printf("At %d:%02d the angle is 0.0 degrees.\n",(int)a,(int)b);
		}
		else {
   			c=(b/5-a)*30-b/2 ;
			printf("At %d:%02d the angle is %.1f degrees.\n",(int)a,(int)b,c);
		}
	}
	else if((b/5-a)==0)
	{
		c=b/2;
		printf("At %d:%02d the angle is %.1f degrees.\n",(int)a,(int)b,c);
	} 
}
 
