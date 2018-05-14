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
typedef double ld;
typedef long long ll;
typedef pair<int,int>PI;
typedef pair<int,pair<int,int> >PII;

char adj[1026][1026];
ll tot=0;
int p1[514],p2[514],n,k;
int skip1[1026],skip2[1026];
int d1[514],d2[514];
int ga[514],av[514],bv[514];

void cald()
{
	memset(d1,0,sizeof d1);
	memset(d2,0,sizeof d2);
	loop(i,1,n/2)
	{
		loop(j,1,n/2)
		{		
			d1[i]-=adj[p1[i]][p1[j]];
			d2[i]-=adj[p2[i]][p2[j]];
			d1[i]+=adj[p1[i]][p2[j]];
			d2[i]+=adj[p2[i]][p1[j]];
		}
	}
}

void add(int ind)
{
	ga[ind]=-6e8;
	loop(i,1,n/2)
	{
		if(skip1[p1[i]])continue;
		loop(j,1,n/2)
		{
			if(skip2[p2[j]])continue;
			int kp=d1[i]+d2[j]-2*adj[p1[i]][p2[j]];
			if(ga[ind]<kp)
			{
				ga[ind]=kp;
				av[ind]=i;
				bv[ind]=j;
			}
		}
	}
	skip1[p1[av[ind]]]=1;
	skip2[p2[bv[ind]]]=1;
}

void updateDfor(int ind)
{
	loop(i,1,n/2)
	{
		d1[i]+=adj[p1[i]][p1[av[ind]]]*2;
		d1[i]-=adj[p1[i]][p2[bv[ind]]]*2;
		d2[i]+=adj[p2[i]][p2[bv[ind]]]*2;
		d2[i]-=adj[p2[i]][p1[av[ind]]]*2;
	}
}
int getGM()
{
	int gmx=-6e8;
	int cur=0;
	loop(i,1,n/2)
	{
		cur+=ga[i];
		if(cur>gmx)
		{
			gmx=cur;
			k=i;
		}
	}
	return gmx;
}
void s_wap()
{
	loop(i,1,k)
	{
		swap(p1[av[i]],p2[bv[i]]);
	}
}
void printans()
{
	sort(p1+1,p1+1+n/2);
	sort(p2+1,p2+1+n/2);
	printf("Partition 1:\n");
	loop(i,1,n/2)printf("%d\n",p1[i]);
	printf("Partition 2:\n");
	loop(i,1,n/2)printf("%d\n",p2[i]);
}
int main()
{
	int t;
	isc(n);
	loop(i,1,n)
	{
		loop(j,1,n)
		{
			isc(t);
			adj[i][j]=t;
		}
	}
	loop(i,1,n/2)
	{
		p1[i]=i;
		p2[i]=n/2+i;
	}
	int itr=20;
	while(itr--)
	{
		cald();			
		memset(skip1,0,sizeof skip1);
		memset(skip2,0,sizeof skip2);
		loop(i,1,n/2)
		{
			add(i);
			updateDfor(i);
		}
		int g_max=getGM();
		if(g_max>0)s_wap();
		else break;
	}
	printans();
	return 0;
}
