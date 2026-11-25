#include <vector>
#include <string>
#include <utility>
#include <array>
#include <bitset>
#include <cstdlib>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> solveWalled(
    int n,
    const vector<string>& grid
) {
    constexpr int MAX = 144;

    using Bits = bitset<MAX>;

    vector<pair<int, int>> cells;
    vector<vector<pair<int, int>>> solutions;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] != 'W') {
                cells.push_back({r, c});
            }
        }
    }

    const int m = (int)cells.size();

    if (m == 0) {
        return solutions;
    }

    array<Bits, MAX> compatible{};

    for (int i = 0; i < m; ++i) {
        const int r1 = cells[i].first;
        const int c1 = cells[i].second;

        for (int j = i + 1; j < m; ++j) {
            const int r2 = cells[j].first;
            const int c2 = cells[j].second;

            const int dr = r2 - r1;
            const int dc = c2 - c1;

            if (dr != 0 && dc != 0 &&
                abs(dr) != abs(dc)) {
                continue;
            }

            const int rs = (dr > 0) - (dr < 0);
            const int cs = (dc > 0) - (dc < 0);

            int r = r1 + rs;
            int c = c1 + cs;

            bool blocked = false;

            while (r != r2 || c != c2) {
                if (grid[r][c] == 'W') {
                    blocked = true;
                    break;
                }

                r += rs;
                c += cs;
            }

            if (blocked) {
                compatible[i].set(j);
                compatible[j].set(i);
            }
        }
    }

    vector<int> current;
    current.reserve(m);

    int bestCount = 0;

    auto saveSolution = [&]() {
        const int count = (int)current.size();

        if (count < bestCount) {
            return;
        }

        if (count > bestCount) {
            bestCount = count;
            solutions.clear();
        }

        vector<pair<int, int>> result;
        result.reserve(count);

        for (int v : current) {
            result.push_back(cells[v]);
        }

        solutions.push_back(move(result));
    };

    auto colorSort = [&](const Bits& P,
                         int* order,
                         int* bounds) -> int {

        Bits remaining = P;
        int total = 0;
        int color = 0;

        while (remaining.any()) {
            ++color;

            Bits available = remaining;

            while (available.any()) {
                int v = 0;

                while (!available.test(v)) {
                    ++v;
                }

                order[total] = v;
                bounds[total] = color;
                ++total;

                remaining.reset(v);
                available.reset(v);

                available &= ~compatible[v];
            }
        }

        return total;
    };

    auto dfs = [&](auto&& self, Bits P) -> void {

        int order[MAX];
        int bounds[MAX];

        const int count = colorSort(
            P,
            order,
            bounds
        );

        for (int i = count - 1; i >= 0; --i) {

            if ((int)current.size() + bounds[i] < bestCount) {
                return;
            }

            const int v = order[i];

            current.push_back(v);

            saveSolution();

            Bits next = P & compatible[v];

            if (next.any()) {
                self(self, next);
            }

            current.pop_back();

            P.reset(v);
        }
    };

    Bits candidates;

    for (int i = 0; i < m; ++i) {
        candidates.set(i);
    }

    dfs(dfs, candidates);

    return solutions;
}