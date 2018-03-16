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


double arr[11][3];
double tmm[11];
int main() 
{
    int n,t;
    cin>>n>>t;
    double ans=0;
    loop(i,1,n)cin>>arr[i][0]>>arr[i][1]>>arr[i][2];
    loop(i,1,n)ans+=arr[i][2];
    double td=0.01;
    t*=100;
    loop(i,1,t)
    {
		double ma=0;
		int mi=0;
		loop(i,1,n)
		{
			double cur=arr[i][0]*(tmm[i]+td)*(tmm[i]+td)+arr[i][1]*(tmm[i]+td);
			double prv=arr[i][0]*(tmm[i])*(tmm[i])+arr[i][1]*(tmm[i]);
			cur-=prv;
			if(cur>=ma)
			{
				ma=cur;
				mi=i;
			}
		}
		ans+=ma;
		tmm[mi]+=td;
	}
	printf("%0.6lf\n",(ans/n));
  return 0;
}
