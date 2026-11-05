#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define ri(n) scanf("%d",&n)
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()

using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<ld> vd;

const int inf = 1e9;
const int nax = 1e5+200;
const ld pi = acos(-1);
const ld eps= 1e-9;

int dr[] = {1,-1,0, 0,1,-1,-1, 1};
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

ostream& operator<<(ostream& os, const ii& pa) {
  return os << "("<< pa.fi << ", " << pa.se << ")";
}

bool solve(){
    struct dsu{
        vi p, r; int comp;
        dsu(int n): p(n), r(n, 1), comp(n){iota(all(p), 0);}
        int find_set(int i){return p[i] == i ? i : p[i] = find_set(p[i]);}
        bool is_same_set(int i, int j){return find_set(i) == find_set(j);}
        void union_set(int i, int j){
            if((i = find_set(i)) == (j = find_set(j))) return;
            if(r[i] > r[j]) swap(i, j);
            r[j] += r[i]; r[i] = 0;
            p[i] = j; --comp;
        }
    };
    struct edges{
        int a,b,c;
    };
    int n,m; cin>>n>>m;
    dsu d1 = dsu(n);
    dsu d2 = dsu(n);
    vector<edges> vt;
    for(int i = 0; i<m; i++){
        int a,b,c; cin>>a>>b>>c;
        vt.emplace_back(edges{a,b,c});
        if(c==1){
            d1.union_set(a,b);
        } else{
            d2.union_set(a,b);
        }
    }
    for(auto &e : vt){
        if(e.c==1 && d2.is_same_set(e.a,e.b)){
            return false;
        }
        if(e.c==0 && d1.is_same_set(e.a,e.b)){
            return false;
        }
    }
    return true;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout << setprecision(20)<< fixed;
  int t=1;
  while(t--){
    if(solve()){
        cout<<"YES"<<el;
    } else{
        cout<<"NO"<<el;
    }
  }
}
