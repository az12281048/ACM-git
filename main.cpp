#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 501000;

struct acAutomata
{
    int ch[maxn][2];
    int val[maxn];
    int cnt[maxn];
    int f[maxn];
    int last[maxn];
    int sz;

    void init()
    {
        sz = 1;
        memset(ch,0,sizeof(ch));
    }
    int idx(char c)
    {
        return c-'0';
    }
    void insert(const char *s, int v)
    {
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++)
        {
            int c = idx(s[i]);
            if(!ch[u][c])
            {
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }
    void getfail()
    {
        queue<int> q;
        f[0] = 0;
        for(int c = 0; c < 2; c++)
        {
            int u = ch[0][c];
            if(u)
            {
                f[u] = 0;
                q.push(u);
                last[u] = 0;
            }
        }
        while(!q.empty())
        {
            int r = q.front();
            q.pop();
            for(int c = 0; c < 2; c++)
            {
                int u = ch[r][c];
                if(u)
                {
                    q.push(u);
                    int v = f[r];
                    while(v && !ch[v][c]) v = f[v];
                    f[u] = ch[v][c];
                    last[u] = val[f[u]]?f[u]:last[f[u]];
                }
            }
        }
    }
    void print(int j)
    {
        if(j)
        {
            cnt[val[j]]++;
            print(last[j]);
        }
    }
    void find(const char *s)
    {
        memset(cnt,0,sizeof(cnt));
        int n = strlen(s);
        int j = 0;
        for(int i = 0; i < n; i++)
        {
            int c = idx(s[i]);
            while(j && !ch[j][c])
            {
                j = f[j];
            }
            j = ch[j][c];
            if(val[j])
            {
                print(j);
            }
            else if(last[j])
            {
                print(last[j]);
            }
        }
    }
};
char str1[5001000], str2[5001000];
acAutomata all, tp;
vector<string> sta;
map<string,int> mp;

int main()
{
    //freopen("in.txt","r",stdin);
    int t, n, cn_all, cn_tp;
    ll pre;
    scanf("%d",&t);
    for(int ca = 1; ca <= t; ca++)
    {
        all.init();
        tp.init();
        mp.clear();
        sta.clear();
        cn_all = cn_tp = 1;
        pre = 0;
        printf("Case #%d:\n",ca);
        scanf("%d",&n);
        while(n--)
        {
            scanf("%s",str1);
            if(str1[0] == '+')
            {
                if(mp.find(string(&str1[1])) == mp.end())
                {
                    tp.insert(&str1[1], cn_tp++);
                    sta.push_back(string(&str1[1]));
                    if(tp.sz > 1000)
                    {
                        for(int i = 0; i < sta.size(); i++)
                            all.insert(sta[i].c_str(),cn_all++);
                        sta.clear();
                        cn_tp = 1;
                        tp.init();
                        all.getfail();
                    }
                }
            }
            else
            {
                int len = strlen(&str1[1]), tmp;
                pre%=len;
                for(int i = 0; i < len; i++)
                    str2[i] = str1[1+(i+pre)%len];
                str2[len] = '\0';
                long long ans = 0;
                if(tp.sz > 1)
                {
                    tp.getfail();
                    tp.find(str2);
                    for(int i = 1; i < cn_tp; i++)
                        ans += tp.cnt[i];
                }
                if(all.sz > 1)
                {
                    all.find(str2);
                    for(int i = 1; i < cn_all; i++)
                        ans += all.cnt[i];
                }
                printf("%I64d\n",ans);
                pre = ans;
            }
        }
    }
    return 0;
}
