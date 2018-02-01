    #include<stdio.h>  
    int main()  
    {  
      int a,d,c,i,j,n;  
      scanf("%d",&n);  
      for(a=d=n,i=1;i<=n;i++)  
      {  
        for(j=1;j<a;j++)  
        printf("  ");  
       for(j=a;j<=d;j++)  
        {  
         printf("%d",n);  
         if(n<10)  
         printf(" ");  
         n--;   
        }  
        n++;  
        for(j=n;j<d;j++)  
        {  
         n++;  
         printf("%d",n);  
         if(n<10)  
         printf(" ");  
        }     
        printf("\n");  
        a=n-i;  
      }  
      for(c=d=n,a=1,i=1;i<n;i++)  
      {  
        for(j=c;j<=n;j++)  
        printf("  ");  
        for(j=a;j<d;j++)  
        {  
         printf("%d",n);  
         if(n<10)  
         printf(" ");  
         n--;   
        }  
        n++;  
        for(j=a;j<d-1;j++)  
        {  
         n++;  
         printf("%d",n);  
         if(n<10)  
         printf(" ");  
        }     
        printf("\n");  
        a++;  
        c--;  
      }  
      return 0;  
    }  
