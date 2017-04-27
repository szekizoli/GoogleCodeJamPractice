// 2016  Round 1B Problem B
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<iostream>
#include<limits>
#include<utility>
#include<vector>

using namespace std;

// I/O

enum class larger { None, C, J };

struct input {
  string c, j;
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
  is >> in.c >> in.j;
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

void add(long& i, int j) {
  if (j < 0) cout << i << " error" << endl;
  i = i*10 + j;
}

inline int value(char c) { return c - '0'; }

inline bool empty(char c) { return c == '?'; }

int smallest(char x) {
  return empty(x) ? 0 : value(x);
}

int largest(char x) {
  return empty(x) ? 9 : value(x);
}

int equal_min(char a, char b) {
  return max(smallest(a), smallest(b));
}

pair<int, int> larger(char a, char b) {
  if (empty(a)) {
    int s = smallest(b);
    return make_pair(s+1, s);
  } else {
    return empty(b) ? make_pair(value(a), value(a-1)) : make_pair(value(a), value(b));
  }
}

template<typename I>
size_t find_mismatch(I f0, I l0, I f1, I l1) {
  size_t result = 0;
  while(f0 != l0 && (*f0 == *f1 || empty(*f0) || empty(*f1))) {
    ++result;
    ++f0; ++f1;
  }
  return result;
}

typedef pair<long, long> result_t;

template<typename I>
pair<long, long> generate_nums(I f0, I l0, I f1, I l1, size_t pos) {
  // Precondition: first is intended to be larger.
  // Precondition: pos < l0-f0 && l0-f0 == l1-f1
  long n0 = 0, n1 = 0;

  // equal part
  while (pos > 0) {
    int val = equal_min(*f0, *f1);
    add(n0, val);
    add(n1, val);
    ++f0; ++f1; --pos;
  }
  if (f0 == l0) return make_pair(n0, n1);
  // first larger position
  if (*f1 == '9' || *f0 == '0') return make_pair(numeric_limits<long>::max(), 0);
  pair<int, int> val = larger(*f0, *f1);
  add(n0, val.first);
  add(n1, val.second);
  ++f0; ++f1;
  // rest
  while (f0 != l0) {
    add(n0, smallest(*f0));
    add(n1, largest(*f1));
    ++f0; ++f1;
  }
  return make_pair(n0, n1);
}

long diff(result_t const& a) { return abs(a.first - a.second); }

bool operator<(pair<long, long> const& a, pair<long, long> const& b) {
  if (diff(a) != diff(b)) return diff(a) < diff(b);
  return a.first == b.first ? a.second < b.second : a.first < b.first;
}

void solve(input const& in) {
  size_t pos = find_mismatch(begin(in.c), end(in.c), begin(in.j), end(in.j));
  result_t min = make_pair(numeric_limits<long>::max(), 0);
  for (size_t i = 0; i <= pos; ++i) {
    result_t r0 = generate_nums(begin(in.c), end(in.c), begin(in.j), end(in.j), i);
    if (r0 < min) min = r0;
    result_t r1 = generate_nums(begin(in.j), end(in.j), begin(in.c), end(in.c), i);
    swap(r1.first, r1.second);
    if (r1 < min) min = r1;
  }

  cout << setfill('0') << setw(in.c.size()) << min.first << " ";
  cout << setfill('0') << setw(in.j.size()) << min.second;
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    //cout << in.c << " " << in.j << endl;
    cout << "Case #" << t+1 << ": ";
    solve(in);
    cout << endl;
  }
  return 0;
}
