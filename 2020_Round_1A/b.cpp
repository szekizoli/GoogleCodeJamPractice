// 2020 Round 1A Problem B
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
  long N;
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
  return is >> in.N;
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

vector<long> next(long n_r, vector<long> const& v) {
  if (v.size() == 1) return vector<long> {1, 1};
  vector<long> r;
  r.push_back(1);
  for (size_t i = 0; i < v.size() - 1; ++i) {
    r.push_back(v[i] + v[i+1]);
  }
  if (n_r % 2 == 0) {
    r.push_back(v.back() + v.back());
  }
  return r;
}

size_t idx(vector<long> const& v, size_t b) {
  return (v.size() - b >= 1) ? v.size() - b - 1 : 0;
}

long last_2(vector<long> const& v) {
  return v.back() + v[v.size()-2];
}

void solve_large(input const& in) {
  long sum = 0;
  long n_r = 1;
  long n_s = 1;
  int dir = 0;
  cout << endl;
  vector<vector<long>> p;
  p.emplace_back(vector<long>{1});
  while (in.N > sum + n_s) {
    vector<long>& r = p.back();
    cout << r << endl;
    cout << n_r << " " << r.size() << " (" << r.back() << ")" << endl;
    sum += r.back();
    n_s *= 2;
    ++n_r;
    p.emplace_back(next(n_r, p.back()));
  }
  vector<long>& r = p.back();
  cout << r << endl;
  cout << sum << endl;
  --n_r;
  for (; n_r >= 0 && in.N >= sum + p[n_r][p[n_r].size()-2]; --n_r) {
    cout << n_r << " " << p[n_r].size()-1 << endl;
    sum += p[n_r][p[n_r].size()-2]; 
  }
  /*for (size_t i = r.size() - 1 ; i > 0 && in.N > sum + r[i-1]; --i) {
    cout << n_r << " " << i-1 << endl;
    sum += r[i-1];
    cout << sum << endl;
  }*/
  cout << sum << endl;
  /*while (sum < in.N) {
    if (dir == 0) {
      cout << n_r << " " << "1" << endl;
    } else {
      cout << n_r << " " << n_r << endl;
    }
    ++sum;
    ++n_r;
  }*/
}

void solve(input const& in) {
  cout << endl;
  cout << "1 1" << endl;
  if (in.N == 1) { return; }
  if (in.N > 1000) { solve_large(in); return; }
  long sum = 1;
  long c_r = 2;
  while (sum + 2*c_r + 1 <= in.N) {
    sum += 2*c_r + 1;
    cout << c_r << " 1" << endl;
    cout << c_r << " 2" << endl;
    ++c_r;
    cout << c_r << " 2" << endl;
    cout << c_r << " 1" << endl;
    ++c_r; 
  }
  while (sum < in.N) {
    cout << c_r << " 1" << endl;
    ++c_r; ++sum;
  }
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
