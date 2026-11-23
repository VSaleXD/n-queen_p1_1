#include <cstdint>
#include <vector>

namespace {

int N;
uint32_t FULL;
int cur[32];
std::vector<std::vector<int>>* out;

void dfs(int row, uint32_t cols, uint32_t d1, uint32_t d2) {
    uint32_t avail = FULL & ~(cols | d1 | d2);
    if (row == N - 1) {
        while (avail) {
            cur[row] = __builtin_ctz(avail);
            avail &= avail - 1;
            out->emplace_back(cur, cur + N);
        }
        return;
    }
    while (avail) {
        uint32_t bit = avail & (~avail + 1);
        avail ^= bit;
        cur[row] = __builtin_ctz(bit);
        dfs(row + 1, cols | bit, ((d1 | bit) << 1) & FULL, (d2 | bit) >> 1);
    }
}

const size_t KNOWN[15] = {1, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596};

}

std::vector<std::vector<int>> solveNQueens(int n) {
    std::vector<std::vector<int>> result;
    if (n <= 0 || n > 31 || n == 2 || n == 3) return result;
    if (n <= 14) result.reserve(KNOWN[n]);

    N = n;
    FULL = (1u << n) - 1;
    out = &result;

    if (n == 1) {
        result.push_back({0});
        return result;
    }

    for (int c0 = 0; c0 <= (n - 1) / 2; ++c0) {
        uint32_t bit = 1u << c0;
        size_t start = result.size();
        cur[0] = c0;
        dfs(1, bit, (bit << 1) & FULL, bit >> 1);
        if (c0 == n - 1 - c0) continue;
        size_t end = result.size();
        for (size_t i = start; i < end; ++i) {
            int tmp[32];
            for (int r = 0; r < n; ++r) tmp[r] = n - 1 - result[i][r];
            result.emplace_back(tmp, tmp + n);
        }
    }
    return result;
}