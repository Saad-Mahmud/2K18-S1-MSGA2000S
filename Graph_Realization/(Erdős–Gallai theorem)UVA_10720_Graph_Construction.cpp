#include<bits/stdc++.h>
using namespace std;
#define loop(i,L,R) for(int i=(L);i<=(R);i++)
#define rept(i,L,R) for(int i=(L);i<(R);i++)
#define isc(n) scanf("%d",&n)
#define llsc(n) scanf("%lld",&n)
#define dsc(n) scanf("%lf",&n)
#define enl cout<<endl
#define PB(x) push_back(x)
#define MP(x,y) make_pair(x,y)
#define xx first
#define yy second
typedef long long ll;
typedef pair<ll,ll>PI;
typedef pair<ll,pair<int,int> >PII;

//Erdős–Gallai theorem O(n) implimentation 
const int mx=1e4+10;
int n, deg[mx];
int sum, left_sum[mx],cnt[mx];
bool valid;

bool solve() 
{
    memset(cnt,0,sizeof cnt);
    loop(i,1,n)cnt[deg[i]]++;
    int cur=1;
    for(int i=10000;i>=0;i--)while(cnt[i]--)deg[cur++]=i;
    memset(left_sum,0,sizeof left_sum);
    for (int i = n; i >= 1; i--)left_sum[i]=left_sum[i + 1] + deg[i];
    int left=0,right;
    int p=n;
    loop(k, 1, n) 
    {
        while(p>k && deg[p]<k)p--;
        p=max(p,k);
        left += deg[k];
        right = k*(k-1)+k*(p-k) + left_sum[p + 1];
        if (left > right) return false;
    }
    return true;
}

int main() 
{
    while (scanf("%d", &n) && n) 
    {
        valid = true;
        sum = 0;
        loop(i, 1, n) 
        {
            scanf("%d", &deg[i]);
            if (!valid) continue;
            if (deg[i] >= n || deg[i] < 0) valid = false;
            sum += deg[i];
        }
        if(sum&1)valid=false;
        if (valid && solve()) puts("Possible");
        else puts("Not possible");
    }
    return 0;
}
