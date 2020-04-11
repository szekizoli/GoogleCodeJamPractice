// 2020 Round 1A Problem A
// Pattern Matching
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
  int N;
  vector<string> P;
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
  is >> in.N;
  in.P.resize(in.N);
  return is >> in.P;
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

bool suffix_matches(string const &a, string const& b) {
  auto it_p = mismatch(rbegin(a), rend(a), rbegin(b), rend(b));
  return it_p.first == rend(a) || it_p.second == rend(b);
}

void solve(input const& in) {
  string max_prefix = "";
  string max_suffix = ""; // reversed suffix
  // suffix
  for (auto const& s : in.P) {
    auto it = find(rbegin(s), rend(s), '*');
    if (it == rend(s)) { cerr << "Invalid input: " << s << endl; return; }

    auto it_p = mismatch(rbegin(s), it, begin(max_suffix), end(max_suffix));
    if (it_p.first != it && it_p.second != end(max_suffix)) {
      cout << "*"; return;
    }

    if (distance(rbegin(s), it) > max_suffix.size()) {
      max_suffix = string(rbegin(s), it);
    }
  }
  // prefix
  for (auto const& s : in.P) {
    auto it = find(begin(s), end(s), '*');
    if (it == end(s)) { cerr << "Invalid input: " << s << endl; return; }

    auto it_p = mismatch(begin(s), it, begin(max_prefix), end(max_prefix));
    if (it_p.first != it && it_p.second != end(max_prefix)) {
      cout << "*"; return;
    }

    if (distance(begin(s), it) > max_prefix.size()) {
      max_prefix = string(begin(s), it);
    }
  }

  cout << max_prefix << string(rbegin(max_suffix), rend(max_suffix));
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
