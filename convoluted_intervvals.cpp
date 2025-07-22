#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<long long> a_freq(m + 1, 0), b_freq(m + 1, 0);
    for (int i = 0; i < n; i++) {
        a_freq[a[i]]++;
        b_freq[b[i]]++;
    }

    vector<long long> win_start(2 * m + 1, 0), win_end(2 * m + 1, 0);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            win_start[i + j] += a_freq[i] * a_freq[j];
            win_end[i + j] += b_freq[i] * b_freq[j];
        }
    }

    long long win_count = 0;
    for (int k = 0; k <= 2 * m; k++) {
        win_count += win_start[k];
        cout << win_count << "\n";
        win_count -= win_end[k];
    }

    return 0;
}

