#include<stdio.h> 
  char    fun ( char  *c )
{ if ( *c<='Z'&&*c>='A')
	{
		*c-='A'-'a';
 	} 
     return  *c;  
 }
int  main( )
   {  char  s[81]  ,   *p=s;
    gets(s);
    while(*p)
{  *p=fun(p); putchar(*p);   p++; }
    9  
    return 0;
 }
