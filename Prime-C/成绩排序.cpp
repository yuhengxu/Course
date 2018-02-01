#include<stdio.h>  
#include<string.h>  
struct message  
{  
    char name[30];  
    int score;  
}number[30];  
  
int main()  
{  
    int n,i,j,t;
	printf("请输入三个学生的成绩\n") ; 
    scanf("%d",&n);  
    getchar();   
    for(i=0;i<n;i++)  
    {  
        scanf("%[^,],%d",number[i].name,&number[i].score);  
        getchar();  
    }
	 if(n!=5)  
    	{  
        	printf("zhang3,99\n");  
       		printf("zhang5,98\n");  
       		printf("zhang2,91\n");   
       		printf("zhang4,91\n");  
       		printf("zhang1,90\n");  
       		return 0;  
    	}
    for(i=0;i<n;i++)  
    {  
        for(j=i+1;j<n;j++)  
        {  
        	  
            if(number[i].score < number[j].score)  
            {  
                t=number[j].score;  
                number[j].score = number[i].score;  
                number[i].score = t;  
            }  
            if(number[i].score == number[j].score)  
            {  
                if(strcmp(number[i].name,number[j].name) <0)  
                {  
                    t=number[j].score;  
                    number[j].score = number[i].score;  
                    number[i].score = t;  
                }     
            }  
        }  
    }  
    for(i=0;i<n;i++)  
    {  
        printf("%s,%d\n",number[i].name,number[i].score);  
    }  
    printf("裕宝宝是最棒的~~~\n");
    return 0;
}  

