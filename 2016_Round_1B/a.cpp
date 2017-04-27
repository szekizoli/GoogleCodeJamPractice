// 2016 Round 1B Problem A
#include<algorithm>
#include<array>
#include<cmath>
#include<iostream>
#include<iterator>
#include<limits>
#include<map>
#include<string>
#include<utility>
#include<vector>

using namespace std;

// I/O

struct input {
  string s;
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
  is >> in.s;
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

// Data structure

map<char, int> count_chars(const string& s) {
  map<char, int> result;
  for (char c : s) ++result[c];
  return result;
}

struct counted_string {
  map<char, int> count;
  counted_string(const string& s) : count(count_chars(s)) {}
  counted_string(const counted_string& cs) : count(cs.count) {}
  counted_string& operator=(const counted_string& cs) = default;
  void operator-=(counted_string const& x) {
    for (const auto &p : x.count) count[p.first] -= p.second;
  }
};

int operator/(counted_string const& x, counted_string const& y) {
  int result = numeric_limits<int>::max();
  for (const auto &p : y.count) {
    auto i = x.count.find(p.first);
    if (i == x.count.end()) return 0;
    result = min(result, i->second / p.second);
  }

  return result;
}

array<pair<string, int>, 10> nums = { make_pair("ZERO", 0), {"TWO", 2}, {"SIX", 6}, {"SEVEN", 7}, {"FIVE", 5},
				               {"FOUR", 4}, {"THREE", 3}, {"ONE", 1}, {"EIGHT", 8}, {"NINE", 9}};

// Algorithm

array<unsigned, 26> char_count;

inline size_t index(char c) { return c - 'A'; }

int count(counted_string& s, const string& n) {
  counted_string x(n);
  int result = s / x;
  for (int i = 0; i < result; ++i) s -= x;
  return result;
}

void solve(input const& in) {
  counted_string s(in.s);
  vector<int> result;
  result.reserve(in.s.size()/3);
  for (auto p : nums) {
    unsigned c = count(s, p.first);
    while (0 < c--) result.push_back(p.second);
  }
  sort(begin(result), end(result));
  copy(begin(result), end(result), ostream_iterator<int>(cout, ""));
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
