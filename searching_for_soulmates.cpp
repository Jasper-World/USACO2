#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long cow1, cow2;
        cin >> cow1 >> cow2;

        long long answer = LLONG_MAX;

        for (int removed = 0; (cow2 >> removed) > 0; ++removed) {
            long long steps = 0;
            long long prefix = cow2 >> removed;
            long long cow = cow1;

            while (cow > prefix) {
                if (cow % 2 == 1) {
                    cow++;
                    steps++;
                }
                cow /= 2;
                steps++;
            }

            steps += (prefix - cow);  
            steps += removed;         
            steps += __builtin_popcountll(cow2 & ((1LL << removed) - 1)); 

            answer = min(answer, steps);
        }

        cout << answer << '\n';
    }

    return 0;
}

