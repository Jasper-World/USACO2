#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) {
        int M, K; cin >> M >> K;
        vector<int> last;  
        int xor_sum = 0;   
        for (int i = 0; i < 5; i++) {
            if (K & (1 << i)) {
                last.push_back((1 << (1 << i)) - 1);
                xor_sum += last.back();
            }
        }

        int diff = M - xor_sum;
        vector<int> pcM;       
        int flag = 0;
        if (diff < 0) {
            flag = 1;
        } else if (diff >= 2) {
            if (diff % 2 == 0) {
                pcM = {diff / 2, diff / 2};
            } else {
                pcM = {1, 2, (diff - 3) / 2, (diff - 3) / 2};
            }
        } else if (diff == 0) {
            pcM = {};
        } else {  
            if (last[0] == 1) {
                last[0] = 2;
            } else {
                flag = -1;
            }
        }

        if (flag) {
            cout << "-1\n";
        } else {
            cout << last.size() + pcM.size() << "\n";
            for (int i : last) cout << i << " ";
            for (int i : pcM) cout << i << " ";
            cout << "\n";
        }
    }
}

