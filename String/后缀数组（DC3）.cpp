/*
复杂度 o(nlogn) 比倍增法快
r数组的有效位为0~n-1，但是需要将r[n]置0，不然会RE;
调用dc3(r, sa, n+1, m);
对于sa[],rank[],height[],额外添加的0作为空串被考虑在内.
sa[1~n](0~n-1) rank[0~n-1](1~n) height[2~n]
r[]和sa[]要开三倍
*/
const int maxn = 1001000;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[maxn], wb[maxn], wv[maxn], wd[maxn];
int c0(int *r, int a, int b)
{
    return r[a]==r[b] && r[a+1]==r[b+1] && r[a+2]==r[b+2];
}
int c12(int k, int *r, int a, int b)
{
    if(k==2) return r[a]<r[b] || (r[a]==r[b]&&c12(1,r,a+1,b+1));
    else return r[a]<r[b] || (r[a]==r[b]&&wv[a+1]<wv[b+1]);
}
void sort(int *r, int *a, int *b, int n, int m)
{
    int i;
    for(i = 0; i < n; i++) wv[i] = r[a[i]];
    for(i = 0; i < m; i++) wd[i] = 0;
    for(i = 0; i < n; i++) wd[wv[i]]++;
    for(i = 1; i < m; i++) wd[i] += wd[i-1];
    for(i = n-1; i >= 0; i--) b[--wd[wv[i]]] = a[i];
}
void dc3(int *r, int *sa, int n, int m)
{
    int i, j, *rn=r+n, *san=sa+n, ta=0, tb=(n+1)/3, tbc=0, p;
    r[n] = r[n+1] = 0;
    for(i = 0; i < n; i++) if(i%3 != 0) wa[tbc++]=i;
    sort(r+2, wa, wb, tbc, m);
    sort(r+1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for(p = 1, rn[F(wb[0])]=0, i=1; i<tbc; i++)
        rn[F(wb[i])] = c0(r, wb[i-1], wb[i])?p-1:p++;
    if(p<tbc) dc3(rn, san, tbc, p);
    else for(i = 0; i < tbc; i++) san[rn[i]]=i;
    for(i = 0; i < tbc; i++) if(san[i] < tb) wb[ta++] = san[i]*3;
    if(n%3==1) wb[ta++] = n-1;
    sort(r, wb, wa, ta, m);
    for(i = 0; i < tbc; i++) wv[wb[i]=G(san[i])] = i;
    for(i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j]%3, r, wa[i], wb[j])?wa[i++]:wb[j++];
    for(; i < ta; p++) sa[p] = wa[i++];
    for(; j < tbc; p++) sa[p] = wb[j++];
}

int rank[maxn], height[maxn];

void getheight(int *r, int *sa, int n)
{
    int i, j, k = 0;
    for(i = 1; i <= n; i++) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i++]] = k)
        for(k?k--:0, j=sa[rank[i]-1]; r[i+k]==r[j+k]; k++);
}

int n, m; //字符串长度，字符范围（要稍大一点）
int r[3*maxn], sa[3*maxn]; //待处理的串,后缀数组
