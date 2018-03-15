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
typedef pair<double,pair<int,int> >PII;

const int maxn = 1009;
const int inf = 0x3f3f3f3f;

int first[maxn],cur[maxn],d[maxn];
bool vis[maxn];
struct edg{int next,to,cap,flow;}e[maxn*5];
struct node{int x,y,val;}a[maxn];
int n,m,s,t,e_sum,ans;
queue<int> q;

//sort on edge weight
bool cmp(const node &x,const node &y){return x.val<y.val;}

void add_edg(int x,int y,int z)
{
    e_sum++;
    e[e_sum].next=first[x];
    first[x]=e_sum;
    e[e_sum].to=y;
    e[e_sum].cap=z;e[e_sum].flow=0;
}
void insert(int x,int y,int z)
{
    add_edg(x,y,z);
    add_edg(y,x,0);
}

bool bfs()
{
    while(!q.empty())q.pop();
    memset(vis,0,sizeof vis);
    q.push(s);vis[s]=1;d[s]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=first[x];i;i=e[i].next)
        {
            int w=e[i].to;
            if(e[i].cap>e[i].flow&&!vis[w])
            {
                q.push(w);vis[w]=1;d[w]=d[x]+1;
                if(w==t) return true;
            }
        }
    }
    return false;
}
int dfs(int x,int mr)
{
    if(x==t||mr==0) return mr;
    int &i=cur[x],tot=0;
    for(;i;i=e[i].next)
    {
        int w=e[i].to;
        if(e[i].cap>e[i].flow&&d[w]==d[x]+1)
        {
            int flow=dfs(w,min(mr,e[i].cap-e[i].flow));
            if(flow)
            {
                tot+=flow;mr-=flow;
                e[i].flow+=flow;
                e[((i-1)^1)+1].flow-=flow;
                if(mr==0) return tot;
            }
        }
    }
    return tot;
}

int dinic()
{
    int res=0;
    while(bfs())
    {
        for(int i=1;i<=n;i++) cur[i]=first[i];
        res+=dfs(s,inf);
    }
    return res;
}

int calc(int x)
{
	//init
    e_sum=0;
    memset(first,0,sizeof first);
    //add edge with smaller weight than current edge
    for(int i=1;i<=x;i++) 
    {
		if(a[x].val>a[i].val)
		{
			insert(a[i].x,a[i].y,1);
			insert(a[i].y,a[i].x,1);
		}
	}
    s=a[x].x;t=a[x].y;
    //return flow
    return dinic();
}
//idea: for each edge: e->(x,y) how many edge with smaller weight than e
//have to be removed to make x->y unreachable 
//Make x src and y des and run maxflow on the graph where each edge has smaller weight than e. 
int main()
{
    isc(n);
    isc(m);
    for(int i=1;i<=m;i++)
    {
		isc(a[i].x);
		isc(a[i].y);
		isc(a[i].val);
	}
    sort(a+1,a+1+m,cmp);
    for(int i=1;i<=m;i++) ans+=calc(i);
    cout<<ans<<endl;
    return 0;
}
