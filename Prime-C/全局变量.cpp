#include<stdio.h>
int main()
{   void  increment(void);
     increment(  );
     increment(  );
     increment(  );
    return 0;
}
void  increment(void)
{   int x=0;
     x++;
     printf("%3d" ,x);
}
