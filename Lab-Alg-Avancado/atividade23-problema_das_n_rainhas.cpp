/*
 * Problema: Problema das N-Rainhas (N-Queens)
 * Técnica/Algoritmo: Backtracking / Busca Exaustiva
 */
#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<bool>>& grid, int n, int l, int c) {
    // Colunas
    for (int i = 0; i < n; i++) {
        if (grid[i][c]) return false;
    }

    // Diagonal principal
    for (int i = l-1, j = c-1; i >= 0 && j >= 0; i--, j--) {
        if (grid[i][j]) return false;
    }

    // Diagonal secundária
    for (int i = l-1, j = c+1; i >= 0 && j < n; i--, j++) {
        if (grid[i][j]) return false;
    }

    return true;
}

void solver(vector<vector<bool>>& grid, int n, int row, int& possibilities, vector<int>& solve) {
    for (int i = 0; i < n; i++) {
        if (isSafe(grid, n, row, i)) {
            if (possibilities == 0) solve[row] = i+1;
            grid[row][i] = true;

            if (row == n-1) {
                possibilities++;
            } else {
                solver(grid, n, row+1, possibilities, solve);
            }

            grid[row][i] = false;
        }
    }

    return;
}

int main (void) {
    int n = 0;
    while (true) {
        cin >> n;
        if (n == 0) break;
        if (n == 2 || n == 3) {
            cout << "[" << n << ",0]\n" << "sem solucao\n";
            continue;
        }

        vector<vector<bool>> grid(n, vector<bool>(n, false));
        vector<int> solve(n, 0);
        int s = 0;

        solver(grid, n, 0, s, solve);
        cout << '[' << n << ',' << s << ']' << '\n';
        for (int i = 0; i < n; i++) {
            cout << solve[i] << ' ';
        }
        cout << '\n';
    }
}