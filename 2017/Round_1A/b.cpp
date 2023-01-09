#include <algorithm>
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

typedef unsigned T;

pair<T, T> range(T Q, T p) {
  int lower = static_cast<T>(ceil((double(Q)/double(1.1))/double(p)));
  int upper = static_cast<T>(floor((double(Q)/double(0.9))/double(p)));
  return make_pair(lower, upper);
}

struct node_t {
  pair<T, T> p;
  node_t() {}
  node_t(pair<T, T> p) : p(p) {}
  node_t(T r, T p) : p(range(r, p)) {}
};

struct matcher {
  bool operator()(const node_t& x, const node_t& y) {
    return x.p.first <= y.p.second && y.p.first <= x.p.second;
  }
};

bool operator<(const node_t& x, const node_t& y) {
  return x.p < y.p;
}

ostream& operator<<(ostream& o, const node_t& n) {
  o << "(" << n.p.first << ", " << n.p.second << ")";
  return o;
}

void print(vector<vector<node_t>> const& graph) {
  for (const auto& v : graph) {
    for (const auto& n : v) {
      cout << n << " ";
    }
    cout << endl;
  }
  cout << endl;
}

template<typename I, typename R>
I find_match(I n, I f, I l, R r) {
  while(f != l) {
    if (r(*n, *f)) return f;
    ++f;
  }
  return l;
}

void solve() {
  T N, P;
  cin >> N >> P;
  vector<T> R(N, 0);
  for (T& t : R) cin >> t;
  vector<vector<node_t>> graph(N);
  for (int n = 0; n < N; ++n) {
    graph[n].reserve(P);
    for (int p = 0; p < P; ++p) {
      int r; cin >> r;
      pair<T, T> rg = range(r, R[n]);
      if (!(rg.second < rg.first)) graph[n].push_back(node_t(rg));
    }
    sort(begin(graph[n]), end(graph[n]));
  }
  if (N == 1) {
    cout << graph[0].size() << endl;
    return;
  }
  // N == 2, greedy
  int count = 0;
  auto first = begin(graph[0]);
  auto last = end(graph[0]);
  while (first != last) {
    auto match = find_match(first, begin(graph[1]), end(graph[1]), matcher());
    if (match != end(graph[1])) {
      ++count;
      graph[1].erase(match);
    }
    ++first;
  }
  cout << count << endl;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    cout << "Case #" << t+1 << ": ";
    solve();
  }
  return 0;
}
