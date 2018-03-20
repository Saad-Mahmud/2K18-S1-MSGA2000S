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

const int mx = 2e3+10 ;
const int INF = 1 << 29 ;
vector <int> adj[mx],rev[mx],can[mx];
int n,scc,m ;
int Color[mx],vis[mx];
stack <int>stk ;
const int NIL = 0;
vector<int> adjList[mx];
int pairU[mx], pairV[mx], dist[mx];
 
bool bfs()
{
    queue<int> q;
 
    for(int u = 1; u <= scc; ++u) 
    {
        if(pairU[u] == NIL) 
        {
            dist[u] = 0;
            q.push(u);
        }
        else dist[u] = INF;
    }
    dist[NIL] = INF;
 
    while(!q.empty()) 
    {
        int u = q.front(); q.pop();
 
        if(dist[u] < dist[NIL]) 
        {
            int v, sz = adjList[u].size();
 
            for(int i = 0; i < sz; ++i) 
            {
                v = adjList[u][i];
                if(dist[pairV[v]] == INF) 
                {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
 
    return (dist[NIL] != INF);
}
 
bool dfs(int u)
{
    if(u == NIL) return true;
    int v, sz = adjList[u].size();
    for(int i = 0; i < sz; ++i) 
    {
        v = adjList[u][i];
        if(dist[pairV[v]] == dist[u]+1 && dfs(pairV[v])) 
        {
            pairV[v] = u;
            pairU[u] = v;
            return true;
        }
    }
    dist[u] = INF;
    return false;
}
 
int hopcroft_karp()
{
    fill(pairU+1, pairU+n+1, NIL);
    fill(pairV+1, pairV+n+1, NIL);
    int matching = 0;
    while(bfs()) 
    {
        for(int u = 1; u <= scc; ++u)
        {
			if(pairU[u] == NIL && dfs(u))++matching;
		}
    }
    return matching;
}


void dfs1(int x)
{
    vis[x] = 1 ;
    int sz = adj[x].size();
    rept(i,0,sz)
    {
        int u = adj[x][i];
        if( vis[u] == 0 ) dfs1( u );
    }
    stk.push(x);
}
void Kosaraju( int x , int c)
{
    vis[x] = 0 ;
    Color[x] = c ;
    int sz = rev[x].size();
    rept(i,0,sz)
    {
        int u = rev[x][i];
        if( vis[u] )Kosaraju( u , c );
    }
}


void src( int x )
{
    vis[x] = 1 ;
    int sz = can[x].size();
    rept(i,0,sz)
    {
        int u = can[x][i];
        if( vis[u] == 0 )src(u);
    }
}

void constractGraph()
{
    loop(i,1,scc)
    {
        loop(j,1,scc) vis[j] = 0 ;
        src(i);
        loop(j,1,scc)
        {
            if(i!=j&&vis[j])adjList[i].PB(j);
        }
    }
}


void ini()
{
    rept(i,0,mx)
    {
        adj[i].clear();
        rev[i].clear();
        adjList[i].clear();
        vis[i] = 0 ;
    }
    while( !stk.empty()) stk.pop();
}

int main()
{
	int t,cas=0;
	isc(t);
	while(t--)
    {  
		int u,v;
		isc(n);isc(m);
		ini();
		rept(i,0,m)
		{
			isc(u);isc(v);
			adj[u].PB(v);
			rev[v].PB(u);
		}
		loop(i,1,n)if(vis[i]==0) dfs1(i);
		scc = 0 ;
		while(!stk.empty())
		{
			int u = stk.top();
			stk.pop();
			if( vis[u] == 0 ) continue ;
			Kosaraju( u , ++scc );
			can[scc].clear();
		}
		
		loop(i,1,n)
		{
			int sz = adj[i].size();
			rept(j,0,sz)
			{
				if(Color[i]!=Color[adj[i][j]])
				{
					can[Color[i]].PB(Color[adj[i][j]]);
				}
			}
		}
		constractGraph();
		int mn = hopcroft_karp();
		printf("Case %d: %d\n",++cas,scc-mn);
    }
    return 0;
}
