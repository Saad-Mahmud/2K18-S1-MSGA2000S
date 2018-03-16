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

//Havel-Hakimi O(Summation of degrees* log(n)) 
const int mx=1e4+10;
int n, deg[mx];
int sum, left_sum[mx],cnt[mx];
bool valid;

priority_queue<int>pq;

bool solve() 
{
    vector<int>tmp;
    loop(i,1,n)pq.push(deg[i]);
    for(int i=1;i<=n;i++)
    {
		int cur=pq.top();
		pq.pop();
		tmp.clear();
		if(cur<0)return false;
		if(cur==0)continue;
		while(!pq.empty())
		{
			if(!pq.top())return false;
			tmp.PB(pq.top()-1);
			pq.pop();
			cur--;
			if(cur==0)break;
		}
		if(cur)return false;
		for(int i:tmp)pq.push(i);
	}
	return true;
}

int main() 
{
    while (scanf("%d", &n)!=EOF) 
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
        if(sum>((n*(n-1))))valid=false;
        if (valid && solve()) puts("1");
        else puts("0");
    }
    return 0;
}
