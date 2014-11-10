#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

//根据题意初始化点儿东西出来
ll dp[20][20][2000];
void init()
{
    memset(dp,0,sizeof(dp));
    for(int j = 1; j <= 18; j++)
        for(int k = 0; k <= 9; k++)
            if((j-1)*k >= 0) dp[1][j][(j-1)*k] += 1;
    for(int i = 2; i <= 18; i++)
        for(int j = 1; j <= 18; j++)
            for(int k = 0; k < 1400; k++)
                for(int l = 0; l <= 9; l++)
                    if(k+(j-i)*l >= 0) dp[i][j][k+(j-i)*l] += dp[i-1][j][k];
}

//获取各个数位
int x[30], len;
void lal(ll c)
{
    if(c==0)
    {
        len = 1;
        x[1] = 0;
        return;
    }
    len = 0;
    while(c > 0)
    {
        x[++len] = c%10;
        c/=10;
    }
}

//从高位到低位推答案
ll getsum(ll c)
{
    lal(c);
    if(len==0) return 0;
    if(len==1&&x[1]==0) return 1;
    ll re = (len==1?0:1);
    for(int i = 1; i < len; i++)
        re += (dp[len-1][i][0]-1);
    int pi;
    for(int j = len; j > 0; j--)
    {
        for(int k = 1; k < x[len]; k++)
            if((len-j)*k >= 0) re += dp[len-1][j][(len-j)*k];
        pi = (len-j)*x[len];
        for(int i = len-1; i > 1; i--)
        {
            for(int k = 0; k < x[i]; k++)
                if(pi+(i-j)*k >= 0) re += dp[i-1][j][pi+(i-j)*k];
            pi += (i-j)*x[i];
        }
        for(int k = 0; k <= x[1]; k++)
            if(pi+(1-j)*k == 0) re++;
    }
    return re;
}

int main()
{
    int t;
    scanf("%d",&t);
    ll a, b;
    init();
    while(t--)
    {
        scanf("%lld %lld",&a,&b);
        a = getsum(a-1);
        b = getsum(b);
        printf("%lld\n",b-a);
    }
    return 0;
}
