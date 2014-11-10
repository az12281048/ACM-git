//概率期望典型
//期望等于子期望的加权和，权为子期望对应事件发生的概率
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

int n,m,k;
double p1,p2,p3,p4;
double p21,p31,p41;
double dp[2010][2010], po[2010];

int main()
{
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        scanf("%lf%lf%lf%lf",&p1,&p2,&p3,&p4);
        if(p4 < 1e-5)
        {
            printf("0.00000\n");
            continue;
        }
        p21 = p2/(1-p1);
        p31 = p3/(1-p1);
        p41 = p4/(1-p1);
        po[0] = 1;
        for(int i = 1; i <= n; i++) po[i] = po[i-1]*p21;
        memset(dp,0,sizeof(dp));
        dp[1][1] = p41/(1-p21);
        for(int i = 2; i <= n; i++)
        {
            //迭代解方程，解出dp[i][i]
            double sum = p41*po[i-1];
            for(int j = 2; j <= k && j <= i; j++) sum += po[i-j]*(p31*dp[i-1][j-1]+p41);
            for(int j = k+1; j <= i; j++) sum += po[i-j]*(p31*dp[i-1][j-1]);
            dp[i][i] = sum/(1-po[i]);
            dp[i][1] = p21*dp[i][i]+p41;
            for(int j = 2; j <= k; j++) dp[i][j] = p21*dp[i][j-1]+p31*dp[i-1][j-1]+p41;
            for(int j = k+1; j < i; j++) dp[i][j] = p21*dp[i][j-1]+p31*dp[i-1][j-1];
        }
        printf("%.5lf\n",dp[n][m]);
    }
    return 0;
}
