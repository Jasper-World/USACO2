#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Edge {
    int to, w;
    Edge(int to, int w): to(to), w(w) {}
};

int n, m;
vector<int> loc;
vector<int> component;
vector<vector<Edge>> edges;

void dfs(int curr, int label, int minW) {
    if (component[curr] == label) return;
    component[curr] = label;
    for (auto &child : edges[curr]) {
        if (child.w >= minW) {
            dfs(child.to, label, minW);
        }
    }
}

bool valid(int minW) {
    fill(component.begin(), component.end(), -1);
    int numcomps = 0;
    for (int i = 0; i < n; i++) {
        if (component[i] == -1) {
            dfs(i, numcomps++, minW);
        }
    }
    for (int i = 0; i < n; i++) {
        if (component[i] != component[loc[i]]) return false;
    }
    return true;
}

int main() {
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");

    fin >> n >> m;
    loc.resize(n);
    component.resize(n, -1);
    edges.assign(n, vector<Edge>());

    for (int i = 0; i < n; i++) {
        fin >> loc[i];
        loc[i]--; 
    }

    for (int i = 0; i < m; i++) {
        int a, b, w;
        fin >> a >> b >> w;
        a--; b--;  
        edges[a].emplace_back(b, w);
        edges[b].emplace_back(a, w);
    }

    int low = 0, high = 1000000001;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (valid(mid)) low = mid;
        else high = mid - 1;
    }
    if (low > 1000000000) low = -1;

    fout << low << "\n";
    return 0;
}

