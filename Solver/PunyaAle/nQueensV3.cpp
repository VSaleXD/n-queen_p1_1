#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#include "nqueens.h"

namespace {

const std::size_t kKnown[15] = {1,  1,   0,    0,    2,     10,    4,    40,
                                92, 352, 724, 2680, 14200, 73712, 365596};

class Solution {
 public:
  explicit Solution(int n)
      : n_(n), full_((n == 32) ? ~0u : ((1u << n) - 1)), columns_(n) {}

  std::vector<std::vector<int>> run() {
    if (n_ <= 14) solutions_.reserve(kKnown[n_]);
    helper(0, 0, 0, 0);
    return std::move(solutions_);
  }

 private:
  int n_;
  uint32_t full_;
  std::vector<int> columns_;
  std::vector<std::vector<int>> solutions_;

  // cols: kolom terpakai, d1/d2: diagonal terancam (sudah digeser ke baris ini).
  void helper(int row, uint32_t cols, uint32_t d1, uint32_t d2) {
    uint32_t avail = full_ & ~(cols | d1 | d2);

    // Baris terakhir: tidak perlu rekursi lagi.
    if (row == n_ - 1) {
      while (avail) {
        columns_[row] = __builtin_ctz(avail);
        avail &= avail - 1;
        solutions_.push_back(columns_);
      }
      return;
    }

    while (avail) {
      uint32_t bit = avail & (~avail + 1);  // bit terendah (kolom terkecil dulu)
      avail ^= bit;
      columns_[row] = __builtin_ctz(bit);
      helper(row + 1, cols | bit, ((d1 | bit) << 1) & full_, (d2 | bit) >> 1);
    }
  }
};

}  // namespace

std::vector<std::vector<int>> solveNQueens(int n) {
  if (n <= 0 || n > 31) return {};
  return Solution(n).run();
}