// 2020 Round 1B Problem A
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
  int X, Y;
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
  return is >> in.X >> in.Y;
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

bool odd(int a) {
  return abs(a) % 2 == 1;
}

bool even(int a) {
  return !odd(a);
}

char next(int i) {
  switch (i) {
    case 0: return 'E';
    case 1: return 'N';
    case 2: return 'W';
    case 3: return 'S';
  }
  return '*';
}

using pos = pair<int, int>;
pos update(pair<int, int> const& p, int d, int v) {
  auto n = p;
  switch (d) {
    case 0: n.first += v; return n;
    case 1: n.second += v; return n;
    case 2: n.first -= v; return n;
    case 3: n.second -= v; return n;
  }
  return n;
}

void sol(int v, string result, string& min, pos const& cur, pos const& goal) {
  if (v == 256) return;

  for (int i = 0; i < 4; ++i) {
    auto current = result + next(i);
    auto next = update(cur, i, v);
    if (next == goal) {
      if (current.size() < min.size()) {
        min = current;
      }
      return;
    }
    sol(v+v, current, min, next, goal); 
  }
}

void solve(input const& in) {
  if ((odd(in.X) && odd(in.Y)) || (even(in.X) && even(in.Y))) {
    cout << "IMPOSSIBLE";
    return;
  }

  if (abs(in.X) > 100 || abs(in.Y) > 100) {
    cout << "IMPOSSIBLE";
    return;
  }
  
  auto goal = make_pair(in.X, in.Y);

  string  min = "IMPOSSIBLE";
  sol(1, "", min, make_pair(0, 0), goal);
  cout << min;
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
