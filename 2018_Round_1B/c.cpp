// 2018 Round 1B Problem C
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

void solve(input const& in) {
  
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
