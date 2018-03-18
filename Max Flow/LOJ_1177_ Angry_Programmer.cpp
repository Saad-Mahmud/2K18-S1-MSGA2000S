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

const int MAXN=1e5+10;
const int MAXE=2e5+10;
int src, snk, nNode, nEdge;
int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
int flow[MAXE], cap[MAXE], nxt[MAXE], to[MAXE];
 
inline void init(int _src, int _snk, int _n) 
{
    src = _src, snk = _snk, nNode = _n, nEdge = 0;
    memset(fin, -1, sizeof(fin));
}
 
inline void add(int u, int v, int _cap) 
{
    to[nEdge] = v, cap[nEdge] = _cap, flow[nEdge] = 0;
    nxt[nEdge] = fin[u], fin[u] = nEdge++;
    to[nEdge] = u, cap[nEdge] = 0, flow[nEdge] = 0;//cap[nEdge] = 0 for directed graph cap[nEdge] = cap for undirected
    nxt[nEdge] = fin[v], fin[v] = nEdge++;
}
 
bool bfs() 
{
    int st, en, i, u, v;
    memset(dist, -1, sizeof(dist));
    dist[src] = st = en = 0;
    Q[en++] = src;
    while(st < en) 
    {
        u = Q[st++];
        for(i=fin[u]; i>=0; i=nxt[i]) 
        {
            v = to[i];
            if(flow[i] < cap[i] && dist[v]==-1) 
            {
                dist[v] = dist[u]+1;
                Q[en++] = v;
            }
        }
    }
    return dist[snk]!=-1;
}
 
int dfs(int u, int fl) 
{
    if(u==snk) return fl;
    for(int &e=pro[u], v, df; e>=0; e=nxt[e]) 
    {
        v = to[e];
        if(flow[e] < cap[e] && dist[v]==dist[u]+1) 
        {
            df = dfs(v, min(cap[e]-flow[e], fl));
            if(df>0) 
            {
                flow[e] += df;
                flow[e^1] -= df;
                return df;
            }
        }
    }
    return 0;
}
 
ll dinitz() 
{
    ll ret = 0;
    ll df;
    while(bfs()) 
    {
        for(int i=1; i<=nNode; i++)pro[i]=fin[i];
        while(true) 
        {
            df = dfs(src, 1e8);
            if(df) ret +=df;
            else break;
        }
    }
    return ret;
}


int main()
{
	int t,cas=0;
	isc(t); 
	while(t--) 
	{
		int n, m;
		isc(n);isc(m);
		init(1,n*2,n*2);
		int c,u,v;
		for (int i = 2; i<=n-1; ++i) 
		{
			isc(c);
			add(i*2-1,i*2,c);
		}
		add(1,2,1e8);
		add(n*2-1,n*2,1e8);
		for (int i = 0; i < m; ++i) 
		{
			isc(u);isc(v);isc(c);
			add(u*2,v*2-1, c);
			add(v*2,u*2-1, c);
		}
		long long flow = dinitz();
		printf("Case %d: %lld\n",++cas,flow);
	}
  return 0;
}
