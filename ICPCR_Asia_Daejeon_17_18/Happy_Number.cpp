#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

string toST(ll ret)
{
    string temp = "";
    while(ret) 
    {
        int v = ret%10;
        ret /= 10;
        temp += (v + '0');
    }
    reverse(temp.begin(), temp.end());
    return temp;
}

bool ok(string ini) 
{
    string s = ini;
    map<string,int> mp;
    while(true) 
    {
        mp[s] = 1;
        ll sum = 0;
        for(int i=0; i<s.size(); i++) 
        {
            ll val = s[i] - '0';
            sum += val*val;
        }

        s = toST(sum);
        if(s == "1") return 1;
        else if(mp[s]) return 0;
    }
}

int main() 
{
    string s;
    cin>>s;
    if(ok(s)) cout<<"HAPPY"<<endl;
    else cout<<"UNHAPPY"<<endl;
    return 0;
}
