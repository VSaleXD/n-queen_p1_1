#include <vector>


namespace {

void backtrack(
    int row,
    int n,
    std::vector<int>& vertical,
    std::vector<int>& pos,
    std::vector<int>& neg,
    std::vector<int>& columns,
    std::vector<std::vector<int>>& solutions
) {
    if (row == n) {
        solutions.push_back(columns);
        return;
    }

    for (int col = 0; col < n; ++col) {
        const int positiveDiagonal = row + col;
        const int negativeDiagonal = col - row + n - 1;
        if (vertical[col] == 0 &&
            pos[positiveDiagonal] == 0 &&
            neg[negativeDiagonal] == 0) {
            columns[row] = col;
            vertical[col] = 1;
            pos[positiveDiagonal] = 1;
            neg[negativeDiagonal] = 1;

            backtrack(row + 1, n, vertical, pos, neg, columns, solutions);

            vertical[col] = 0;
            pos[positiveDiagonal] = 0;
            neg[negativeDiagonal] = 0;
        }
    }
}

}  // namespace

std::vector<std::vector<int>> solveNQueens(int n) {
    if (n <= 0 || n > 12) return {};

    std::vector<int> vertical(n, 0);
    std::vector<int> pos(2 * n - 1, 0);
    std::vector<int> neg(2 * n - 1, 0);
    std::vector<int> columns(n);
    std::vector<std::vector<int>> solutions;

    backtrack(0, n, vertical, pos, neg, columns, solutions);
    return solutions;
}
