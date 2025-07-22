#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.length();
    vector<vector<int>> prefixCounts(n + 1, vector<int>(3, 0));
    for (int i = 0; i < n; ++i) {
        prefixCounts[i + 1] = prefixCounts[i];
        if (s[i] == 'C') prefixCounts[i + 1][0]++;
        if (s[i] == 'O') prefixCounts[i + 1][1]++;
        if (s[i] == 'W') prefixCounts[i + 1][2]++;
    }

    int Q;
    cin >> Q;
    string result = "";

    while (Q--) {
        int l, r;
        cin >> l >> r;

        int countC = prefixCounts[r][0] - prefixCounts[l - 1][0];
        int countO = prefixCounts[r][1] - prefixCounts[l - 1][1];
        int countW = prefixCounts[r][2] - prefixCounts[l - 1][2];

        if ((countO + countW) % 2 == 0 && (countC + countO) % 2 == 1) {
            result += 'Y';
        } else {
            result += 'N';
        }
    }

    cout << result << endl;
    return 0;
}

