// 2020 Round 1B Problem B
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
  long A, B;
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
  return is >> in.A >> in.B;
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
const long MAX_R = 1000000000;

string guess(long x, long y) {
  cout << x << " " << y << endl;
  cerr << x << " " << y << endl;
  string rsp;
  cin >> rsp;
  cerr << rsp << endl;
  return rsp;
}

bool respond(long x, long y) {
  return guess(x, y)  == "CENTER";
}

bool solve(input const& in) {
  long low = in.A + in.A - MAX_R;
  long high = MAX_R + 1;
  string rsp;
  while (low < high) {
    long mid = (low+high)/2;
    rsp = guess(mid, 0);
    if (rsp == "WRONG") return false;
    if (rsp == "MISS") {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  long first = low - in.A;
  low = in.B + in.B - MAX_R;
  high = MAX_R;
  while (low < high) {
    long mid = (low+high)/2;
    rsp = guess(0, mid);
    if (rsp == "WRONG") return false;
    if (rsp == "MISS") {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  long second = low - in.B;
  if (respond(first, second)) return true;
  if (respond(first - 1, second)) return true;
  if (respond(first, second - 1)) return true;
  return respond(first - 1, second -1);
}

int main() {
  int T = 0; cin >> T;
  input in; cin >> in;
  for (int t = 0; t < T; ++t) {
    if (!solve(in)) return 0;
  }
  return 0;
}
