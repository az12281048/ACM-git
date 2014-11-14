//hdu4787  根号n的优化，用两个acAutomata。总复杂度为 n*sqrt(n)
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

const int MAXNODE = 100100;
const int CHARSET = 2;

struct TrieNode
{
    int ch[CHARSET];
    int cnt;
};

struct acAutomata
{
    TrieNode trie[MAXNODE];
    int sz, fail[MAXNODE];

    void init()
    {
        memset(fail,0,sizeof(fail));
        sz = 0;
        memset(trie[0].ch, -1, sizeof(trie[0].ch));
        trie[0].cnt = 0;
    }

    int idx(char c)
    {
        return c-'0';
    }

    void insert(const char *s, int L)//L表示插入的串已被左移L位
    {
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++)
        {
            int v = idx(s[(i+L)%n]);
            if(trie[u].ch[v] == -1)
            {
                sz++;
                trie[u].ch[v] = sz;
                memset(trie[sz].ch, -1, sizeof(trie[sz].ch));
                trie[sz].cnt = 0;
            }
            u = trie[u].ch[v];
        }
        trie[u].cnt = 1;
    }

    void getFail()
    {
        queue<int> q;
        q.push(0);
        fail[0] = -1;
        while(!q.empty())
        {
            int r = q.front();
            q.pop();
            for(int i = 0; i < CHARSET; i++)
            {
                int v = trie[r].ch[i];
                if(v == -1) continue;
                int f = fail[r];
                while(f != -1 && trie[f].ch[i] == -1)
                    f = fail[f];
                if(f == -1) fail[v] = 0;
                else fail[v] = trie[f].ch[i];
                q.push(v);
            }
        }
    }

    int query(const char *s, int L)//L表示插入的串已被左移L位
    {
        int re = 0, u = 0, n = strlen(s);
        for(int i = 0; i < n; i++)
        {
            int v = idx(s[(i+L)%n]);
            while(u && trie[u].ch[v]==-1) u = fail[u];
            u = trie[u].ch[v];
            if(u==-1)
            {
                u = 0;
                continue;
            }
            int cur = u;
            while(cur != -1)
            {
                re += trie[cur].cnt;
                cur = fail[cur];
            }
        }
        return re;
    }
};

acAutomata ac, tp;
vector<string> tr;
vector<int> tn;
char str[6000000];

int main()
{
    //freopen("in.txt","r",stdin);
    int t, n, pre;
    scanf("%d",&t);
    for(int ca = 1; ca <= t; ca++)
    {
        printf("Case #%d:\n",ca);
        ac.init();
        tp.init();
        tr.clear();
        tn.clear();
        pre = 0;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%s",str);
            if(str[0] == '+')
            {
                if(tp.sz > 2000)
                {
                    for(int i = 0; i < tr.size(); i++)
                        ac.insert(tr[i].c_str(),tn[i]);
                    tp.init();
                    tr.clear();
                    tn.clear();
                    ac.getFail();
                }
                tp.insert(str+1, pre);
                tr.push_back(string(str+1));
                tn.push_back(pre);
            }
            else
            {
                tp.getFail();
                pre = ac.query(str+1,pre)+tp.query(str+1,pre);
                printf("%d\n",pre);
            }
        }
    }
    return 0;
}
