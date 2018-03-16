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

void insert2(string &s)
{
	//add 2 to odd length consecutive 2 
	int cnt = 0;
	int len=s.length();
	for (int i = len-1; i >= 0; i--) 
	{
		if (s[i] == '2')cnt++;
		else 
		{
			if(cnt&1)s.insert(i+1, "2");
			cnt=0;
		}
	}
	if(cnt&1)s.insert(0, "2");
}

void insert4(string &s)
{
  //add 4 to odd length consecutive 4 after 2 compression 
	if (s == "22")return;
	int cnt=0;
	for (int i=0; i<(int)s.length(); i++) 
	{
		if (s[i] == '2')cnt++;
		else if (s[i] == '4')cnt+=2;
		else 
		{
			cnt/=2;
			if(cnt&1)s.insert(i,"4");
			cnt=0;
		}
	}
	cnt/=2;
	if (cnt&1)s+="4";
}

void insert8(string &s)
{
	//pad with 8 in the end
	int sum = 0;
	for(char i:s)sum+= (i-'0');
	int pow2 = 1;
	while (pow2 < sum)pow2<<= 1;
	sum=(pow2-sum)/8;
	rept(i,0,sum)s+='8';
}

int main()
{
	int t;
	cin>>t;
	while (t--)
	{
		string s;
		cin >> s;
		
		if (s.length() > 1) 
		{
			insert2(s);
			insert4(s);
			insert8(s);
		}
		cout << s << endl;
	}
	return 0;
}
