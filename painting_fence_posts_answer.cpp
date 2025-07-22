#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <optional>
#include <vector>
using namespace std;

using ll = int64_t;
using pi = pair<int, int>;
template <class T> using V = vector<T>;
#define f first
#define s second

V<ll> tot_along;

// represent a position along a fence by
// - the index of the last fence post you touch when walking from the first
// fence post to that point (idx)
// - the additional distance you walk after touching that fence post (along)
struct Position {
    int idx, along;
    ll val() { return tot_along.at(idx) + along; }  // dist along fence
    int round_up() {                                // next fence post
        if (along == 0) return idx;
        return idx + 1;
    }
    int round_down() { return idx; }  // prev fence post
};

int dist(pi a, pi b) { return abs(a.f - b.f) + abs(a.s - b.s); }

V<int> index_in_ord;
map<int, V<pi>> by_x, by_y;
int P;

// get position of a cow along the fence, if
// located on a vertical segment
optional<Position> lookup(const V<pi> &v, int y) {
    int i = lower_bound(begin(v), end(v), make_pair(y, 0)) - begin(v);
    if (i < size(v) && v.at(i).f == y)
        return Position{index_in_ord.at(v.at(i).s), 0};
    if (i & 1) {
        pi a = v.at(i - 1), b = v.at(i);
        if ((index_in_ord.at(a.s) + 1) % P != index_in_ord.at(b.s)) swap(a, b);
        assert((index_in_ord.at(a.s) + 1) % P == index_in_ord.at(b.s));
        return Position{index_in_ord.at(a.s), abs(a.f - y)};
    }
    return nullopt;
}

// get position of a cow along the fence
Position get_pos(pi p) {
    if (by_x.count(p.f)) {
        auto res = lookup(by_x.at(p.f), p.s);
        if (res.has_value()) return res.value();
    }
    auto res = lookup(by_y.at(p.s), p.f);
    assert(res.has_value());
    return res.value();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N >> P;
    V<pi> posts(P);
    for (auto &[x, y] : posts) cin >> x >> y;
    for (int i = 0; i < P; ++i) {
        // fence posts for each x-coordinate, sorted by y
        by_x[posts[i].f].push_back({posts[i].s, i});
        // fence posts for each y-coordinate, sorted by x
        by_y[posts[i].s].push_back({posts[i].f, i});
    }
    V<V<int>> adj(P);  // posts adjacent to each post
    for (auto &[_, v] : by_x) {
        assert(size(v) % 2 == 0);
        sort(begin(v), end(v));
        for (int i = 0; i < size(v); ++i) adj[v[i].s].push_back(v[i ^ 1].s);
    }
    for (auto &[_, v] : by_y) {
        assert(size(v) % 2 == 0);
        sort(begin(v), end(v));
        for (int i = 0; i < size(v); ++i) adj[v[i].s].push_back(v[i ^ 1].s);
    }
    {
        V<int> ord{0};  // indices of posts we encounter if we walk around
                        // the fence starting from the first post
        while (true) {
            for (int x : adj[ord.back()]) {
                if (size(ord) > 1 && end(ord)[-2] == x) continue;
                ord.push_back(x);
                break;
            }
            if (ord.back() == 0) break;
        }
        ord.pop_back();
        assert(size(ord) == P);
        tot_along = {0};  // distance of each post along the fence
        for (int i = 1; i <= P; ++i)
            tot_along.push_back(
                tot_along.back() +
                dist(posts.at(ord.at(i - 1)), posts.at(ord.at(i % P))));
        index_in_ord.resize(P, -1);
        for (int i = 0; i < P; ++i) index_in_ord.at(ord[i]) = i;
    }
    V<int> cum(P + 1);  // difference array
    auto add = [&](int l, int r) {
        ++cum.at(l), --cum.at(r + 1);
    };  // add to range in difference array
    while (N--) {
        pi f1, f2;
        cin >> f1.f >> f1.s >> f2.f >> f2.s;
        auto p1 = get_pos(f1),
             p2 = get_pos(f2);  // position of each cow along the fence
        if (p1.val() > p2.val()) swap(p1, p2);
        const ll perim = tot_along.back();
        assert(2 * (p2.val() - p1.val()) != perim);
        if (2 * (p2.val() - p1.val()) > perim) {
            add(p2.round_up(), P - 1);
            add(0, p1.round_down());
        } else {
            add(p1.round_up(), p2.round_down());
        }
    }
    for (int i = 1; i < P; ++i) cum.at(i) += cum.at(i - 1);  // prefix sums
    for (int i = 0; i < P; ++i) cout << cum.at(index_in_ord.at(i)) << "\n";
}
