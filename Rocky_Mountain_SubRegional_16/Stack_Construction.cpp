#include<bits/stdc++.h>
using namespace std;

const int maxi = 222;
int dp[maxi][maxi];
string str;
int n;

int lol(int l, int r)
{
    if(l > r) return 0;
    if(l == r) return 3;

    if(dp[l][r] != -1) return dp[l][r];
    int ret = INT_MAX;
    if(str[l] == str[r]) ret = min(ret, 1 + lol(l, r-1));

    for(int i=l+1; i<=r; i++) 
    {
        ret = min(ret, lol(l, i-1) + lol(i, r));
    }

    return dp[l][r] = ret;
}

int main() 
{
    int n1;
    cin>>n1;
    cin.ignore();

    for(int i=1; i<=n1; i++) {
        memset(dp, -1, sizeof(dp));
        getline(cin, str);
        n = str.size();
        cout<<lol(0, n-1)<<endl;
    }

    return 0;
}
