#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

int N;
bool atLeast100[1000][1000];

ll countRectangles() {
    ll total = 0;
    for (int top = 0; top < N; ++top) {
        vector<bool> validColumns(N, true);
        for (int bottom = top; bottom < N; ++bottom) {
            int consecutive = 0;
            for (int col = 0; col < N; ++col) {
                validColumns[col] = validColumns[col] && atLeast100[bottom][col];
                if (validColumns[col]) {
                    consecutive++;
                    total += consecutive;
                } else {
                    consecutive = 0;
                }
            }
        }
    }
    return total;
}

int main() {
    cin >> N;
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> grid[i][j];


    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            atLeast100[i][j] = grid[i][j] >= 100;
    ll countAtLeast100 = countRectangles();


    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            atLeast100[i][j] = grid[i][j] > 100;
    ll countGreaterThan100 = countRectangles();


    cout << countAtLeast100 - countGreaterThan100 << "\n";
}

