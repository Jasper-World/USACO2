#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 2500;

int N;
pair<int, int> cows[MAX_N];
int prefix[MAX_N + 1][MAX_N + 1];

int getSum(int x1, int y1, int x2, int y2) {
    return prefix[x2 + 1][y2 + 1] - prefix[x2 + 1][y1] - prefix[x1][y2 + 1] + prefix[x1][y1];
}

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        cows[i] = make_pair(x, y);
    }


    sort(cows, cows + N);
    for (int i = 0; i < N; i++) cows[i].first = i + 1;


    sort(cows, cows + N, [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });
    for (int i = 0; i < N; i++) cows[i].second = i + 1;


    for (int i = 0; i < N; i++) {
        prefix[cows[i].first][cows[i].second] = 1;
    }


    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }

    long long answer = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int x1 = min(cows[i].first, cows[j].first) - 1;
            int x2 = max(cows[i].first, cows[j].first) - 1;
            answer += (long long)getSum(0, i, x1, j) * getSum(x2, i, N - 1, j);
        }
    }

    cout << answer + 1 << "\n";  
    return 0;
}

