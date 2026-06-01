/*
 * Problema: Solucionador de Sudoku
 * Técnica/Algoritmo: Backtracking
 */
#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> sub_grids_tem(9, vector<bool>(9, false));
vector<vector<bool>> linha_tem(9, vector<bool>(9, false));
vector<vector<bool>> coluna_tem(9, vector<bool>(9, false));
vector<vector<bool>> pre_definido(9, vector<bool>(9, false));

bool isSafe (int l, int c, int k) {
    if (sub_grids_tem[(l / 3) * 3 + (c / 3)][k-1] || 
        linha_tem[l][k-1] ||
        coluna_tem[c][k-1]
    ) return false;
    return true;
}

void insert(int i, int j, int k) {
    sub_grids_tem[(i / 3) * 3 + (j / 3)][k-1] = true;
    linha_tem[i][k-1] = true;
    coluna_tem[j][k-1] = true;
}

void remove (int i, int j, int k) {
    sub_grids_tem[(i / 3) * 3 + (j / 3)][k-1] = false;
    linha_tem[i][k-1] = false;
    coluna_tem[j][k-1] = false;
}

void solver(int& pos, int iter) {
    if (iter == 81) {
        pos++;
        return;
    }

    int l = iter / 9;
    int c = iter % 9;

    if (pre_definido[l][c]) {
        solver(pos, iter + 1);
        return;
    }

    for (int i = 1; i <= 9; i++) {
        if (isSafe(l, c, i)) {
            insert(l, c, i);
            solver(pos, iter + 1);
            remove(l, c, i);
        }
    }
}

int main(void) {
    int n;
    cin >> n;
    
    while (n--) {
        int i, j, k;
        cin >> i >> j >> k;
        insert(i - 1, j - 1, k);
        pre_definido[i-1][j-1] = true;
    }

    int pos = 0;
    solver(pos, 0);
    cout << pos << '\n';
    return 0;
}