#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100005;

int cow[MAXN];             
bool visited[MAXN];        
int answer[MAXN];          
int cnt[MAXN];           
int uniqueCount = 0;       

vector<int> graph[MAXN];  
vector<int> reachable[MAXN]; 
queue<int> q;              


void add(int node) {
    for (int pos : reachable[node]) {
        if (cnt[pos] == 0) uniqueCount++;
        cnt[pos]++;
    }
}

void remove(int node) {
    for (int pos : reachable[node]) {
        cnt[pos]--;
        if (cnt[pos] == 0) uniqueCount--;
    }
}

void dfs(int position, const vector<int>& P) {
    visited[position] = true;
    add(position);
    q.push(position);
    int next_pos = P[position];
    if (!visited[next_pos]) dfs(next_pos, P);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> swapList(k);
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        swapList[i] = {a, b};
    }

    for (int i = 1; i <= n; i++) {
        cow[i] = i;
        reachable[i].push_back(i); 
    }

    for (int i = 0; i < k; i++) {
        int a = swapList[i].first;
        int b = swapList[i].second;
        reachable[cow[a]].push_back(b);
        reachable[cow[b]].push_back(a);
        swap(cow[a], cow[b]);
    }

    vector<int> P(n + 1);
    for (int pos = 1; pos <= n; pos++) {
        P[cow[pos]] = pos;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            uniqueCount = 0;
            dfs(i, P);
            int totalUnique = uniqueCount;
            while (!q.empty()) {
                int c = q.front();
                q.pop();
                remove(c);
                answer[c] = totalUnique;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << "\n";
    }

    return 0;
}

