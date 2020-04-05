// ESAb ATAd
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209a9e
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
  int b;
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
  return is >> in.b;
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

using bit = int;
using probe = vector<bit>;
const bit BAD = -2;

bool matches(bit a, bit b) {
  return a == -1 || b == -1 || a == b;
}

bit flip(bit i) {
  if (i == -1) return -1;
  return (-i)+1;
}

bool negative(int i) {
  return i < 0;
}

bit bplus(bit a, bit b) {
  if (negative(a) || negative(b)) return -1;
  return (a + b) % 2;
}

struct bit_s {
  int value;
  bit_s(int b) : value(b) {}
};

struct bits {
  vector<bit> b;
  bits(size_t i): b(vector<bit>(i, -1)) {}
  bits(vector<bit> && v): b(v) {}

  bits(bits const& o) = default;
  bits(bits && o) = default;
  bits& operator=(bits const& o) = default;
  bits& operator=(bits && o) = default;

  bool operator==(bits const& o) const {
    if (b.size() != o.b.size()) {
      cerr << "Bits size mismatch" << endl;
      exit(1);
    }

    return std::mismatch(begin(b), end(b), begin(o.b), matches).first == end(b);
  }

  bits reverse() const {
    return bits(vector<int>(rbegin(b), rend(b)));
  }

  bits complement() const {
    vector<int> v(b);
    std::transform(begin(v), end(v), begin(v), flip);
    return bits(std::move(v));
  }

  void merge(bits const& o) {
    if (b.size() != o.b.size()) {
      this->set_bad();
      return;
    }
    for (size_t i = 0; i < o.b.size(); ++i) {
      if (!matches(b[i], o.b[i])) { this->set_bad(); return; }
      if (negative(b[i])) { b[i] = o.b[i]; }
    }
  }

  bits merge(bits const& o) const {
    if (b.size() != o.b.size()) {
      bits r(1); r.set_bad();
      return r;
    }
    bits r(*this);
    for (size_t i = 0; i < o.b.size(); ++i) {
      if (!matches(b[i], o.b[i])) { r.set_bad(); return r; }
      if (r[i] < 0) { r[i] = o.b[i]; }
    }
    return r;
  }

        int& operator[](size_t i)       { return b[i]; }
  const int& operator[](size_t i) const { return b[i]; }

  void   set_bad()       { b[0] = BAD; }
  bool   is_bad()  const { return b[0] == BAD; }
  bool   is_full() const { return !any_of(begin(b), end(b), negative); }
  size_t size()    const { return b.size(); }

  bool is_set(size_t i) const { return !negative(b[i]); }
  bit  mod(size_t i)    const { return bplus(b[i], b[size() - 1 - i]); }
};

ostream& operator<<(ostream& os, bits const& b) {
  for (int i : b.b) {
    if (i < 0) os << "_";
    else       os << i;
  }
  return os;
}

const int testSet1 =  10;
const int testSet2 =  20;
const int testSet3 = 100;

template<typename T>
void msg(string const& s, T const& b) {
  //cerr << s << endl << b << endl;
}

bool judgement(bits const& solution) {
  msg("final", solution);
  cout << solution << endl;
  char r;
  cin >> r;
  return r == 'Y';
}

bits read(size_t size, vector<int> vals) {
  bits b(size);
  for (int v : vals) {
    cout << v << endl;
    char bit;
    cin >> bit;
    if (bit == 'N') {
      b.set_bad();
      break;
    }
    b[v-1] = bit - '0';
  }
  return b;
}

bool solve1(input const& in) {;
  bits b = read(10, probe {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  if (b.is_bad()) {
    msg("Invalid output produced", b);
    return false;
  }
  return judgement(b);
}

vector<bits> add_all(bits const& b) {
  vector<bits> res;
  res.push_back(b);
  bits rev = b.reverse();
  res.push_back(rev);
  res.push_back(b.complement());
  res.push_back(rev.complement());
  return res;
}

struct filter{
  bits b;
  filter(bits o) : b(o) {}
  bool operator()(bits const& o) {
    return !(o == b);
  }
};

bits find(size_t index, bits const& b0, bits const& b1) {
  vector<bits> v = add_all(b0);
  v.erase(remove_if(begin(v), end(v), filter {b1}), end(v));
  if (v.size() != 1) {
    msg("find error " + to_string(index), v);
  }
  return v.front();
}

bool mod(bits & acc, bits const& read) {
  if (acc.size() * 2 != read.size()) {
    msg("Invalid size" + to_string(acc.size()) + "*2 != " + to_string(read.size()), acc);
    return false;
  }
  const size_t s = read.size();
  for (size_t i = 0; i < acc.size(); ++i) {
    if (read.is_set(i) && read.is_set(s-1-i)) {
      acc[i] = read.mod(i);
    }
  }
  return true;
}

bool solve2(input const& in) {
  bits c(10);
  bits b1 = read(20, probe {1, 2, 3, 4, 5, 16, 17, 18, 19, 20} );
  msg("1", b1);
  if (b1.is_bad()) { return false; }
  mod(c, b1);
  bits b2 = read(20, probe {6, 7, 8, 9, 10, 11, 12, 13, 14, 15} );
  msg("2", b2);
  if (b2.is_bad()) { return false; }
  mod(c, b2);
  msg("c", c);
  bits b3 = read(20, probe {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} );
  msg("3", b3);
  if (b3.is_bad()) { return false; }
  for (size_t i = 0; i < 10; ++i) {
    b3[i+10] = (b3[9-i] + c[9-i]) % 2;
  }
  return judgement(b3);
}

probe create_probe(size_t i) {
  probe p;
  for (size_t j = i*5; j < i*5 + 5; ++j) {
     p.push_back(j + 1); p.push_back(100 - j);
  }
  msg("probe", p);
  return p;
}

pair<int, int> select2(size_t i, size_t step, bits const& b) {
  bits c = b.reverse();
  auto p = make_pair(0, 0);
  msg("b " + to_string(i), b);
  msg("c " + to_string(i), c);
  for (size_t j = i * step; j < i * step + step; ++j) {
    if (!c.is_set(j)) msg("c not set " + to_string(i), c);
    if (!b.is_set(j)) msg("b not set " + to_string(i), b);
    if (b[j] != c[j] && p.second == 0) p.second = j + 1;
    if (b[j] == c[j] && p.first  == 0) p.first = j + 1;
  }
  if (p.first  == 0) p.first  = p.second;
  if (p.second == 0) p.second = p.first;
  return p;
}

void push(vector<int> & v, pair<int, int> p) {
  v.push_back(p.first);
  v.push_back(p.second);
}

bool solve3(const size_t size) {
  vector<bits> probes;
  for (size_t i = 0; i < 10; ++i){
    bits b = read(size, create_probe(i));
    msg("b" + to_string(i+1), b);
    if (b.is_bad()) { return false; }
    probes.push_back(b);
  }
  probe p1;
  for (size_t i = 0; i < 5; ++i) {
    auto pp = select2(i, 5, probes[i]);
    p1.push_back(pp.first);
    p1.push_back(pp.second);
  }
  msg("probing 1", p1);
  bits b1 = read(size, p1);
  for (size_t i = 0; i < 5; ++i) {
    bits f = find(i, probes[i], b1);
    b1.merge(f);
    if (b1.is_bad()) {
      msg("failed to merge 1st", b1);
      break;
    }
  }
  probe p2;
  for (size_t i = 5; i < 10; ++i) {
    auto pp = select2(i, 5, probes[i]);
    p2.push_back(pp.first);
    p2.push_back(pp.second);
  }
  msg("probing 2", p2);
  bits b2 = read(size, p2);
  for (size_t i = 5; i < 10; ++i) {
    bits f = find(i, probes[i], b2);
    b2.merge(f);
    if (b2.is_bad()) {
      msg("failed to merge 2st", b2);
      break;
    }
  }
  probe p3;
  push(p3, select2(0, 25, b1));
  push(p3, select2(1, 25, b2));
  msg("probing 3", p3);
  bits b3 = read(size, p3);
  bits f1 = find(11, b1, b3);
  b3.merge(f1);
  if (b3.is_bad()) { msg("failed to merge 3rd", b3); }
  bits f2 = find(12, b2, b3);
  b3.merge(f2);
  if (b3.is_bad()) { msg("failed to merge 4th", b3); }
  return judgement(b3);
}

bool solve(input const& in) {
  if (in.b == testSet1) {
    return solve1(in);
  }
  if (in.b == testSet2) {
    return solve2(in);
  }
  if (in.b == testSet3) {
    return solve3(in.b);
  }
  cout << "Unexpected bit array size" << endl;
  bits b(1); b.set_bad();
  return judgement(b);
}

int main() {
  int T = 0; cin >> T;
  input in; cin >> in;
  msg("input size", in.b);
  for (int t = 0; t < T; ++t) {
    bool success = solve(in);
    if (!success) {
      msg("Test failed", t+1);
      return 1;
    } else {
      msg("Test succeed", t+1);
    }
  }
  return 0;
}
