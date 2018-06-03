// 2018 Round 2 Problem B
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
  int R, B;
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
  return is >> in.R >> in.B;
}

ostream& operator<<(ostream& os, pair<int, int> const& x) {
  os << x.first << " " << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

void solve(input const& in) {
  int m0 = std::min(in.R, in.B);
  int m1 = std::max(in.R, in.B);
  vector<pair<int, int>> sums;
  sums.push_back(make_pair(0, 0));
  for (int i = 1; i < 50; ++i) {
    sums_push_back(make_pair((3*i*i+i)/2, 2*i+1)); 
  }
  int sum = 0;
  int index = 0;
  for (int i = 1; i < sums.size() && sum + sums[i].first <= m0; ++i) {
    index = i;
  }
  int count = 0;
  for (int i = 1; i <= index; ++i) count += sums[i].second;
  m1 -=  
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

