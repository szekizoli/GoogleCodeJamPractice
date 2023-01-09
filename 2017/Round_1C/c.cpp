// 201  Round Problem
#include<algorithm>
#include<cmath>
#include<iostream>
#include<limits>
#include<utility>
#include<vector>

using namespace std;

// I/O

struct input {
  int N, K;
  double U;
  vector<double> P; // size = N
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
  is >> in.N >> in.K >> in.U;
  in.P.resize(in.N);
  is >> in.P;
  return is;
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
// based on contestant's solution

double solve(input & in) {
  if (in.N == 1) return in.P.front() + in.U;
  sort(begin(in.P), end(in.P));
  double sum = 0.0;
  for (size_t i = 0; i < in.P.size(); ++i) {
    sum += in.P[i];
    if (i == in.P.size() - 1 || sum + in.U <= (i+1)*in.P[i+1]) {
      double val = (sum + in.U) / (i+1);
      fill(begin(in.P), begin(in.P) + i + 1, val);
      break;
    }
  }
  
  return accumulate(begin(in.P), end(in.P), double{1}, multiplies<double>());
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": ";
    cout.precision(6);
    cout << fixed << solve(in) << endl;
  }
  return 0;
}
