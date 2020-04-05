// Parenting Partnering Returns
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/000000000020bdf9
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

using interval = pair<int, int>;

struct input {
  int n;
  vector<pair<int, int>> a;
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
  is >> in.n;
  in.a.resize(in.n);
  return is >> in.a;
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

struct activity {
  interval a;
  size_t i;

  activity(interval a, size_t i) : a(a), i(i) {}

  activity(activity const& a) = default;
  activity(activity && o) = default;
  activity& operator=(activity const& o) = default;
  activity& operator=(activity && o) = default;

  bool operator<(activity const& o) const {
    return this->a < o.a;
  }
};

// Algorithm

bool intersects(interval const& a, interval const& b) {
  if (a.second <= b.first) return false;
  if (b.second <= a.first) return false;
  return true;
}

void solve(input const& in) {
  vector<activity> a;
  for (size_t i = 0; i <in.a.size(); ++i) {
    a.emplace_back(activity(in.a[i], i));
  }
  sort(begin(a), end(a));
  string assignment(in.a.size(), ' ');
  interval c = make_pair(-1, -1);
  interval j = make_pair(-1, -1);

  for (auto const& i: a) {
    if (!intersects(i.a, c)) {
      c = i.a;
      assignment[i.i] = 'C';
    } else if (!intersects(i.a, j)) {
      j = i.a;
      assignment[i.i] = 'J';
    } else {
      cout << "IMPOSSIBLE";
      return;
    }
  }

  cout << assignment;
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
