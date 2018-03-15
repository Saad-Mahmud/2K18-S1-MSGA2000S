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

int a[100005], d[100005];
int n;
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d%d", &a[i], &d[i]);
    }
    int di = 0;
    int minx = 0, maxx = 0, miny = 0, maxy = 0;
    int px = 0, py = 0;
    for(int i = 1; i <= n; i ++)
    {
        //always try to go to rightmost leftmost upmost downmost so far plus one
        //this way it create a outgoing spiral pattern
        //while keeping the value less than or equal to n

        //right
        if(di == 0)
        {
            a[i] = maxx + 1 - px;
            px += a[i];
            maxx = max(maxx, px);
        }
        //up
        if(di == 1)
        {
            a[i] = maxy + 1 - py;
            py += a[i];
            maxy = max(maxy, py);
        }
        //left
        if(di == 2)
        {
            a[i] = px - minx + 1;
            px -= a[i];
            minx = min(minx, px);
        }
        //down
        if(di == 3)
        {
            a[i] = py - miny + 1;
            py -= a[i];
            miny = min(miny, py);
        }
        di=(di+d[i]+4)%4;
    }

    for(int i = 1; i <= n; i ++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}
close
