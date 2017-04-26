// 2015 Round 1C Problem C
#include<algorithm>
#include<cmath>
#include<iostream>
#include<limits>
#include<utility>
#include<vector>

using namespace std;

// I/O

struct input {
  int C, D, V;
  vector<int> coins;
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

istream& operator>>(istream& is, input& i) {
  is >> i.C >> i.D >> i.V;
  i.coins.resize(i.D);
  is >> i.coins;
  return is;
}

template<typename T0, typename T1>
ostream& operator>>(ostream& os, pair<T0, T1>& x) {
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

typedef int N;

void solve(input const& p) {
  long N = 0;
  int add = 0;
  size_t coin_index = 0;
  
  while (N < p.V) {
    long X = N + 1;
    if (p.D == coin_index || X < p.coins[coin_index]) {
      ++add;
    } else {
      X = p.coins[coin_index++];
    }
    N += X*p.C;
  }

  cout << add;
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
