// 2020 Round 1B Problem C
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
  int R, S;
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
  return is >> in.R >> in.S;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1> const& x) {
  os << x.first << " " << x.second << endl;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(auto const& t : x) os << t << " ";
  return os;
}

// Algorithm
void add(vector<pair<int, int>> & v, int x, int y) {
  v.push_back(make_pair(x, y));
}
void solve(input const& in) {
  vector<pair<int, int>> v;
  vector<int> deck;
  for (int s = 1; s <= in.S; ++s) {
    for (int r = 1; r <= in.R; ++r) {
      deck.push_back(r*10);
    }
  }
  if (in.S == 2) {
    for (int r = in.R - 1; r > 0; --r) {
      v.push_back(make_pair(r+1, r));
    }
  } else if (in.R == 2) {
    for (int s = 0; s < in.S - 1; ++s) {
      v.push_back(make_pair(in.S+in.S - s - 2, 1));
    }
  } else {
    int a = in.R * (in.S - 1);
    int b = in.R - 1;
    int c = 0;
    while (b > 0 && a >= in.S) {
      add(v, a, b);
      --a;
      ++c;
      if (c == (in.S - 1)) {
        c = 0;
        --b;
      }
    }
  }
  cout << v.size() << " > " << (((in.R * in.S - in.R)+1)/2) <<  endl;
  cout << deck << endl;
  for (auto const& p : v) {
    cout << p;
    rotate(begin(deck), begin(deck) + p.first, begin(deck) + p.first + p.second);
    cout << deck << endl;
  }
  size_t idx = 0;
  for (int r = 1; r <= in.R; ++r) {
    for (int s = 1; s <= in.S; ++s) {
      int min = r*10;
      int max = min + 10;
      //cout << idx << " min=" << min << endl;
      if (deck[idx] != min || deck[idx] > max) {
        cout << "ERROR!: " << deck[idx] << " should be between " << min << " and " << max << endl;
      }
      ++idx;
    }
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
