#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

typedef int ll;
typedef vector<ll> vll;
typedef vector<vll> vvl;
typedef pair<ll, ll> pll;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#define sp << " " <<
#define debug(x) cout << x << endl
#define sz(x) (ll)(x.size())

// const ll BIG=1e18;
const ll MOD=1e9+7;
const ll INF=1e9;

// TLE
void solve() {
    ll n, p;
    cin >> n >> p;
    ll out=0;
    vvb cg(n, vb(n, false)), grid(n, vb(n, false)); // queen grid, pawn grid
    for (ll i=0; i<p; i++) {
        ll r, c;
        cin >> r >> c;
        r--; c--;
        grid[r][c]=true;
    }
    map<vvb, bool> memo;
    auto dfs=[&](auto&& self, ll cnt, vvb cg) -> void {
        if (cnt==n) {
            if (!memo[cg]) {
                memo[cg]=true;
                // cout << "!" sp cnt << endl;
                // for (ll i=0; i<n; i++) {
                //     for (ll j=0; j<n; j++) cout << cg[i][j] << " ";
                //     cout << endl;
                // }
                out++;
            }
            return;
        }
        if (memo[cg]) return;
        memo[cg]=true;
        for (ll i=0; i<n; i++) {
            for (ll j=0; j<n; j++) {
                if (!cg[i][j] && !grid[i][j]) {
                    // can place a queen?
                    // check the row for any queens/pawns
                    bool ok=true;
                    for (ll k=(i-1); k>=0; k--) {
                        if (cg[k][j]) {ok=false; break;}
                        if (grid[k][j]) break;
                    }
                    if (!ok) continue;
                    for (ll k=(i+1); k<n; k++) {
                        if (cg[k][j]) {ok=false; break;}
                        if (grid[k][j]) break;
                    }
                    if (!ok) continue;
                    for (ll k=(j-1); k>=0; k--) {
                        if (cg[i][k]) {ok=false; break;}
                        if (grid[i][k]) break;
                    }
                    if (!ok) continue;
                    for (ll k=(j+1); k<=n; k++) {
                        if (cg[i][k]) {ok=false; break;}
                        if (grid[i][k]) break;
                    }
                    if (!ok) continue;
                    // diagonals
                    for (ll k=0; k<n; k++) {
                        ll dx=i-k, dy=j-k;
                        if (dx<0 || dy<0 || dx>=n || dy>=n) break;
                        if (cg[dx][dy]) {ok=false; break;}
                        if (grid[dx][dy]) break;
                    }
                    if (!ok) continue;
                    for (ll k=0; k<n; k++) {
                        ll dx=i-k, dy=j+k;
                        if (dx<0 || dy<0 || dx>=n || dy>=n) break;
                        if (cg[dx][dy]) {ok=false; break;}
                        if (grid[dx][dy]) break;
                    }
                    if (!ok) continue;
                    for (ll k=0; k<n; k++) {
                        ll dx=i+k, dy=j-k;
                        if (dx<0 || dy<0 || dx>=n || dy>=n) break;
                        if (cg[dx][dy]) {ok=false; break;}
                        if (grid[dx][dy]) break;
                    }
                    if (!ok) continue;
                    for (ll k=0; k<n; k++) {
                        ll dx=i+k, dy=j+k;
                        if (dx<0 || dy<0 || dx>=n || dy>=n) break;
                        if (cg[dx][dy]) {ok=false; break;}
                        if (grid[dx][dy]) break;
                    }
                    if (!ok) continue;
                    // can place queen
                    // debug(i sp j);
                    cg[i][j]=true;
                    self(self, cnt+1, cg);
                    cg[i][j]=false;
                }
            }
        }
    };
    dfs(dfs, 0LL, cg);
    cout << out << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}