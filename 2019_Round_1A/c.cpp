// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e05
// 2019 Round 1C Alien Ryhme
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
  vector<string> words;
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
  in.words.resize(in.N);
  return is >> in.words;
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

struct rhyming_pair {
  string w0;
  string w1;
  string suffix;

  rhyming_pair(const string& w0, const string& w1, const string& suffix) : w0(w0), w1(w1), suffix(suffix) {}
  
  rhyming_pair(const rhyming_pair& other) = default; 
  rhyming_pair(rhyming_pair&& other) = default;
  rhyming_pair& operator=(const rhyming_pair& other) = default;
  rhyming_pair& operator=(rhyming_pair&& other) = default;

  bool operator<(const rhyming_pair& right) const {
    return this->suffix.size() < right.suffix.size();
  }

  bool operator>(const rhyming_pair& right) const {
    return this->suffix.size() > right.suffix.size();
  }
};

ostream& operator<<(ostream& os, const rhyming_pair& rp) {
  return os << rp.w0 << " " << rp.w1 << " " << rp.suffix;
}

string longest_suffix(string const& w0, string const& w1) {
  auto it0 = rbegin(w0); const auto e0 = rend(w0);
  auto it1 = rbegin(w1); const auto e1 = rend(w1);
  for (; it0 != e0 && it1 != e1 && *it0 == *it1; ++it0, ++it1) {}

  const auto diff = std::distance(rbegin(w0), it0);
  return w0.substr(w0.size() - diff);
}

vector<rhyming_pair> collect(vector<string> const& words) {
  vector<rhyming_pair> pairs;
  for (int i = 0; i < words.size(); ++i) {
    auto const& w0 = words[i];
    for (int j = i + 1; j < words.size(); ++j) { 
      auto const& w1 = words[j];
      string const& suffix = longest_suffix(w0, w1);
      if (suffix.size() > 0) {
        pairs.push_back(rhyming_pair(w0, w1, suffix));
      }
    }
  } 

  std::sort(begin(pairs), end(pairs), std::greater<>());
  return pairs;
}

int solve(input const& in) {
  vector<rhyming_pair> rp = collect(in.words);
  set<string> used_words;
  set<string> used_suffixes;
  for (auto const& p : rp) {
    if (used_words.count(p.w0) == 0 && used_words.count(p.w1) == 0 && used_suffixes.insert(p.suffix).second) {
      used_words.insert(p.w0);
      used_words.insert(p.w1);
    }
  }
  
  return used_words.size();
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": " << solve(in) << endl;
  }
  return 0;
}
