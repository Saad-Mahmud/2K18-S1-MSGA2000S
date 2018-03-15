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


struct node {
 int x,y;
};
node t;
node solve(int n,int m)
{
	//base case
    if(n==2)
    {
        if(m==0)
        {
            t.x = 1;t.y = 1;
            return t;
        }
        if(m==1)
        {
            t.x = 1;t.y = 2;
            return t;
        }
        if(m==2)
        {
            t.x = 2;t.y = 2;
            return t;
        }
        else
        {
            t.x = 2;t.y = 1;
            return t;
        }
    }
    
    int k = n/2;
    int x = m/(k*k);//quadrent
    if(x == 0)
    {
	   //bottom left = rotation but no offset
       t=solve(k,k*k -1- m%(k*k));//k*k -1- m%(k*k) rotation less position
       swap(t.x,t.y);
       t.y=k-t.y+1;//rotate row becomes col and col becomes row from oposite side
       return t;
    }
    else if(x == 1)
    {
		//top left = no rotation and y offset
        t = solve(k,m%(k*k));
        t.y += k;
        return t;
    }
    else if(x == 2)
    {
		//top right = no rotation and x,y offset
        t = solve(k,m%(k*k));
        t.x += k;t.y += k;
        return t;
    }
    else
    {
		//bottom right = rotation and x offset
        t=solve(k,k*k -1- m%(k*k));//k*k -1- m%(k*k) rotation less position
        swap(t.x,t.y);
        t.x=k-t.x+1;//rotation
        t.x+=k;//offset
        return t;
    }
}

int main()
{
    int n,m;
    cin>>n>>m;
    m--;
    node p = solve(n,m);
    cout<<p.x<<" "<<p.y<<endl;
}
