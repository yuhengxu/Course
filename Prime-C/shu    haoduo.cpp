#include<stdio.h>
#include<math.h>
int main()
{
	int n,x,a,b,c,d,e,f,t,u,v,w,y,z;
	scanf("%d",&n);
	if(n>=3&&n<=6)
	{
		for(x=pow(10,n-1);x<(pow(10,n)-1);)
		{
		loop:x++;
		a=x%10;
		t=x/10;
		b=t%10;
		u=t/10;
		c=u%10;
		v=u/10;
		d=v%10;
		w=v/10;
		e=w%10;
		y=w/10;
		f=y%10;
		z=y/10;
		while (x==pow(a,n)+pow(b,n)+pow(c,n)+pow(d,n)+pow(e,n)+pow(f,n))
		printf("%d",x);
		goto loop;
	    }
	}
	else
	{
		printf("No output.");
	}
}
		
