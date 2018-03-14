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


const int N = 1e5 + 5;

vector<int> adj[N];
int dp[N];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) 
	{
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector< pair<int, int> > cit;
	for (int i = 0; i < n; i++) 
	{
		cit.PB(MP(adj[i].size(), i));
	}
	//sort all the cities on neighbor
	sort(cit.begin(), cit.end());
	//DP. You can not create a cycle because next node has to have more neighbor than previous.
	int ans = 1;
	for (PI i : cit) 
	{
		int now = i.second;
		dp[now]=max(dp[now],1);
		for (int it : adj[now]) 
		{
			if (adj[it].size() > adj[now].size()) 
			{
				dp[it] = max(dp[it], dp[now] + 1);
				ans = max(ans, dp[it]);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
