#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<int> vll;
typedef vector<vll> vvl;
typedef pair<int, int> pll;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#define sp << " " <<
#define debug(x) cout << x << endl
#define sz(x) (int)(x.size())

vector<vector<pll>> solveWalled(int n, const vector<string>& grid) {
    vector<pll> queens;
    vector<vector<pll>> solutions;
    int bestCount = 0;

    auto attacks = [&](int row, int column) {
        for (const pll& queen : queens) {
            int qRow = queen.first;
            int qCol = queen.second;

            if (qRow != row && qCol != column &&
                abs(qRow - row) != abs(qCol - column)) {
                continue;
            }

            int rowStep = 0;
            if (qRow < row) rowStep = 1;
            if (qRow > row) rowStep = -1;

            int colStep = 0;
            if (qCol < column) colStep = 1;
            if (qCol > column) colStep = -1;

            int currRow = qRow + rowStep;
            int currCol = qCol + colStep;

            bool block = false;
            while (currRow != row || currCol != column) {
                if (grid[currRow][currCol] == 'W') {
                    block = true;
                    break;
                }
                currRow += rowStep;
                currCol += colStep;
            }

            if (!block) return true;
        }
        return false;
    };

    auto dfs = [&](auto&& self, int cell) -> void {
        if (cell == n * n) {
            int queenCount = (int)queens.size();
            if (queenCount > bestCount) {
                bestCount = queenCount;
                solutions.clear();
                solutions.push_back(queens);
            } else if (queenCount == bestCount) {
                solutions.push_back(queens);
            }
            return;
        }

        int row = cell / n;
        int column = cell % n;

        if (grid[row][column] != 'W' && !attacks(row, column)) {
            queens.push_back({row, column});
            self(self, cell + 1);
            queens.pop_back();
        }

        self(self, cell + 1);
    };

    dfs(dfs, 0);
    return solutions;
}
