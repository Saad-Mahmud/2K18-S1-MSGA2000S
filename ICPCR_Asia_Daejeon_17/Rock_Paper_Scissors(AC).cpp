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

//iterative fft
typedef complex<double> cd;
typedef vector< cd > vcd;
const long double PI = acos(-1);

vcd fft(const vcd &as) 
{
	int n = (int)as.size();
	int k = 0;
	while((1<<k) < n) k++;
	vector< int > r(n);
	r[0] = 0;
	int h = -1;
	for(int i = 1; i<n; i++) 
	{
		if((i & (i-1)) == 0)
		h++;
		r[i] = r[i ^ (1 << h)];
		r[i] |= (1<<(k-h-1));
	}
	vcd root(n);
	for(int i = 0; i<n; i++) 
	{
		double ang = 2.0*PI*i/n;
		root[i] = cd(cos(ang), sin(ang));
	}

	vcd cur(n);
	for(int i = 0; i<n; i++)
		cur[i] = as[r[i]];

	for(int len = 1; len < n; len <<= 1 ) 
	{
		vcd ncur(n);
		int step = n/(len << 1);
		for(int pdest = 0; pdest <n;) 
		{
			for(int i = 0; i<len; i++) 
			{
				cd val = root[i*step]*cur[pdest + len];
				ncur[pdest] = cur[pdest] + val;
				ncur[pdest + len] = cur[pdest] - val;
				pdest++;
			}
			pdest += len;
		}
		cur.swap(ncur);
	}
	return cur;
}

vcd inv_fft(const vcd& fa) 
{
	vcd res = fft(fa);
	int nn = res.size();
	for(int i = 0; i<nn; i++) 
	{
		res[i] /= nn;
	}
	reverse(res.begin() + 1, res.end());
	return res;
}

vcd multiply(vcd& a, vcd & b) 
{
	int len = a.size() + b.size();
	while (len & (len-1)) ++len;
	a.resize(len);
	b.resize(len);
	a = fft(a);
	b = fft(b);
	for (int i = 0; i < len; ++i)
		a[i] *= b[i];
	a = inv_fft(a);
	return a;
}

string rps = "RPSRPS";
const int N = 3e5 + 5;

int cnt[N];
char s[N], p[N];
//Calculate win for R,S,P separately using FFT
int main() 
{
	int n, m;
	scanf("%d %d %s %s", &n, &m, s, p);
	for (int c = 0; c < 3; ++c) 
	{
		vcd a(n), b(m);
		for (int i = 0; i < n; ++i)a[i] = (s[i] == rps[c]);
		for (int i = 0; i < m; ++i)b[m-1-i] = (p[i] == rps[c+1]);
		vcd res = multiply(a, b);
		//x^(i)*x^(m-1-i)=x^m-1
		//m-1 has the answer for index 0
		for (int i = m-1; i < n+m; ++i) 
		{
		  cnt[i] += (int)((double)res[i].real()+0.5);
		}
	}
	int ans = 0;
	for (int i = 0; i < n+m; ++i)ans = max(ans, cnt[i]);
	printf("%d\n", ans);
	return 0;
}
