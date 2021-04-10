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
    int x, y;
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
  return is >> in.x >> in.y >> in.s;
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

int get_cost_negative(int x, int y, string s) {
    auto first_c = std::find(begin(s), end(s), 'C');
    auto first_j = std::find(begin(s), end(s), 'J');
    auto first = std::min(first_c, first_j);
    int cost = 0;
    auto prev = first;
    while (++first != end(s)) {
        if (*first == '?')        { *first = *prev;}
        else if (*prev == *first) { }
        else if (*prev == 'C')    { cost += x; }
        else                      { cost += y; }
        prev = first;
    }
    
    cout << s << endl;
    
    return cost;
}

int get_cost(int x, int y, string s) {
    auto first_c = std::find(begin(s), end(s), 'C');
    auto first_j = std::find(begin(s), end(s), 'J');
    auto first = std::min(first_c, first_j);
    int cost = 0;
    auto prev = first;
    while (++first != end(s)) {
        if (*first == '?')        { *first = *prev;}
        else if (*prev == *first) { }
        else if (*prev == 'C')    { cost += x; }
        else                      { cost += y; }
        prev = first;
    }

    return cost;
}

void solve(input const& in) {
  cout << get_cost(in.x, in.y, in.s);
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
