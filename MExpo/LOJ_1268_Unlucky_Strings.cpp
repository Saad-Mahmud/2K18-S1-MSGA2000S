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

int const MAX = 55;
int n, len;
char str[MAX], ch[MAX];
int nxt[MAX];

struct Matrix {
    int n;
    unsigned mat[MAX][MAX];
    Matrix(int nn) 
    {
        n = nn;
        memset(mat, 0, sizeof(mat));
    }
};

Matrix mul(Matrix a, Matrix b) 
{
    Matrix ans = Matrix(len);
    for(int i = 0; i < len; i ++) 
    {
        for(int j = 0; j < len; j ++) 
        {
            for(int k = 0; k < len; k ++) 
            {
                ans.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return ans;
}

Matrix bigmod(Matrix a, int x) 
{
    Matrix ans = Matrix(len);
    for(int i = 0; i < len; i ++) ans.mat[i][i] = 1;
    while(x) 
    {
        if(x&1) ans = mul(ans, a);
        a = mul(a, a);
        x >>= 1;
    }
    return ans;
}

void failr() 
{
    int i = 0, j = -1;
    nxt[0] = -1;
    while(str[i] != '\0') 
    {
        if(j == -1 || str[i] == str[j]) 
        {
            i++;j++;nxt[i]=j;
        }
        else j = nxt[j];
    }
}

int main() 
{
    int t,cas=0;
    isc(t);
    while(t--) 
    {
        scanf("%d %s %s", &n, ch, str);
        len = strlen(str);
        failr();
        Matrix ans = Matrix(0);
        for(int j = 0; j < (int) strlen(ch); j ++) 
        {
            for(int i = 0; i < len; i ++)
             {
                int pos = i;
                if(str[pos] == ch[j]) 
                {
                    ans.mat[i][pos + 1] ++;
                    continue;
                }
                while(pos && str[pos] != ch[j]) 
                {
                    pos = nxt[pos];
                }
                if(str[pos] == ch[j]) 
                {
                    pos ++;
                }
                ans.mat[i][pos] ++;
            }
        }
        ans = bigmod(ans, n);
        unsigned res = 0;
        for(int i = 0; i < len; i ++) res += ans.mat[0][i];
        printf("Case %d: %u\n",++cas,res);
    }
}
