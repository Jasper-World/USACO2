#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const int N = 1e5 + 5;

int comp[N];
char cow[N];
vector<int> adj[N];
int num = 0;

void dfs(int u, char c) {
    if (comp[u]) return;
    comp[u] = num;
    for (int v : adj[u]) {
        if (cow[v] == c) dfs(v, c);
    }
}

int main() {
    ifstream fin("milkvisits.in");
    ofstream fout("milkvisits.out");

    int n, m;
    fin >> n >> m;

    for (int i = 1; i <= n; i++) {
        fin >> cow[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!comp[i]) {
            num++;
            dfs(i, cow[i]);
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        fin >> a >> b >> c;

        if (cow[a] == c || comp[a] != comp[b]) fout << '1';
        else fout << '0';
    }

    fout << '\n';
    return 0;
}

