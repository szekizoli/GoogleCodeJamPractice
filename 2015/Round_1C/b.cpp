// 2015 Round 1C Problem B
#include<algorithm>
#include<cmath>
#include<iostream>
#include<limits>
#include<utility>
#include<string>
#include<vector>

using namespace std;

// I/O

struct input {
  int K, L, S;
  string kb, word;
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
  is >> i.K >> i.L >> i.S >> i.kb >> i.word;
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

template<typename I>
bool matches(I f0, I f1, I l) {
  while (f1 != l && *f0 == *f1) { ++f0; ++f1; }
  return f1 == l;
}

size_t max_overlap(string const& word) {
  for (size_t i = 1; i < word.size(); ++i) {
    if (matches(begin(word), begin(word) + i, end(word)))
      return word.size() - i;
  }
  return 0;
} 

inline size_t to_index(char c) { return c - 'A'; }

double probability(input const& in) {
  int count[26];
  fill(count, count+26, 0);
  for (char c : in.kb) ++count[to_index(c)];
  double p = 1.0;
  for (char c : in.word) p *= count[to_index(c)] / static_cast<double>(in.K);
  return p;
}

void solve(input const& in) {
  double p = probability(in);
  double result = 0.0;
  if (0 < p) {
    size_t O = max_overlap(in.word);
    double max_copies = (in.S-in.L)/(in.L-O) + 1;
    double expected_copies = p * (in.S - in.L + 1);
    result = max_copies - expected_copies;
  }
  cout.precision(6);
  cout << fixed << result;
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
