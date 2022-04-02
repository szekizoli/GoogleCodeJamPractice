#include<algorithm>
#include<array>
#include<bitset>
#include<cmath>
#include<cstdint>
#include<cctype>
#include<iostream>
#include<iomanip>
#include<iterator>
#include<limits>
#include<map>
#include<memory>
#include<numeric>
#include<queue>
#include<set>
#include<sstream>
#include<string>
#include<utility>
#include<vector>

using namespace std;

// I/O

using num_t = unsigned long long;
using mod_t = size_t;
using edge_t = pair<mod_t, num_t>;
const size_t max_modules = 100000;

struct input {
  int n; // number of modules
  vector<num_t> f; // fun factor per module
  vector<size_t> p; // pointing to
};

template<typename T0, typename T1>
istream& operator>>(istream& is, pair<T0, T1>& x) {
  is >> x.first >> x.second;
  return is;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& x) {
  for(size_t i = 0; i < x.size(); ++i) is >> x[i];
  return is;
}

template<typename T, size_t N>
istream& operator>>(istream& is, array<T, N>& x) {
  for(size_t i = 0; i < x.size(); ++i) is >> x[i];
  return is;
}

istream& operator>>(istream& is, input& in) {
  is >> in.n;
  in.f.resize(in.n);
  in.p.resize(in.n);
  return is >> in.f >> in.p;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1> const& x) {
  os << x.first << " " << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, set<T> const& x) {
  for(T t : x) os << t << " ";
  return os;
}

bool compare(pair<mod_t, num_t> a, pair<mod_t, num_t> b)
{
    return a.second < b.second;
}

set<mod_t> find_initiators(size_t n, bitset<100001> const& pointed_to)
{
  set<mod_t> initiators;
  for (mod_t i = 0; i < n+1; ++i) {
    if (!pointed_to[i]) {
      initiators.insert(i);
    }
  }
  return initiators;
}

mod_t idx_to_node(size_t idx)
{
  return idx + 1;
}

size_t node_to_idx(mod_t node)
{
  return node - 1;
}

void calculate_cost(mod_t from, array<num_t, 100001> const& tree, vector<num_t> const& node_cost, array<edge_t, 100001> & costs)
{
  num_t cost = 0;
  while(from > 0) 
  {
    mod_t to = tree[from];
    edge_t edge = costs[to];
    cost = std::max(cost, node_cost[node_to_idx(from)]);
    if (edge.second > 0 && edge.second < cost) return;
    edge.first = from;
    edge.second = cost;
    costs[to] = edge;
    from = to;
  }
}

struct graph 
{
  size_t n;
  array<num_t, 100001> tree;
  bitset<100001> pointed_to;
  set<mod_t> cross_points;
  set<mod_t> initiators;
  array<pair<mod_t, num_t>, 100001> costs;
  graph(input const& in) : n(in.n)
  {
      for(size_t i = 0; i < in.p.size(); ++i)  {
      mod_t mod = in.p[i];
      tree[idx_to_node(i)] = mod;
      if (pointed_to[mod]) {
        cross_points.insert(mod);
      } 
      pointed_to[mod] = true;
    }
    initiators = find_initiators(in.n, pointed_to);
    for (mod_t i : initiators)
    {
      calculate_cost(i, tree, in.f, costs);
    }
  }

  void print()
  {
    cout << "X " << cross_points << endl;
    cout << "I " << initiators << endl;
    for (size_t i = 0; i < n + 1; ++i) {
      edge_t edge = costs[i];
      if (edge.first == 0) continue;
      cout << i << " -> " << edge.first << " = " << edge.second << endl;
    }
  }
};

// Algorithm
void solve(input const& in) {
  graph g(in);
  
  set<pair<mod_t, mod_t> > selected;
  for (mod_t i = 0; i < g.n + 1; ++i) {
    edge_t edge = g.costs[i];
    if (edge.first == 0) continue;
    selected.insert({i, edge.first});
  }

  num_t sum = 0;
  for (mod_t i : g.initiators) {
    mod_t start = i;
    mod_t next = g.tree[i];
    num_t max_f = in.f[start - 1];
    while (next > 0 && selected.count({next, start}) > 0) {
      start = next;
      next = g.tree[next];
      max_f = std::max(max_f, in.f[start - 1]);
    }
    sum += max_f;
  }
  cout << sum;

}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": ";
    solve(in);
    cout << endl;
  }
  return 0;
}
