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

//Solution: Use KMP to find smallest repeating substring.
//since we can exclude a prefix the main problem is to Use KMP to find smallest repeating substring in a suffix.
//the trick is to reverse the string and then check it for each prefix.
//since we dont have to complete the cycle no need to check the mod=0
int nxt[1000005];
int b[1000005];
int n, m;
int main()
{
    scanf("%d", &n);

    for(int i = 1; i <= n; i ++) scanf("%d", &b[n-i+1]);//reverse
    //LPS
    nxt[1] = 0;
    for(int i = 1; i < n; i ++)
    {
        int j = nxt[i];
        while(j && b[j + 1] != b[i + 1]) j = nxt[j];
        nxt[i + 1] = (b[j + 1] == b[i + 1]) ? j + 1 : 0;
    }
    //cycle
    int ans = 0x3f3f3f3f, p = 0, k = 0;
    for(int i = 1; i <= n; i ++)
    {
        //excluding first i char
        int np = (n - i + 1 - nxt[n - i + 1]);
        if(i + np < ans || (i + np == ans && np < p))
        {
            ans = i + np;
            k = i - 1; p = np;
        }
    }
    printf("%d %d\n", k, p);
    return 0;
}
close
