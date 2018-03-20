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

const int MN  = 40;
typedef unsigned int uint;
 
struct matrix 
{
	int r, c;
	uint m[MN][MN]; 
	matrix() {}
	matrix (int _r, int _c) 
	{
		r=_r;
		c=_c;
		memset(m, 0, sizeof m);
	}
 
	void print() 
	{
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)cout<<m[i][j]<< " ";
			enl;
		}
	}
 
	uint x[MN][MN];
	matrix & operator *= (const matrix &o) 
	{
		memset(x, 0, sizeof x);
		for (int i = 0; i < r; ++i)
			for (int k = 0; k < c; ++k)
				if (m[i][k] != 0)
					for (int j = 0; j < c; ++j)
					{
						x[i][j] = x[i][j] +  m[i][k] * o.m[k][j];
					}
		memcpy(m, x, sizeof(m));
		return *this;
  }
};
 
void matrix_pow(matrix b, long long e, matrix &res)
{
	memset(res.m, 0, sizeof res.m);
	for (int i = 0; i < b.r; ++i)
		res.m[i][i] = 1;
 
	if (e == 0) return;
	while (true) 
	{
		if (e & 1) res *= b;
		if ((e >>= 1) == 0) break;
		b *= b;
	}
}
 
matrix a, b;
vector<pair<int, int> > s;
vector<vector<uint> > t;
void pre() 
{
	s.push_back(make_pair(-10, -12));
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 2; j < 10; ++j)
		{
			s.push_back(make_pair(i, j));
		}
	}
	t.resize(s.size(), vector<uint> (s.size()));
	for (int i = 0; i < s.size(); ++i)
	{
		for (int j = 0; j < s.size(); ++j)
		{
			if (abs(s[i].first - s[j].first) > 1 &&
			abs(s[i].first - s[j].second) > 1 &&
			abs(s[i].second - s[j].first) > 1 &&
			abs(s[i].second - s[j].second) > 1)
			{
				t[i][j] = 1;
			}
		}
		t[i][0] = 0;
	}
}
 
int main() 
{
	pre();
	int T,cas=0; 
	isc(T);
	while(T--) 
	{
		int n;
		scanf("%d", &n);
		a.r = a.c = t.size();
		b.r = b.c = t.size();
		for (int i = 0; i < t.size(); ++i)
		{
			for (int j = 0; j < t.size(); ++j)a.m[i][j] = t[i][j];
		} 
		matrix_pow(a, n, b);
		uint ans = 0;
		for (int i = 1; i < t.size(); ++i) 
		{
			ans += b.m[0][i];
		}
		printf("Case %d: %u\n",++cas,ans);
	}
	return 0;
}
