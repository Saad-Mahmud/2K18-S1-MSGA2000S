//https://www.codechef.com/problems/COUNTARI
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
	double nn = res.size();
	for(int i = 0; i<nn; i++) 
	{
		res[i] /= nn;
	}
	reverse(res.begin() + 1, res.end());
	return res;
}
vcd p1(65536),p2(65536),ans(65536);
void multiply() 
{
	int len=65536;
	p1 = fft(p1);
	p2 = fft(p2);
	for(int i = 0; i < len; ++i)ans[i]=p1[i]*p2[i];
	ans=inv_fft(ans);
}

#define N2 65536
#define M 30000
#define BLOCK_SIZE 25

int in[120000];
int bef[M], aft[M], inside[M];
int main()
{
	int n,k;
	int st,ed,per;
	ll res=0;
	scanf("%d",&n);
	rept(i,0,n)
	{
		isc(in[i]);
		in[i]--;
	}
	memset(bef,0,sizeof bef);
	memset(aft,0,sizeof aft);
	rept(i,0,n)aft[in[i]]++;
	per=(n+BLOCK_SIZE-1)/BLOCK_SIZE;

	rept(block,0,BLOCK_SIZE)
	{
		st = block * per;
		ed = (block+1) * per;
		if(ed > n) ed = n;
		
		rept(i,st,ed) aft[in[i]]--;
		rept(i,0,M)inside[i]=0;

		rept(i,st,ed)
		{
			rept(j,i+1,ed) 
			{
				if(in[i] != in[j])
				{
					k = in[i] - (in[j] - in[i]);
					if(0<=k && k<M) res += bef[k] + inside[k];//three in block and two in block and one in before
					k = in[j] + (in[j] - in[i]);
					if(0<=k && k<M) res += aft[k];//two in block and one in after
				}
			}
			inside[in[i]]++;
		}

		rept(i,0,M)
		{
		  res += (ll)inside[i] * (inside[i]-1) / 2 * (bef[i] + aft[i]);//two in block with same value
		  res += (ll)inside[i] * (inside[i]-1) * (inside[i]-2) / 6;//three in block with same value
		}
		//j is in the block i is in before and k is in after
		if(block && block+1 < BLOCK_SIZE)
		{
			rept(i,0,p1.size())p1[i]=p2[i]=ans[i]=0;
			rept(i,0,M)p1[i]= bef[i], p2[i]= aft[i];
			multiply();
			rept(i,0,M) res += inside[i] * (ll)( ans[2*i].real() + 0.5);
		}
		rept(i,st,ed) bef[in[i]]++;
	}
	printf("%lld\n",res);
	return 0;
}
