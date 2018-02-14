// 2016  Round 1B Problem C
#include<algorithm>
#include<bitset>
#include<cmath>
#include<iostream>
#include<limits>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<unordered_map>
#include<vector>

#include "bipartite_graph.h"
#include "minimal_edge_cover.h"

using namespace std;

// I/O

struct input {
  vector<pair<string, string>> topics;
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

istream& operator>>(istream& is, input& in) {
  int N; is >> N;
  in.topics.resize(N);
  is >> in.topics;
  return is;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1> const& x) {
  os << x.first << x.second;
  return os;
}


// Algorithm

int solve(input const& in) {
  bipartite_graph<string> graph;
  for (auto const& p : in.topics) {
    graph.insert_edge(edge_t<string>("A_"+p.first, "B_"+p.second));
  }
  auto min_edge_cover = minimal_edge_cover(graph);
  int edge_size = in.topics.size();
  int vertex_size = graph.size();
  for (const auto& e : min_edge_cover) cout << e << endl;
  cout << "min_edge_cover = " << min_edge_cover.size() << endl;
  int min_edge_cover_size = min_edge_cover.size();
  return std::max(0, edge_size + min_edge_cover_size - vertex_size);  
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": " << solve(in) << endl;
  }
  return 0;
}
