#include <algorithm>
#include <array>
#include <string>
#include <utility>
#include <vector>

namespace {

// Empat garis serang yang perlu dicek:
// baris, kolom, diagonal "\", dan diagonal "/".
constexpr int kFam = 4;

using Board = std::vector<std::pair<int, int>>;
using Solutions = std::vector<Board>;

int n_;
int total_;
std::vector<char> wall_;

std::vector<int> freeLeft_;

std::vector<int> seg_[kFam];
std::vector<char> last_[kFam];
std::vector<char> used_[kFam];

std::array<int, kFam> alive0_{};

int best_;
Board queens_;
Solutions solutions_;

// Sel hanya dapat dibuka jika berada di papan dan bukan wall.
bool openCell(int r, int c) {
  return r >= 0 && r < n_ && c >= 0 && c < n_ &&
         !wall_[r * n_ + c];
}

void dfs(int cell, int count, std::array<int, kFam> alive) {
  // Sel wall tidak dapat berisi ratu, jadi langsung dilewati.
  while (cell < total_ && wall_[cell]) ++cell;

  int bound = freeLeft_[cell];
  for (int f = 0; f < kFam; ++f)
    bound = std::min(bound, alive[f]);
  if (count + bound < best_) return;

  // Semua sel sudah diproses. Simpan papan hanya jika jumlah ratu
  // sama atau lebih besar dari catatan terbaik saat ini.
  if (cell == total_) {
    if (count < best_) return;
    if (count > best_) {
      best_ = count;
      solutions_.clear();
    }
    solutions_.push_back(queens_);
    return;
  }

  // Dua ratu tidak boleh berada pada segmen garis yang sama.
  // Ambil ID segmen sel ini untuk keempat keluarga garis.
  int segment[kFam];
  bool canPlace = true;
  for (int f = 0; f < kFam; ++f) {
    segment[f] = seg_[f][cell];
    if (used_[f][segment[f]]) canPlace = false;
  }

  // Pilihan pertama: menaruh ratu jika keempat segmennya masih kosong.
  if (canPlace) {
    std::array<int, kFam> nextAlive;
    for (int f = 0; f < kFam; ++f) {
      used_[f][segment[f]] = 1;
      nextAlive[f] = alive[f] - 1;
    }

    queens_.push_back({cell / n_, cell % n_});
    dfs(cell + 1, count + 1, nextAlive);
    queens_.pop_back();

    for (int f = 0; f < kFam; ++f)
      used_[f][segment[f]] = 0;
  }

  // Pilihan kedua: membiarkan sel kosong.
  // Jika sel adalah ujung segmen dan segmen belum dipakai,
  // segmen tersebut tidak lagi bisa menerima ratu pada sisa pencarian.
  std::array<int, kFam> nextAlive;
  for (int f = 0; f < kFam; ++f) {
    nextAlive[f] = alive[f] -
        ((last_[f][cell] && !used_[f][segment[f]]) ? 1 : 0);
  }
  dfs(cell + 1, count, nextAlive);
}

} 

std::vector<std::vector<std::pair<int, int>>> solveWalled(
    int n, const std::vector<std::string>& grid) {
  // Reset semua state setiap kali fungsi solver dipanggil.
  n_ = n;
  total_ = n * n;
  wall_.assign(total_, 0);
  freeLeft_.assign(total_ + 1, 0);
  best_ = 0;
  queens_.clear();
  solutions_.clear();

  for (int r = 0; r < n_; ++r) {
    for (int c = 0; c < n_; ++c)
      wall_[r * n_ + c] = (grid[r][c] == 'W');
  }

  // Isi freeLeft dari kanan ke kiri. Dengan demikian freeLeft[i]
  // menyatakan jumlah sel bebas pada posisi i sampai akhir papan.
  for (int i = total_ - 1; i >= 0; --i) {
    freeLeft_[i] = freeLeft_[i + 1] +
                   (wall_[i] ? 0 : 1);
  }

  const int dr[kFam] = {0, 1, 1, 1};
  const int dc[kFam] = {1, 0, 1, -1};

  // Bangun segmen untuk empat arah garis.
  // Wall memutus segmen, sedangkan sel bebas yang berhubungan
  // secara berurutan mendapat ID segmen yang sama.
  for (int f = 0; f < kFam; ++f) {
    seg_[f].assign(total_, -1);
    last_[f].assign(total_, 0);
    int count = 0;

    for (int r = 0; r < n_; ++r) {
      for (int c = 0; c < n_; ++c) {
        if (wall_[r * n_ + c]) continue; // tidak bisa ditempati
        if (openCell(r - dr[f], c - dc[f])) continue; // tidak ada queen di arah ini

        int id = count++;
        int cr = r;
        int cc = c;

        while (openCell(cr, cc)) {
          seg_[f][cr * n_ + cc] = id;
          int nextR = cr + dr[f];
          int nextC = cc + dc[f];
          last_[f][cr * n_ + cc] =
              !openCell(nextR, nextC);
          cr = nextR;
          cc = nextC;
        }
      }
    }

    alive0_[f] = count;
    used_[f].assign(count, 0);
  }

  dfs(0, 0, alive0_);
  return solutions_;
}
