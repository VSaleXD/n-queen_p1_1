#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<int> vll;
typedef vector<vll> vvl;
typedef pair<int, int> pll;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<bool> vb;
typedef vector<vb> vvb;

bool isSafe(int row, int column, const vll& columns) {
  for (int previousRow = 0; previousRow < row; ++previousRow) {
    int previousColumn = columns[previousRow];

    if (previousColumn == column) return false;
    if (abs(previousRow - row) == abs(previousColumn - column)) return false;
  }
  return true;
}

void searchRow(int row, int n, vll& columns, vvl& solutions) {
  if (row == n) {
    solutions.push_back(columns);
    return;
  }

  for (int column = 0; column < n; ++column) {
    if (isSafe(row, column, columns)) {
      columns[row] = column;
      searchRow(row + 1, n, columns, solutions);
      columns[row] = -1;
    }
  }
}

vvl solveNQueens(int n) {
  vll columns(n, -1);
  vvl solutions;
  searchRow(0, n, columns, solutions);
  return solutions;
}

int main() {
  int n;
  if (cin >> n) {
    vvl ans = solveNQueens(n);
    cout << ans.size() << "\n";
  }
  return 0;
}