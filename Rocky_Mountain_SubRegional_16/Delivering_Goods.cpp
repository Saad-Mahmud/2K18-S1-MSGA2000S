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

struct edge 
{
    int u, v;
    ll w;
    edge (int uu = 0, int vv = 0, ll ww = 0) : u(uu), v(vv), w(ww) {}
    bool operator<(const edge& rhs) const 
    {
        return w > rhs.w;
    }
};
vector<edge> adj[1001];
int n, m, c;
ll d[302][1001];
void dijkstra(int s, int i) 
{
    priority_queue<edge> pq;
    pq.push(edge(-1, s, 0));
    while (!pq.empty()) 
    {
        edge curr = pq.top();
        pq.pop();
        if (d[i][curr.v] != -1) continue;
        d[i][curr.v] = curr.w;
        for (auto nxt : adj[curr.v])
        {
            nxt.w += curr.w;
            pq.push(nxt);
        }
    }
}


class KuhnImplementation
{
public:
    int n, k;
    vector < vector<int> > g;
    vector<int> pairs_of_right, pairs_of_left;
    vector<bool> used;
    bool kuhn (int v)
    {
        if (used[v])  return false;
        used[v] = true;
        for (int i = 0; i < g[v].size(); ++i)
        {
            int to = g[v][i];
            if (pairs_of_right[to] == -1 || kuhn (pairs_of_right[to]))
            {
                pairs_of_right[to] = v;
                pairs_of_left[v] = to;
                return true;
            }
        }
        return false;
    }
 
    int find_max_matching(vector<vector<int> > &_g, int _n, int _k)
    {
        g = _g;
        n = _n;
        k = _k;
        pairs_of_right = vector<int> (k, -1);
        pairs_of_left = vector<int> (n, -1);
        used = vector<bool> (n, false);
        bool path_found;
        do
        {
            fill(used.begin(), used.end(), false);
            path_found = false;
            for (int i = 0; i < n; ++i)
                if (pairs_of_left[i] < 0 && !used[i])
                    path_found |= kuhn (i);
        }
        while (path_found);
        int res = 0 ;
        for(int i = 0; i < k; i++)if(pairs_of_right[i] != -1)res++ ;
        return res;
    }
};
 
vector< vector<int> > graph;
KuhnImplementation kuhn;
int cl[301];

int main() 
{
    isc(n);isc(m);isc(c);
    rept(i,0,c)isc(cl[i]);
    memset(d,-1,sizeof d);
    edge e;
    loop(i,1,m) 
    {
        isc(e.u);isc(e.v);llsc(e.w);
        adj[e.u].push_back(e);
    }
	graph.resize(n);
    dijkstra(0,301);
    for (int i = 0; i < c; ++i) 
    {
        dijkstra(cl[i],i);
        for (int j = 0; j < c; ++j)
        {    
			if (i != j && d[i][cl[j]] != -1 && d[301][cl[i]] + d[i][cl[j]] == d[301][cl[j]])
			{
				graph[i].push_back(j);
			}
	   }
    }
    int ans=c-kuhn.find_max_matching(graph,c,c);
	printf("%d\n",ans);
    return 0;
}
