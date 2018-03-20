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

const int MOD = 10;
int n;
 
struct matrix {
    vector<vector<int> > mt;
 
    matrix() {
        mt.assign(n, vector<int>(n, 0));
    }
 
    matrix operator+(const matrix &ob) {
        matrix sum;
 
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                sum.mt[i][j] = (mt[i][j] + ob.mt[i][j]) % MOD;
 
        return sum;
    }
 
    matrix operator*(const matrix &ob) {
        matrix prod;
 
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                for(int k = 0; k < n; ++k) {
                    prod.mt[i][j] += mt[i][k] * ob.mt[k][j];
                }
 
                prod.mt[i][j] %= MOD;
            }
        }
 
        return prod;
    }
};
 
struct mat {
    matrix mm[2][2];
 
    mat operator+(const mat &ob) {
        mat sum;
 
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j)
                sum.mm[i][j] = mm[i][j] + ob.mm[i][j];
 
        return sum;
    }
 
    mat operator*(const mat &ob) {
        mat prod;
 
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j)
                for(int k = 0; k < 2; ++k)
                    prod.mm[i][j] = prod.mm[i][j] + (mm[i][k] * ob.mm[k][j]);
 
        return prod;
    }
 
    mat expo(int pw) {
        if(pw == 1) return *this;
 
        mat res = expo(pw >> 1);
        res = res * res;
 
        if(pw & 1) res = (*this) * res;
 
        return res;
    }
};
 
int main()
{
    int t,cas=0;
    isc(t);
 
    while(t--)
    {
        int k;
        scanf("%d %d", &n, &k);
        matrix a;
        rept(i,0,n)rept(j,0,n)isc(a.mt[i][j]);
        mat b;
        b.mm[0][0] = b.mm[0][1] = a;           
        b.mm[1][0] = b.mm[1][1] = matrix();     
        rept(i,0,n)b.mm[1][1].mt[i][i] = 1;
        vector<vector<int> >ans=(b.expo(k).mm[0][1]).mt;
        printf("Case %d:\n",++cas);
        rept(i,0,n) 
        {
            rept(j,0,n)printf("%d", ans[i][j]);
            putchar('\n');
        }
    }
    return 0;
}
