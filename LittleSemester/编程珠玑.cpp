#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 10005;
typedef struct
{
    int a,b,c;
}Node;
Node node[maxn];
 int T,n;

 double ans(double  x)
 {
     double  Max = node[0].a*x*x + node[0].b*x +node[0].c;
     for(int i = 1; i < n; i++)
     {
         Max = max(Max, node[i].a*x*x + node[i].b*x +node[i].c);
     }

     return Max;
 }
int main()
{

   #ifdef xxz
   freopen("in","r",stdin);
    #endif // xxz
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 0; i <n; i++)
        {
            scanf("%d%d%d",&node[i].a,&node[i].b,&node[i].c);
        }
            double left = 0, right = 1000;
            for(int j= 0; j <= 100; j ++)//精度把握不好的用for循环
            {
                  double mid = (left +right)/2;
                  double midmid =(right+ mid)/2;
                  if(ans(mid) < ans(midmid) )  right = midmid;
                  else  left = mid;
            }
            printf("%.4lf\n",ans(left));
    }
    return 0;
}