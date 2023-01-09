// 2017  Round 1C Problem B
#include<algorithm>
#include<cmath>
#include<iostream>
#include<limits>
#include<utility>
#include<vector>

using namespace std;

// I/O

typedef pair<int, int> activity;

struct input {
  int Ac, Aj;
  vector<activity> vc;
  vector<activity> vj;
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
  cin >> in.Ac >> in.Aj;
  in.vc.resize(in.Ac);
  in.vj.resize(in.Aj);
  cin >> in.vc >> in.vj;
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

enum current { n, c, j};

void solve(input & in) {
  if (in.Ac + in.Aj == 1 || in.Ac == 1) {
    // change where the activity starts
    cout << "2"; return;
  }
  sort(in.vc.begin(), in.vc.end(), less<activity>());
  sort(in.vj.begin(), in.vj.end(), less<activity>());
  size_t ac = 0;
  size_t aj = 0;
  vector<activity> v;
  activity next;
  current cr = n;
  if (in.Ac > 0 && in.Aj > 0) {
    if (in.vc[ac] < in.vj[aj]) { cr = c; ++ac; next = in.vc[0];}
    else                       { cr = j; ++aj; next = in.vj[0]; }
  }
  while (ac < in.Ac && aj < in.Aj) {
    if (cr == c) {
      if (in.vc[ac] < in.vj[aj]) { next.second = in.vc[ac].second; ++ac; }
      else { v.push_back(next); next = in.vj[aj]; ++ aj; cr = j; }
    } else {
      if (in.vj[aj] < in.vc[ac]) { next.second = in.vj[aj].second; ++aj; }
      else { v.push_back(next); next = in.vc[ac]; ++ ac; cr = c; }
    }
  }

  size_t count = v.size() + in.Ac - ac + in.Aj - aj;

  if (ac < in.Ac) v.push_back(activity(in.vc[ac].first, in.vc.back().second));
  else v.push_back(activity(in.vj[aj].first, in.vj.back().second));


  //  cout << v << endl;

  for (const auto& p : v) if (p.second - p.first > 720) count += 2;
  cout << count;
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
