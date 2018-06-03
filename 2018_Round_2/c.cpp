// 2018 Round 2 Problem C
#include<algorithm>
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
#include<set>
#include<sstream>
#include<string>
#include<utility>
#include<vector>

using namespace std;

// I/O

struct input {
  int N;
  vector<vector<int>> grid;
};

template<typename T0, typename T1>
istream& operator>>(istream& is, pair<T0, T1>& x) {
  is >> x.first >> x.second;
  return is;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& x) {
  for(size_t i = 0; i < x.size(); ++i) { is >> x[i]; std::cout << "Read:" << i << endl; }
  return is;
}

istream& operator>>(istream& is, input& in) {
  is >> in.N;
  int n;
  for (int i = 0; i < in.N; ++i) {
    in.grid.push_back(vector<int>{});
    for (int j = 0; j < in.N; ++j) {
      is >> n; in.grid[i].push_back(n); 
    }
  }
  return is;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1>& x) {
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

#define F first
#define S second

int cc(int x) {
  return x*(x-1)/2;
}

int changes(input& in, int x, int y) {
  if (in.grid[x][y] == 0) return 0;
  vector<int> cols(in.N, 0);
  cols[y] = 1;
  vector<int> rows(in.N, 0);
  rows[x] = 1;
  vector<pair<int, int>> r;
  auto & g = in.grid;
  for (int i = x; i < in.N; ++i) {
    for (int j = y; j < in.N; ++j) {
      if (g[i][j] == g[x][y] && (rows[i] > 0 || cols[j] > 0)) {
        r.push_back(make_pair(i, j));
        rows[i]++;
        cols[j]++;
      }
    }
  }
  int count = 0;
  for (int i : rows) count += cc(i);
  for (const auto& p : r) g[p.F][p.S] = 0;
  //cout << "Result size (" << x << ", " << y << ") = " << r.size() << endl;
  return count;
}

void solve(input & in) {
  // count same costumes
  int count = 0;
  for (int i = 0; i < in.N; ++i) {
    for (int j = 0; j < in.N; ++j) {
      count += changes(in, i, j);
    }
  }
  cout << count;
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
