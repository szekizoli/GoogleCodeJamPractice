// Indicium
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209aa0
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
  int N, K;
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
  return is >> in.N >> in.K;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1>& x) {
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i];
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << endl;
  return os;
}

// Algorithm

vector<int> get_trace(input const& in) {
  vector<int> trace(in.N, in.K / in.N);
  int mod = in.K % in.N;
  if (mod == 0) { 
    return trace; 
  }
  if (mod == 1) {
      trace[0] += 2; --trace[1]; --trace[2];
  }
  return trace;
}

vector<vector<int>> get_matric(input const& in) {

  
}

void solve(input const& in) {
  if (in.K == in.N + 1 || in.K == in.N * in.N -1) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  int mod = in.K % in.N;
  if (in.K <= 3 && mod != 0) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  if (mod == 0) {
    
  }
  cout << "POSSIBLE" << endl;
  vector<vector<int>> m(in.N, vector<int>(in.N, 0));
  vector<int> trace = get_trace(in);
  for (int i = 0; i < in.N; ++i) m[i][i] = trace[i];
  cout << m; 
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": ";
    solve(in);
  }
  return 0;
}
