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


vector<int> mask, unmask;
int st;
int a, b, pos, bpos;
int dx[] = {0, 1, 1, 1}, dy[] = {1, 1, 0, -1};

int check(int black, int white) 
{
	//unwanted game state
	for (int x : unmask) 
	{
		if ((black&x)==x || (white&x)==x)return 0;
	}
	//wanted game state
	for (int x : mask) 
	{
		if ((white & x) == x)return 1;
	}  
	return 0;
}

int cnt[5];
set<pair<int, int> > ans;
void solve(int black, int white, int cur) 
{
	//basecase
	if ((black | white) & bpos) 
	{
		//if ok add to answer
		if (check(black, white))ans.insert(make_pair(black, white));
	}
	else 
	{
		//try to add stone on each col 
		for (int i = 0; i < 4; ++i) 
		{
			if (cnt[i] >= 4) continue;
			int now = cnt[i] * 4 + i;
			cnt[i]++;
			if (cur)solve(black | (1 << now), white, 0);
			else solve(black, white | (1 << now), 1);
			cnt[i]--;
		}
	}
}
//gen all end states
void gen(int a,int b)
{
	pair<int, int> now = {a, b};
	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; ++j)  
		{
			//for each cell
			for (int d = 0; d < 4; ++d) 
			{
				//for each direction
				int cur = 0;
				bool last = 0;
				for (int k = 0; k < 3; ++k) 
				{
					//3 stone
					int x = i + dx[d] * k;
					int y = j + k * dy[d];
					if (x < 0 || x >= 4 || y < 0 || y>= 4) break;
					if (make_pair(x, y) == now) last = 1;
					int val = x * 4 + y;
					cur |= 1 << val;
				}
				if(__builtin_popcount(cur) == 3) 
				{
					//if has end pos put it in mask else unmask
					if(last) mask.push_back(cur);
					else unmask.push_back(cur);
				}
			}
		}
	}
}
int main() 
{
  scanf("%d %d %d", &st, &a, &b);
  a--; 
  b--; 
  st--;
  pos=a*4+b;//end pos
  gen(a,b);//gen all end game states
  bpos = 1 << pos;
  cnt[st] = 1;//add to st col
  solve(1 << st, 0, 0);//backtrack
  printf("%d\n", ans.size());
  return 0;
}
