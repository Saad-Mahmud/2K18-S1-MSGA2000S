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
typedef unsigned long long ll;
typedef pair<int,int>PI;
typedef pair<int,pair<int,int>>PII;

const int mx=1e5+10;
int n,m,q;
map<int,int>mp1,mp2;
int revmp1[mx],revmp2[mx];
struct
{
    int x,y,k,id;
} qs[mx];
int ans[mx];
vector<PII>edge;
vector<int>tocheck[mx];
int lo[mx],hi[mx];
int parent[mx],szunion[mx];
set<int>all[mx];

int findset(int x)
{
    return x == parent[x] ? x : findset(parent[x]);
}
void wunion(int a,int b)
{
    int root_A = findset(a);
    int root_B = findset(b);
    //cout<<a<<" "<<root_A<<" "<<b<<" "<<root_B<<endl;
    if(root_A==root_B)
        return;
    if(szunion[root_A] < szunion[root_B ])
    {
        parent[ root_A ] = parent[root_B];
        szunion[root_B] += szunion[root_A];
        if(all[root_A].size()>all[root_B].size())swap(all[root_A],all[root_B]);
        while(all[root_A].size())
        {
            all[root_B].insert(*all[root_A].begin());
            all[root_A].erase(all[root_A].begin());
        }
    }
    else
    {
        parent[root_B]=parent[root_A];
        szunion[root_A]+=szunion[root_B];
        if(all[root_A].size()<all[root_B].size())swap(all[root_A],all[root_B]);
        while(all[root_B].size())
        {
            all[root_A].insert(*all[root_B].begin());
            all[root_B].erase(all[root_B].begin());
        }
    }

  //  cout<<a<<" "<<parent[root_A]<<" "<<b<<" "<<parent[root_B]<<endl;
}
int ind,cntb,cnte;
void apply(int k)
{
   // cout<<"Apply "<<k<<" ind "<<ind<<endl;
    while(ind<edge.size())
    {
        if(edge[ind].xx>k)
            break;
        else
        {
            wunion(edge[ind].yy.xx,edge[ind].yy.yy);
            ind++;
        }
    }
   // cout<<"Applied "<<k<<" ind "<<ind<<endl;
}
int main()
{
    int t,u,v,w;
    isc(n);
    isc(m);
    isc(q);
    cntb=0;
    loop(i,1,n)
    {
        isc(t);
        if(!mp1[t])
            mp1[t]=(++cntb);
        revmp1[i]=mp1[t];
    }
    rept(i,0,m)
    {
        isc(u);
        isc(v);
        isc(w);
        edge.PB(MP(w,MP(u,v)));
    }
    sort(edge.begin(),edge.end());
    for(int k=0; k<edge.size(); k++)
    {
        PII i=edge[k];
        if(!mp2[i.xx])
        {
            mp2[i.xx]=(++cnte);
            revmp2[cnte]=i.xx;
        }
        edge[k].xx=mp2[i.xx];

    }
    int tot=0;
    rept(i,0,q)
    {
        isc(u);
        isc(v);
        isc(w);
        if(w>cntb)
        {
            ans[i]=-1;
        }
        else
        {
            tot++;
            qs[tot].x=u;
            qs[tot].y=v;
            qs[tot].k=w;
            qs[tot].id=i;
        }
    }
    for(int i=1; i<=tot; i++)
    {
        lo[i]=1;
        hi[i]=cnte+1;
    }
    bool changed = true;
    while(changed)
    {
        changed = false;

        // clean up mess.
        for(int a = 0; a <= n; a++)
        {
            all[a].clear();
            all[a].insert(revmp1[a]);
            parent[a] = a ;
            szunion[a] = 1;
        }
        int upto=0;
        for(int i = 1; i <= tot; i++)
        {
            if(lo[i] != hi[i])
            {
                tocheck[ (lo[i] + hi[i]) >> 1 ].PB(i);
                upto=max(upto,(lo[i] + hi[i]) >> 1);
            }
        }
        // end of cleaning up
        ind=0;
        //cout<<upto<<endl;
        for(int q = 1; q <=upto ; q++)
        {
            apply(q);

            while(tocheck[q].size())
            {
                changed = true;
                int id = tocheck[q].back();
                tocheck[q].pop_back();
                int rootx=findset(qs[id].x);
                int rooty=findset(qs[id].y);
                if(rootx!=rooty)
                    lo[id] = q + 1;
                else
                {
                    //cout<<all[rootx].size()<<" "<<q<<endl;
                    if(all[rootx].size()>=qs[id].k)
                        hi[id]=q;
                    else
                        lo[id] = q + 1;
                }
            }
        }
    }

    for(int i = 1; i <= tot; i++)
    {
        assert(lo[i] == hi[i]);
        if(lo[i]<=cnte)
            ans[qs[i].id]=revmp2[lo[i]];
        else
            ans[qs[i].id]=-1;
    }
    rept(i,0,q)printf("%d\n",ans[i]);
    return 0;
}
