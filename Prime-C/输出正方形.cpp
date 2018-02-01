#include <stdio.h>
int main()
{
	 int n,i,j,t;
	 char m;
	 scanf("%d %c",&n,&m);
	 for(i=0;i<n;i++)
	 {
		 if(i==0)
		 {
			 for(j=0;j<n;j++)
			 {
				 t=m+j;
				if((m<=90&&t>90)||(m>96&&t>122))
					t=t-26;
		        if(j==n-1)
			        printf("%c\n",t);
		        else
		 	         printf("%c ",t);
			 }
		 }
		 else if(i==n-1)
			  {
		          for(j=0;j<n;j++)
			     {
					t=m+3*n-3-j;
				   if((m<=90&&t>90)||(m>96&&t>122))
					   t=t-26;
		            if(j==n-1)
			            printf("%c\n",t);
		            else
		 	            printf("%c ",t);
			     }
		     }
		 else
		 {
			 for(j=0;j<2*n-1;j++)
			 {
				 
				 if(j==0)
				 {
                    t=m+4*n-4-i;
				    if((m<=90&&t>90)||(m>96&&t>122))
					    t=t-26;  
					 printf("%c",t);
				 }
				 else if(j==2*n-2)
				 {
					 t=m+n-1+i;
					 if((m<=90&&t>90)||(m>96&&t>122))
					    t=t-26;  
					 printf("%c\n",t);
				 }
				 else
					 printf(" ");
			 }
		 }
	 }

	return 0;
 }

