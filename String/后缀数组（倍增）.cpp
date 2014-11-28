/*
���Ӷ� o(nlogn)
r�������ЧλΪ0~n-1��������Ҫ��r[n]��0����Ȼ��RE;
����getsa(r, n+1, m);
����sa[],rank[],height[],������ӵ�0��Ϊ�մ�����������.
*/
const int maxn = 1010;
int sa[maxn], rank[maxn], height[maxn];
//��i����sa[i]����׺i����Ϊrank[i],height[i]Ϊsa[i]��sa[i-1]�������ǰ׺
// sa[1~n](0~n-1) rank[0~n-1](1~n) height[2~n]

int wa[maxn], wb[maxn], wv[maxn], wd[maxn];

int cmp(int *r, int a, int b, int l)
{
    return r[a]==r[b] && r[a+l]==r[b+l];
}

void getsa(int *r, int n, int m)
{
    int i, j, k, p, *x = wa, *y = wb, *t;
    for(i = 0; i < m; i++) wd[i] = 0;
    for(i = 0; i < n; i++) wd[x[i]=r[i]]++;
    for(i = 1; i < m; i++) wd[i] += wd[i-1];
    for(i = n-1; i >= 0; i--) sa[--wd[x[i]]] = i;
    for(j = 1, p = 1; p < n; j<<=1, m = p)
    {
        for(p = 0, i = n-j; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i]-j;
        for(i = 0; i < n; i++) wv[i] = x[y[i]];
        for(i = 0; i < m; i++) wd[i] = 0;
        for(i = 0; i < n; i++) wd[wv[i]]++;
        for(i = 1; i < m; i++) wd[i] += wd[i-1];
        for(i = n-1; i >= 0; i--) sa[--wd[wv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
    }

    for(i = 0, k = 0; i < n; i++) rank[sa[i]] = i;
    for(i = 0; i < n-1; height[rank[i++]] = k)
        for(k?k--:0, j = sa[rank[i]-1]; r[i+k]==r[j+k]; k++);
}

int n, m; //�ַ������ȣ��ַ���Χ��Ҫ�Դ�һ�㣩
int r[maxn]; //������Ĵ�
