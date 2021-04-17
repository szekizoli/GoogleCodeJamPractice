// 2020 Round 1C Problem B
#include<algorithm>
#include<array>
#include<bitset>
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

using query = pair<int, string>;

struct input {
  int U;
  vector<query> q;
  input(size_t num = 10000) : q(vector<query>(num)) {}
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
  return is >> in.U >> in.q;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T1, T1>& x) {
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

template< std::size_t N >
ostream& operator<<(ostream& os, bitset<N> const& x) {
  for (size_t i = 0; i < N; ++i) {
    if (x[i]) os << i << " ";
  }
  return os;
}

// Algorithm

using digit = pair<char, bitset<10>>;

bitset<10> create(int min, int max) {
  bitset<10> b(0);
  while (min <= max) { b.set(min); ++min; }
  return b;
}

int len(int i) {
  int l = 0;
  while (i > 0) {
    i /= 10;
    ++l;
  }
  return l;
}

int first(int i) {
  while (i > 10) i /= 10;
  return i;
}

int count(digit const& a) { return a.second.count(); }

size_t first_set(digit const& a) {
  for (size_t i = 0; i < 10; ++i) {
    if (a.second[i]) return i;
  }
  cerr << "Invalid query" << endl;
  return 10;
}

bool lessThan(digit const& a, digit const& b) {
  int ac = count(a);
  int bc = count(b);
  if (ac == 0 && bc == 0) return true;
  return ac == bc ? first_set(a) < first_set(b) : ac < bc;
}

struct secret {
  vector<digit> v;
  void limit(char c, int min, int max) {
    auto it = find_if(begin(v), end(v), [c](const digit& d) { return d.first == c; });
    if (it == end(v)) {
      v.push_back(make_pair(c, create(min, max)));
    } else {
      auto& bs = it->second; 
      for (int i = 0; i < 10; ++i) {
        if (i < min || i > max) bs.reset(i);
      }
    }
  }

  void limit(size_t pos, int min, int max) {
    auto& bs = v[pos].second;
    for (int i = 0; i < 10; ++i) {
      if (i < min || i > max) bs.reset(i);
    }
  }

  pair<int, size_t> count_set(size_t letter) {
    pair<int, size_t> r = make_pair(0, 10);
    const auto& dig = v[letter];
    for (size_t i = 0; i < 10; ++i) {
      if (dig.second[i]) {
        ++r.first;
        if (r.first == 1) r.second = i;
      }
    }
    return r;
  }

  pair<int, size_t> count_pos(size_t pos) {
    pair<int, size_t> r = make_pair(0, 10);
    for (size_t d = 0; d < 10; ++d) {
      if (v[d].second[pos]) {
        ++r.first;
        if (r.first == 1) r.second = d;
      }
    }
    return r;
  }

  void reduce() {
    if (v.size() < 10) return;
    for (size_t p = 0; p < 10; ++p) {
      auto count = count_pos(p);
      if (count.first == 1) {
        limit(count.second, p, p); 
      }
    }

    // if i has only one position set, clear that position on other values.
    for (size_t d = 0; d < 10; ++d) {
      auto count = count_set(d);
      if (count.first == 1) {
        size_t pos = count.second;
        for (size_t j = 0; j < 10; ++j) {
          if (d == j) continue;
          v[j].second.reset(pos);
        }
      } 
    }
  }
 
  void print() {
    sort(begin(v), end(v), lessThan);
    for (auto const& p: v) {
      cout << p.first << ": " << p.second << endl;
    } 
  }
};

void solve(input const& in) {
  string d(10, ' ');
  secret s;
  for (auto const& p : in.q) {
    int f = first(p.first);
    char c = p.second[0];
    if (len(p.first) == p.second.size()) {
      s.limit(c, 1, f);
    } else {
      s.limit(c, 1, 9);
    }
    if (s.v.size() < 10) {
      for (char c : p.second) {
        s.limit(c, 0, 9);
      }
    }
    s.reduce();
  }
  //s.print();
  s.reduce();
  sort(begin(s.v), end(s.v), lessThan);
 // s.print();
  for (size_t i = 0; i < 10; ++i) 
    cout << s.v[i].first;
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
