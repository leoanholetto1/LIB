#include<bits/stdc++.h>
#pragma GCC target("popcnt")
#include <boost/multiprecision/cpp_int.hpp>
#include <bits/extc++.h>                         

#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define vet(Type) vector<Type>
#define all(x) x.begin(),x.end()
#define s second
#define f first
#define lc ((n)<<1)
#define rc ((n)<<1|1)
#define pb push_back
#define sz size()
#define isPowerOfTwo(S) (!(S & (S-1)))
#define LSOne(S) ((S)&-(S))
#define Log2(x) (31^__builtin_clz(x))
#define LLog2(x) (63 ^ __builtin_clzll(x))

using namespace std;
using namespace boost::multiprecision;
using namespace __gnu_pbds;

typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> pds; 
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update> ost;//repetido
typedef unsigned long long ull;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int,ll> pil;
using cd = complex<double>;


int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

int dxx[] = {-1,-1,0,1,1,1,0,-1};
int dyy[] = {0,1,1,1,0,-1,-1,-1};

const int maxN= 2*1e5 +5;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ll mod = 1000000007;
const ld PI = acos(-1.0);
const double ep = 1e-9;


void solve(){

}

int main() {
	IOS;
	//clock_t tStart = clock();
	solve();
	//cerr<<fixed<<setprecision(10)<<"\nTime Taken: "<<(double)(clock()- tStart)/CLOCKS_PER_SEC<<endl; 
	return 0;
}
