// 2020 Round 1A Problem B
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
  long N;
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
  return is >> in.N;
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

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << endl;
  return os;
}

// Algorithm

vector<long> next(vector<long> const& v) {
  if (v.size() == 1) return vector<long> {1, 1};
  vector<long> r {1};
  for (size_t i = 0; i < v.size() - 1; ++i) {
    r.push_back(v[i] + v[i+1]);
  }
  r.push_back(1);
  return r;
}

vector<vector<long>> generate() {
  vector<vector<long>> p;
  p.emplace_back(vector<long>{1});
  for (long r = 0; r < 60; ++r) {
    p.emplace_back(next(p[r]));
  }
  return p;
}

struct context {
  vector<vector<long>> const& tri;
  int r = 1;
  int k = 1;
  long s = 0;

  void select() { s -= value(); }
  context& operator++() {
    ++r;
    if (!at_front()) ++k;
    return *this;
  }

  bool operator()() const { return s > 0; }

  bool at_front() const { return k == 1; }
  bool at_back()  const { return k == r; }

  long value() const { return tri[r-1][k-1]; }
  vector<long> const& operator[](size_t i) const { return tri[i]; }
};

ostream& operator<<(ostream& os, context const& x) {
  return os << x.r << " " << x.k;
}

const long LIMIT = 30;

void solve(input const& in, vector<vector<long>> const& tri) {
  long N = in.N - LIMIT;
  context ctx {tri, 1, 1, in.N};
  cout << ctx << endl; 
  ctx.select();
  for (long i = 1; i < LIMIT && ctx() && in.N > LIMIT; ++i) {
    ++ctx;
    if (((1 << i) & N) > 0) {
      if (ctx.at_front()) {
        for (size_t j = 0; j < ctx[i].size(); ++j) {
          cout << ctx << endl;
          ctx.select();
          if (!ctx.at_back()) ++ctx.k;
        }
      } else {
        for (size_t j = 0; j < ctx[i].size(); ++j) {
          cout << ctx << endl;
          ctx.select();
          if (!ctx.at_front()) --ctx.k;
        }
      } 
    } else {
      cout << ctx << endl;
      ctx.select();
    }
  }

  while (ctx()) {
    cout << ++ctx << endl;
    ctx.select();
  }
}

int main() {
  vector<vector<long>> tri = generate();
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": " << endl;
    solve(in, tri);
  }
  return 0;
}
