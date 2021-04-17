// 2020 Round 1C Problem A
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
  int x, y;
  string m;
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
  return is >> in.x >> in.y >> in.m;
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

using pos = pair<int, int>;

int distance(pos a, pos b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

void solve(input const& in) {
  pos my = make_pair(0, 0);
  pos pp = make_pair(in.x, in.y);
  int steps = 0;
  for (char c: in.m) {
    if (distance(pp, my) <= steps) {
      cout << steps;
      return;
    }
    ++steps;
    if (c == 'N') { ++pp.second; continue; }
    if (c == 'S') { --pp.second; continue; }
    if (c == 'E') { ++pp.first;  continue; }
    if (c == 'W') { --pp.first;  continue; }
  }
  if (distance(pp, my) <= steps) {
    cout << steps;
    return;
  }

  cout << "IMPOSSIBLE"; 
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
