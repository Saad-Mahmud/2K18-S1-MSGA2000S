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

#define maxN 100111
#define mod 1000000007
 
const int size = 35;
struct Matrix {
    int a[size][size];
    Matrix() 
    {
        rept(i,0,size) 
        {
			rept(j,0,size)a[i][j] = 0;
		}
    }
    Matrix multi(Matrix mat) 
    {
        Matrix res;
        rept(i,0,size)
        {
			rept(j,0,size)
			{
				 rept(k,0,size) 
				 {
					res.a[i][j] += (a[i][k] * (ll)mat.a[k][j]) % mod;
					res.a[i][j] %= mod;
				}
			}
        }
        return res;
    }
} base;
 
Matrix power(Matrix mat, int k) 
{
    if (k == 1) return mat;
    Matrix res = power(mat, k / 2);
    res = res.multi(res);
    if (k % 2) return res.multi(mat);
    return res;
}
 
int isOk(vector<int> a,vector<int> b) 
{
    do {
			int ok = 1;
			rept(i,0,4) 
			{
				if (abs(a[i] - b[i]) != 1)
				{
					ok = 0;
					break;
				}
			}
			if(ok)return 1;
			
		}while(next_permutation(b.begin(),b.end()));
		return 0;
}
 
vector< vector<int> > stat;
 
void init() 
{
	loop(i,0,6)
    {
		loop(j,i+1,6)
		{
			loop(u,j+1,6)
			{ 
				loop(v,u+1,6) 
				{
					vector<int> tmp;
					tmp.PB(i); tmp.PB(j); tmp.PB(u); tmp.PB(v);
					stat.PB(tmp);
				}
			}
		}
    }
    
    base = Matrix();
    rept(i,0,stat.size())
    {
		rept(j,0,stat.size())
        {
			base.a[i][j] = isOk(stat[i], stat[j]);
		}
	}
}
 
int main()
{
    
    init();
    int t,cas=0;
    isc(t);
    while(t--) 
    {
		int val, res, pos, n;
        isc(n);
        vector<int> st;
        rept(i,0,7) 
        {
            isc(val);
            if(val)st.PB(i);
        }
        if (n == 1) res = 1;
        else 
        {
            rept(i,0,stat.size())
            {
				if(st == stat[i]) 
				{
					pos = i;
					break;
				}
			}
            Matrix mat = power(base, n - 1);
            res = 0;
            rept(i,0,size) 
            {
                res += mat.a[pos][i];
                res %= mod;
            }
        }
        printf("Case %d: %d\n",++cas,res);
    }
    return 0;
}


 
