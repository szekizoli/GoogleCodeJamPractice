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
  int n;
  vector<vector<int>> m;
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
  is >> in.n;
  in.m.resize(in.n);
  for (auto& v : in.m) v.resize(in.n);
  return is >> in.m;
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

int repeated(vector<int> const& v) {
  vector<bool> mark(v.size(), false);
  for (int i : v) {
    if (mark[i-1]) return 1; // seen this
    mark[i-1] = true;
  }
  for (bool b: mark) {
    if (!b) return 1;
  }
  return 0;
}

void solve(input const& in) {
  int k = 0, r = 0, c = 0;
  for (int i = 0; i < in.n; ++i) k += in.m[i][i];
  for (auto const& v : in.m) r += repeated(v);
  for (int i = 0; i < in.n; ++i) {
    vector<int> v;
    for (int j = 0; j < in.n; ++j) {
      v.push_back(in.m[j][i]);
    }
    c += repeated(v);
  }
  cout << k << " " << r << " " << c;
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
