//状压DP   BFS  图的大小和状态的乘积刚好为复杂度
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
typedef pair<int,int> PII;

struct node{
    int x,y,step,key;
};

int n,m,p;
int door[51][51][51][51], key[51][51], dp[51][51][2100];
int tr[4][2] = {0,1,0,-1,1,0,-1,0};
queue<node> que;

int bfs()
{
    while(!que.empty()) que.pop();
    memset(dp,0,sizeof(dp));
    node cur, nxt;
    cur.x = 1;
    cur.y = 1;
    cur.step = 0;
    cur.key = key[1][1];
    que.push(cur);
    while(!que.empty())
    {
        cur = que.front();
        que.pop();
        for(int i = 0; i < 4; i++)
        {
            nxt.x = cur.x+tr[i][0];
            nxt.y = cur.y+tr[i][1];
            if(nxt.x<1 || nxt.x>n || nxt.y<1 || nxt.y>m) continue;
            int dr = door[cur.x][cur.y][nxt.x][nxt.y];
            if(dr&1 == 1) continue;
            if(dr>0 && (dr&cur.key) != dr) continue;
            if(nxt.x==n && nxt.y==m) return cur.step+1;
            nxt.key = (cur.key|key[nxt.x][nxt.y]);
            if(dp[nxt.x][nxt.y][nxt.key]) continue;
            dp[nxt.x][nxt.y][nxt.key] = 1;
            nxt.step = cur.step+1;
            que.push(nxt);
        }
    }
    return -1;
}

int main()
{
    //freopen("in.txt","r",stdin);
    int k, s;
    while(~scanf("%d%d%d",&n,&m,&p))
    {
        memset(door,0,sizeof(door));
        memset(key,0,sizeof(key));
        scanf("%d",&k);
        int x1, y1, x2, y2, g;
        while(k--)
        {
            scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&g);
            door[x1][y1][x2][y2] |= (1<<g);
            door[x2][y2][x1][y1] |= (1<<g);
        }
        scanf("%d",&s);
        while(s--)
        {
            scanf("%d%d%d",&x1,&y1,&g);
            key[x1][y1] |= (1<<g);
        }
        if(n==1 && m==1) printf("0\n");
        else printf("%d\n",bfs());
    }
    return 0;
}
