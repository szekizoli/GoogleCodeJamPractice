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

using num_t = long long;

struct input {
  num_t n, k;
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
  return is >> in.n >> in.k;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1> const& x) {
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

num_t first_unknown_of(vector<num_t> const& v) 
{
  for (num_t i = 0; i < v.size(); ++i) 
  {
    if (v[i] == 0) return i; 
  }
  return v.size();
}

size_t node_to_idx(num_t n)
{
  return n - 1;
}

num_t idx_to_node(size_t i)
{
  return i + 1;
}

bool read(num_t& node_id, num_t& edge_count)
{
  num_t ni, ec;
  cin >> ni;
  if (ni <= 0) { cerr << "READ INVALID" << ni << endl; return false; }
  cin >> ec;
  cerr << "READ> " << ni << " " << ec << endl;
  node_id = ni;
  edge_count = ec;
  return true;
}

struct graph
{
  vector<pair<num_t, num_t> > edges; // list of edges
  vector<num_t> nodes; // number of edges per node
  num_t total = 0;
  num_t nodes_seen = 0;
  graph(int size)
  {
    nodes.resize(size);
  }
  bool process(num_t node_id, num_t edge_count)
  {
    size_t idx = node_to_idx(node_id);
    bool seen = nodes[idx] > 0;
    if (!seen) { total += edge_count; nodes_seen++; }
    nodes[idx] = edge_count;
    return seen;
  }
  void add_edge(num_t node_0, num_t node_1)
  {
    edges.push_back({node_0, node_1});
  }
  num_t first_unknown()
  {
    return first_unknown_of(nodes);
  }
  void print()
  {
    cout << nodes << endl;
  }
  num_t count_seen()
  {
    return std::count_if(begin(nodes), end(nodes), [](num_t v){return v > 0;});
  }
  num_t total_edges()
  {
    return std::accumulate(begin(nodes), end(nodes), 0);
  }
};

void solve(input const& in)
{
  cerr << "INIT GRAPH N=" << in.n << " K=" << in.k << endl;
  graph g(in.n);
  num_t k = in.k;
  num_t node_id, edge_count;
  num_t total = 0;
  if (!read(node_id, edge_count)) exit(1);
  bool seen = g.process(node_id, edge_count);
  bool connected = true;
  cerr << "OP> W" << endl;
  cout << "W" << endl; --k; cout.flush();
  num_t prev_node = node_id;
  if (!read(node_id, edge_count)) exit(1);
  seen = g.process(node_id, edge_count);
  g.add_edge(prev_node, node_id);
  prev_node = node_id;
  while (k > 0) {
    if (!seen) {
      cerr << "OP> W" << endl;
      cout << "W" << endl; --k; cout.flush();
      connected = true;
    } else {
      num_t next_node = idx_to_node(g.first_unknown());
      cerr << "OP> T " << next_node << endl;
      cout << "T " << next_node << endl; --k; cout.flush();
      connected = false;
    }

    if (!read(node_id, edge_count)) exit(1);
    seen = g.process(node_id, edge_count);
    if (connected) g.add_edge(prev_node, node_id);
  }
  
  num_t estimate = (g.total_edges()/g.count_seen()/2) * in.n;
  cerr << "OP> E " << estimate << endl;
  cout << "E " << estimate << endl;
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    solve(in);
    cout << endl;
  }
  return 0;
}
