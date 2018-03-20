//https://toph.co/p/counting-triplets
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
//typedef pair<ll,ll>PI;
typedef pair<ll,pair<int,int> >PII;

const int mx = 1e3;
const int NIL = 0;
const int INF = INT_MAX;
 
int n,a[mx],b[mx],c[mx],d[mx],startTime[mx],finishTime[mx];
vector<int> adjList[mx];
int pairU[mx], pairV[mx], dist[mx];
 
bool bfs()
{
    queue<int> q;
 
    for(int u = 1; u <= n; ++u) 
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
        for(int u = 1; u <= n; ++u)
        {
			if(pairU[u] == NIL && dfs(u))++matching;
		}
    }
    return matching;
}

bool check(int i,int j)
{
	if(i==j)return false;
	if(finishTime[i]+abs(c[i]-a[j])+abs(d[i]-b[j]) < startTime[j])return true;
	return false;
}
int main()
{
    int t,cas=0;
    isc(t);
    while(t--) 
    {
        isc(n);
        int hh, mm;
        loop(i,1,n) 
        {
			adjList[i].clear();
            scanf("%d:%d",&hh,&mm);
            isc(a[i]);isc(b[i]);isc(c[i]);isc(d[i]);
            startTime[i]=hh*60+mm;
            finishTime[i]=startTime[i]+abs(a[i]-c[i])+abs(b[i]-d[i]);
        }
        loop(i,1,n)loop(j,1,n)if(check(i,j))adjList[i].push_back(j);
        printf("Case %d: %d\n",++cas,n-hopcroft_karp());
    }
    return 0;
}
