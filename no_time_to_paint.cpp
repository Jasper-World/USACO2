#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    vector<int> prefix(n + 1, 0);
    vector<int> suffix(n + 1, 0);

 
    vector<char> stack_prefix;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i];

        while (!stack_prefix.empty() && stack_prefix.back() > s[i]) {
            stack_prefix.pop_back();
        }

        if (stack_prefix.empty() || stack_prefix.back() < s[i]) {
            stack_prefix.push_back(s[i]);
            prefix[i + 1]++;
        }
    }


    vector<char> stack_suffix;
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = (i == n - 1) ? 1 : suffix[i + 1];

        while (!stack_suffix.empty() && stack_suffix.back() > s[i]) {
            stack_suffix.pop_back();
        }

        if (stack_suffix.empty() || stack_suffix.back() < s[i]) {
            stack_suffix.push_back(s[i]);
            if (i != n - 1) suffix[i]++;
        }
    }


    for (int i = 0; i < q; i++) {
        int a = queries[i].first;
        int b = queries[i].second;

        int left = prefix[a - 1];
        int right = (b < n) ? suffix[b] : 0;

        cout << left + right << "\n";
    }

    return 0;
}

