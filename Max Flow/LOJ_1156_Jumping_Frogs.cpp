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
 
int dinitz() 
{
    int ret = 0;
    int df;
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



int n,d;
pair<char,int>inp[111];

void build(int limit)
{
    init(2*n+1,2*n+2,2*n+2);
    for (int i = 1 ; i <= n ; i++ )
    {
        if(inp[i].xx=='B')add(i*2-1,i*2,2);
        else add(i*2-1,i*2,1);
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=i+1;j<=n;j++)
        {
            if(inp[j].yy-inp[i].yy <= limit )add(i*2,j*2-1,2);
        }
    }
    for (int i = 1 ; i <= n ; i++ )
    {
        if( inp[i].yy <= limit )add(n*2+1,i*2-1,2);
        if( d - inp[i].yy <= limit )add(i*2,n*2+2,2);
    }
}

int main()
{

    int t,cas=0;
    isc(t);
    while(t--)
	{
        scanf("%d %d",&n,&d);
		char str[110];
		for(int i = 1 ; i <= n ; i++ )
		{
			scanf("%s",str);
			sscanf(str,"%c-%d",&inp[i].xx,&inp[i].yy);
		}
		int lo=0,hi=d,k=32;
		while(k--)
		{
			int mid=lo+(hi-lo)/2 ;
			build(mid);
			if(dinitz()>= 2)hi=mid;
			else lo=mid;
		}
		
		for(int i=lo;i<=hi;i++)
		{
			
			build(i);
			if(i==d || dinitz()>= 2)
			{
				printf("Case %d: %d\n",++cas,i);
				break;
			}
		}
    }
    return 0;
}
