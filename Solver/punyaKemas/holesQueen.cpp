#include <vector>
#include <string>
#include <cstdint>

namespace {

int N;
uint32_t FULL;
uint32_t holeMask[32];
int cur[32];
std::vector<std::vector<int>>* out;

void dfs(int row, uint32_t cols, uint32_t d1, uint32_t d2) {
    if (row == N) {
        out->emplace_back(cur, cur + N);
        return;
    }

    uint32_t avail = FULL & ~(cols | d1 | d2) & ~holeMask[row];
    while (avail) {
        uint32_t bit = avail & (~avail + 1);
        avail ^= bit;
        cur[row] = __builtin_ctz(bit);
        dfs(row + 1, cols | bit, ((d1 | bit) << 1) & FULL, (d2 | bit) >> 1);
    }
}

}

std::vector<std::vector<int>> solveHoles(int n, const std::vector<std::string>& grid) {
    std::vector<std::vector<int>> result;
    if (n <= 0 || n > 31) return result;

    N = n;
    FULL = (1u << n) - 1;

    for (int r = 0; r < n; ++r) {
        holeMask[r] = 0;
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] == 'H') {
                holeMask[r] |= (1u << c);
            }
        }
        if ((FULL & ~holeMask[r]) == 0) return result;
    }

    out = &result;
    dfs(0, 0, 0, 0);
    return result;
}