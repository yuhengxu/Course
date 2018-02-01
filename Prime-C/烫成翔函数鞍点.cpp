#include <stdio.h>    
int main ( )  
{  
    int num[10][10] = {0};  
    int max;  
    int min;  
    int i, j, l, k, counter = 0;  
    int n;  
    int m;  
      
    scanf ("%d%d", &n, &m);  
    for (i = 0; i < n; i ++)  
    {  
        for (j = 0; j < m; j ++)  
        {  
            scanf ("%d", &num[i][j]);  
        }  
    }  
      
    for (i = 0; i < n; i ++)  
    {  
        max = 0;  
        for (j = 0; j < m; j ++)  
        {  
            if (num[i][j] > max)  
            {  
                max = num[i][j];  
                k = j;  
            }  
        }  
        min = num[i][k];  
        for (l = 0; l < n; l ++)  
        {  
            if (num[l][k] < min)  
            {  
                 break;  
            }  
        }  
        if (l == n)  
        {  
            printf ("Point:a[%d][%d]==%d\n", i, k, num[i][k]);  
            counter ++;  
        }  
    }  
    if (counter == 0)  
    {  
        printf ("No Point\n");  
    }  
}  
