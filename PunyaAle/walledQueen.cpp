#include<iostream>
#include<vector>
#include<map>


using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

typedef vector<int> vll;
typedef vector<vll> vvl;
typedef pair<int, int> pll;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#define sp << " " <<
#define debug(x) cout << x << endl
#define sz(x) (int)(x.size())

// TLE
void solve() {
    int n, p;
    cin >> n >> p;
    int out=0;
    vvb cg(n, vb(n, false)), grid(n, vb(n, false)); // queen grid, pawn grid
    for (int i=0; i<p; i++) {
        int r, c;
        cin >> r >> c;
        r--; c--;
        grid[r][c]=true;
    }
    map<vvb, bool> memo;
    auto dfs=[&](auto&& self, int cnt, vvb cg) -> void {
        if (cnt==n) {
            if (!memo[cg]) {
                memo[cg]=true;
                // cout << "!" sp cnt << endl;
                // for (int i=0; i<n; i++) {
                //     for (int j=0; j<n; j++) cout << cg[i][j] << " ";
                //     cout << endl;
                // }
                out++;
            }
            return;
        }
        if (memo[cg]) return;
        memo[cg]=true;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (!cg[i][j] && !grid[i][j]) {
                    // can place a queen?
                    // check the row for any queens/pawns
                    bool ok=true;
                    for (int k=(i-1); k>=0; k--) {
                        if (cg[k][j]) {ok=false; break;}
                        if (grid[k][j]) break;
                    }
                    if (!ok) continue;
                    for (int k=(i+1); k<n; k++) {
                        if (cg[k][j]) {ok=false; break;}
                        if (grid[k][j]) break;
                    }
                    if (!ok) continue;
                    for (int k=(j-1); k>=0; k--) {
                        if (cg[i][k]) {ok=false; break;}
                        if (grid[i][k]) break;
                    }
                    if (!ok) continue;
                    for (int k=(j+1); k<=n; k++) {
                        if (cg[i][k]) {ok=false; break;}
                        if (grid[i][k]) break;
                    }
                    if (!ok) continue;
                    // diagonals
                    for (int k=0; k<n; k++) {
                        int dx=i-k, dy=j-k;
                        if (dx<0 || dy<0 || dx>=n || dy>=n) break;
                        if (cg[dx][dy]) {ok=false; break;}
                        if (grid[dx][dy]) break;
                    }
                    if (!ok) continue;
                    for (int k=0; k<n; k++) {
                        int dx=i-k, dy=j+k;
                        if (dx<0 || dy<0 || dx>=n || dy>=n) break;
                        if (cg[dx][dy]) {ok=false; break;}
                        if (grid[dx][dy]) break;
                    }
                    if (!ok) continue;
                    for (int k=0; k<n; k++) {
                        int dx=i+k, dy=j-k;
                        if (dx<0 || dy<0 || dx>=n || dy>=n) break;
                        if (cg[dx][dy]) {ok=false; break;}
                        if (grid[dx][dy]) break;
                    }
                    if (!ok) continue;
                    for (int k=0; k<n; k++) {
                        int dx=i+k, dy=j+k;
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
    dfs(dfs, 0, cg);
    cout << out << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}