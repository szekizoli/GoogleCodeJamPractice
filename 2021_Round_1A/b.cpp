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

using val_t = long long;
using prime_count = pair<val_t, val_t>;
struct input {
	int m;
	vector<prime_count> v;
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
	is >> in.m;
	in.v.resize(in.m);
  return is >> in.v;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, const pair<T0, T1>& x) {
  os << x.first << " " << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

const val_t MAX_PRIME = 499;
const val_t MAX = MAX_PRIME * 1000000000000000;
const int MAX_ITEM = 60;
const val_t MAX_SUM_2 = MAX_ITEM * MAX_PRIME;

pair<val_t, bool> prime_factor(val_t num, input const& in) {
  val_t sum = 0;
  for (const prime_count pf : in.v) {
    val_t count = pf.second;
    while (num > 1 && count > 0 && num % pf.first == 0) {
      sum += pf.first;
      num = num / pf.first;
      --count;
    }
    if (num == 1) break;
  }
  return {sum, num == 1};
}

val_t pair_product(val_t const& a, prime_count const& b) {
  return a + b.first * b.second;
}

void solve(input const& in) {
  val_t sum = std::accumulate(begin(in.v), end(in.v), val_t{0}, pair_product);
  val_t min_v = std::max(val_t{1}, sum - MAX_SUM_2 - 1);
  for (val_t i = sum; i > min_v; --i) {
      pair<val_t, bool> pf_result = prime_factor(i, in);
      if (pf_result.second && sum == i + pf_result.first)  {
        cout << i; return;
      }
  }
  cout << "0"; return;
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
