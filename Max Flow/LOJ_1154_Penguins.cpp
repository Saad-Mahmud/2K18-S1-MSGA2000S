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

int N;
double D;
pair<double, double>points[111];
int nn[111],cc[111];
double sq(double x)
{
    return x*x;
}
 
double dis(pair<double, double>A, pair<double, double>B)
{
    return sqrt( sq(A.xx - B.xx) + sq(A.yy - B.yy) );
}

int main()
{
    int t,cas=0;
    isc(t); 
    while(t--)
    {
        scanf("%d %lf", &N, &D);
		int tot=0;
        for(int i=1; i<=N; i++)
		{
			scanf("%lf %lf %d %d", &points[i].xx, &points[i].yy, &nn[i], &cc[i]);
			tot += nn[i];
		}
        vector<int>ans;
        for(int kp=1; kp<=N; kp++)
        {
			init(2*N+1,kp*2-1,2*N+1);
			for(int i=1; i<=N; i++)
			{
				add(2*i-1,2*i,cc[i]);
				add(2*N+1,2*i-1,nn[i]);
			}
			for(int i=1; i<=N; i++)
			{
				for(int j=1; j<=N; j++)
				{
					if(i == j) continue;
	 
					if(dis(points[i], points[j]) <= D)
					{
						add(2*i,2*j-1,1e8);
					}
				}
			}
            int an=dinitz();
            if(an==tot)ans.PB(kp);
        }
        printf("Case %d:", ++cas);
        if(ans.size()==0)printf(" -1\n");
        else
        {
            for(int i=0;i<ans.size();i++)printf(" %d",ans[i]-1);
            puts("");
        }
    }
    return 0;
}
