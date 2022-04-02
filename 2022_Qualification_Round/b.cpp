#include<algorithm>
#include<array>
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

using num_t = unsigned long long;

struct input {
  array<array<num_t, 4>, 3> a = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
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
  return is >> in.a;
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

num_t min(num_t a, num_t b, num_t c) {
  return std::min(std::min(a, b), c);
}

void solve(input const& in) {
  num_t min_c = min(in.a[0][0], in.a[1][0], in.a[2][0]);
  num_t min_m = min(in.a[0][1], in.a[1][1], in.a[2][1]);
  num_t min_y = min(in.a[0][2], in.a[1][2], in.a[2][2]);
  num_t min_k = min(in.a[0][3], in.a[1][3], in.a[2][3]);
  if (min_c + min_m + min_y + min_k < 1000000) {
    cout << "IMPOSSIBLE";
    return;
  }
  num_t remainder = 1000000;
  num_t c = min(min_c, remainder); remainder -= c;
  num_t m = min(min_m, remainder); remainder -= m;
  num_t y = min(min_y, remainder); remainder -= y;
  num_t k = min(min_k, remainder); remainder -= k;
  cout << c << " " << m << " " << y << " " << k;
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
