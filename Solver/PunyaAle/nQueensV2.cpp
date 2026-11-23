#include <string>
#include <vector>
#include <cstdlib>

#include "nqueens.h"

namespace {

class Search {
 public:
  Search(int n) : n_(n), columns_(n, -1) {}

  std::vector<std::vector<int>> run() {
    searchRow(0);
    return solutions_;
  }

 private:
  int n_;
  std::vector<int> columns_;
  std::vector<std::vector<int>> solutions_;

  bool isSafe(int row, int column) const {
    for (int previousRow = 0; previousRow < row; ++previousRow) {
      int previousColumn = columns_[previousRow];

      if (previousColumn == column) return false;
      if (std::abs(previousRow - row) == std::abs(previousColumn - column)) return false;
    }
    return true;
  }

  void searchRow(int row) {
    if (row == n_) {
      solutions_.push_back(columns_);
      NQ_SNAPSHOT(nq::queensOf(columns_),
                  "solution " + std::to_string(solutions_.size()));
      return;
    }

    for (int column = 0; column < n_; ++column) {
      if (isSafe(row, column)) {
        columns_[row] = column;
        searchRow(row + 1);
        columns_[row] = -1;
      }
    }
  }
};

}  // namespace

std::vector<std::vector<int>> solveNQueens(int n) {
  return Search(n).run();
}
