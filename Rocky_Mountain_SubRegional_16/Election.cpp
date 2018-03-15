#include<bits/stdc++.h>
using namespace std;

const int p=50;
unsigned long long ncr[p+1][p+1];
void pre()
{
    ncr[0][0]=1;
    for(int i=1;i<=50;i++)
    {
        for(int j=0;j<=50;j++)
        {
            if(j>i)ncr[i][j]=0;
            else if(j==i || j==0)ncr[i][j]=1;
            else ncr[i][j]=(ncr[i-1][j-1]+ncr[i-1][j]);
        }
    }
}

int main()
{

    pre();
    int t;
    long long k=0;
    for(int i=1;i<=50;i++)k+=ncr[50][i];
    cin>>t;
    while(t--)
    {
        long long n,v1,v2;
        long long w;
        cin>>n>>v1>>v2>>w;
        long long need=(n/2)+1;
        need-=v1;
        long long left=n-(v1+v2);

        if(need>left)
        {
            cout<<"RECOUNT!"<<endl;
        }
        else if(need<=0)
        {
            cout<<"GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!"<<endl;
        }
        else
        {
            unsigned long long all=0;
            //binary string of lengeth left with atleast need 1
            for(int i=need;i<=left;i++)all+=ncr[left][i];
            unsigned long long down=1;
            //all possible binary string of length left
            for(int i=1;i<=left;i++)down*=2;
            all*=100;
            w*=down;
            if(all<=w)
            {
                cout<<"PATIENCE, EVERYONE!"<<endl;
            }
            else
            {
                cout<<"GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!"<<endl;
            }
        }
    }
    return 0;
}
