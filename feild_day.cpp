#include <bits/stdc++.h>
using namespace std;

inline void ckmin(int &a, int b) {
    if (b < a) a = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C, N;
    cin >> C >> N;

    vector<int> teams_mask;

    vector<int> popcount_first_half(1 << ((C + 1) / 2));
    for (int i = 0; i < (int)popcount_first_half.size(); i++) {
        popcount_first_half[i] = __builtin_popcount(i);
    }

    vector<int> dist(1 << C, C);

    for (int i = 0; i < N; i++) {
        string s; 
        cin >> s;

        int mask = 0;
        for (int j = 0; j < C; j++) {
            int bit = (s[j] == 'H' ? 1 : 0);
            mask |= (bit << j);
        }
        teams_mask.push_back(mask);

        int half = C / 2;
        for (int sub = 0; sub < (1 << half); sub++) {
            int combined_mask = mask ^ sub;
            ckmin(dist[combined_mask], popcount_first_half[sub]);
        }
    }

    int half = C / 2;
    int other_half = C - half;

    for (auto mask : teams_mask) {
        int complement = ((1 << C) - 1) ^ mask;

        int res = C;
        for (int sub = 0; sub < (1 << other_half); sub++) {
            int query_mask = complement ^ (sub << half);
            int diff = dist[query_mask] + popcount_first_half[sub];
            ckmin(res, diff);
        }

        cout << C - res << "\n";
    }

    return 0;
}

