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
//typedef pair<ll,ll>PI;
typedef pair<ll,pair<int,int> >PII;

typedef complex <long double> Complex;
typedef valarray <Complex> ValComplex;

const long double PI = 2 * acos(0.0);

void fft(ValComplex &p, bool inverse = 0) {
  int n = p.size();
  if(n <= 1) return;

  ValComplex f = p[slice(0, n/2, 2)],
             g = p[slice(1, n/2, 2)];

  // slice(a, b, c) will return number in indexes
  // a, a + c, a + 2c, .... a + (b-1)c  

  fft(f, inverse); fft(g, inverse); // FFT for F and G

  Complex omega_n = exp(Complex(0, 2 * PI / n)), w = 1;
  if(inverse) omega_n = Complex(1, 0) / omega_n;

  for(int k = 0; k < n / 2; k++) {
    // Here w = omega_n^k
    Complex add = w * g[k];   
    // this is p(x)
    p[k]       = f[k] + add;  
    // Note that p(-x) should be in (x+n/2)th position
    p[k + n/2] = f[k] - add;  
    w *= omega_n;
  }
}
void ifft(ValComplex &p) {
  fft(p, 1);
  p /= p.size(); // Divide each element by p.size()
}

vector<int> multiply(vector<int> a, vector<int> b) {
  int n = a.size(), m = b.size();
  int t = n + m - 1, sz = 1; // t is degree of R
  while(sz < t) sz <<= 1;  // rounding to nearest 2^x

  ValComplex x(sz), y(sz), z(sz);
  // Resize first polynomial by inserting 0.
  for(int i = 0; i < n; i++) x[i] = Complex(a[i], 0);
  for(int i = n; i < sz; i++) x[i] = Complex(0, 0);

  // Resize second polynomial by inserting 0.
  for(int i = 0; i < m; i++) y[i] = Complex(b[i], 0);
  for(int i = m; i < sz; i++) y[i] = Complex(0, 0);

  fft(x); fft(y);   // Do fft on both polynomial
  // Multiply in Point-Value Form
  for(int i = 0; i < sz; i++) z[i] = x[i] * y[i];

  ifft(z);  // Inverse FFT
  vector<int> res(sz);
  // Precision problem may occur, round to nearest integer
  for(int i = 0; i < sz; i++) res[i] = z[i].real() + 0.5;
  // remove trailing 0's
  while(res.size() > 1 && res.back() == 0) res.pop_back();
  return res;
}

string rps = "RPSRPS";
const int N = 3e5 + 5;

int cnt[N];
char s[N], p[N];
//Calculate win for R,S,P separately using FFT
int main() 
{
	int n, m;
	scanf("%d %d %s %s", &n, &m, s, p);
	for (int c = 0; c < 3; ++c) 
	{
		vector<int> a(n), b(m);
		for (int i = 0; i < n; ++i)a[i] = (s[i] == rps[c]);
		for (int i = 0; i < m; ++i)b[m-1-i] = (p[i] == rps[c+1]);
		vector<int> res = multiply(a, b);
		//x^(i)*x^(m-1-i)=x^m-1
		//m-1 has the answer for index 0
		for (int i = m-1; i < n+m; ++i) 
		{
		  cnt[i] += res[i];
		}
	}
	int ans = 0;
	for (int i = 0; i < n+m; ++i)ans = max(ans, cnt[i]);
	printf("%d\n", ans);
	return 0;
}
