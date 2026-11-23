#include<iostream>
#include<vector>
#include<map>
#include<string>


using namespace std;

typedef vector<int> vll;
typedef vector<vll> vvl;
typedef pair<int, int> pll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define sp << " " <<
#define debug(x) cout << x << endl
#define sz(x) (int)(x.size())

bool isSafe(vs &board, int row, int col, int n) {
    for(int i=0; i<row; i++){
        if(board[i][col] == 'Q') return false;
    }
    for(int i=row-1, j=col-1; i>=0 && j>=0; i--, j--){
        if(board[i][j] == 'Q') return false;
    }
    for(int i=row-1, j=col+1; i>=0 && j<n; i--, j++){
        if(board[i][j] == 'Q') return false;
    }
    return true;
}

void nQueens(vs &board, int row, int n, vector<vs> &res) {
    if (row == n) {
        res.push_back(board);
        return;
    }
    for(int j=0; j<n; j++){
        if(isSafe(board, row, j, n)){
            board[row][j] = 'Q';
            nQueens(board, row + 1, n, res);
            board[row][j] = '.';
        }
    }
}

vector<vll> solveNQueens(int n){
    vs board(n, string(n, '.'));
    vector<vs> res;
    nQueens(board, 0, n, res);

    vector<vll> solutions;
    solutions.reserve(res.size());
    for (const vs &solutionBoard : res) {
        vll columns(n);
        for (int row=0; row<n; row++) {
            for (int column=0; column<n; column++) {
                if (solutionBoard[row][column] == 'Q') {
                    columns[row] = column;
                    break;
                }
            }
        }
        solutions.push_back(columns);
    }
    return solutions;
}