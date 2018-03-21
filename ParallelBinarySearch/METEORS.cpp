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


const int maxn = 300005;
vector<int> owner[maxn];
ll reqd[maxn];
int ql[maxn],qr[maxn];
ll qa[maxn];
int lo[maxn], hi[maxn];
vector<int> tocheck[maxn];
ll tree[maxn];
int n,m;
int k;
long long maxi=0;
void update(int x, long long val)
{
	while(x<=m){tree[x]+=val;x+=(x&-x);}
}
long long query(int x)
{
	ll s=0;
	while(x>0){s+=tree[x];x-=(x&-x);}
	return s;
}
 
void apply(int x)
{
	if(ql[x]<=qr[x])update(ql[x],qa[x]),update(qr[x]+1,-qa[x]);
	else
	{
		update(1,qa[x]);
		update(qr[x]+1,-qa[x]);
		update(ql[x],qa[x]);
	}
}
 
int main()
{
	isc(n);
	isc(m);
	int x;
	for(int i = 1; i <= m; i++)
	{
		isc(x);
		owner[x].PB(i);
	}
	for(int i = 1; i <= n; i++)llsc(reqd[i]);
	isc(k);
	for(int i = 1; i <= k; i++)
	{
		isc(ql[i]);
		isc(qr[i]);
		llsc(qa[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		lo[i] = 1;
		hi[i] = k + 1;
	}
	bool changed = true;
	
	while(changed)
	{
		changed = false;
		memset(tree,0,sizeof tree);
		for(int i = 1; i <= n; i++)if(lo[i] != hi[i])tocheck[ (lo[i] + hi[i]) >> 1 ].PB(i);
		 
		for(int q = 1; q <= k; q++)
		{
			apply(q);
			while(tocheck[q].size())
			{
				changed = true;
				int id = tocheck[q].back();
				tocheck[q].pop_back();
 
				ll sum = 0;
				for(auto sectors: owner[id])
				{
					sum += query(sectors);
					if(sum >= reqd[id]) break;
				}
				if(sum >= reqd[id])
					hi[id] = q;
				else
					lo[id] = q + 1;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		assert(lo[i] == hi[i]);		
		if(lo[i] <= k)printf("%d\n",lo[i]);
		else printf("NIE\n");
	}
	return 0;
}
