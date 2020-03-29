// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104f1a
// Go Gophers 2019 1A Problem B
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
  return is;
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

map<string, int> mods;

void prepare() {
  for (int i = 0; i < 1000001; ++i) {
    stringstream buffer;
    buffer << setw(4) << i % 16 << setw(4) << i % 3 << setw(4) << i % 5 << setw(4) << i % 7 << setw(4) << i % 11 << setw(4) << i % 13 << setw(4) << i % 17;
    mods.insert({buffer.str(), i});
  }
}

int solve() {
  vector<int> prob = {16, 3, 5, 7, 11, 13, 17};
  stringstream result;
  for (int i : prob) {
    vector<int> request(18);
    std:fill(begin(request), end(request), i);
    cout << request << endl << flush;
    cin >> request;
    if (std::count(begin(request), end(request), -1)) {
      cerr << "Invalid data sent: " << request << endl;
      return -1;
    }
    int mod = std::accumulate(begin(request), end(request), 0) % i;
    result << setw(4) << mod;
  }
  cout << mods[result.str()] << endl;
  int judgement = 0;
  cin >> judgement;
  return judgement;
}

int main() {
  prepare();
  int T = 0, N, M; cin >> T >> N >> M;
  for (int t = 0; t < T; ++t) {
    int judgement = solve();
    if (judgement != 1) {
      cerr << "Failed to solve #" << t + 1 << endl;
      return 1;
    }
  }
  return 0;
}
