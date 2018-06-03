// 2018 Round 2 Problem A Falling Balls
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

using Num = int;

struct input {
  vector<Num> B;
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
  size_t N; is >> N;
  in.B.resize(N);
  return is >> in.B;
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

void solve(input const& in) {
  vector<Num> const& B = in.B;
  if (B.front() * B.back() == 0) {
    cout << "IMPOSSIBLE"; return;
  }
  vector<Num> endPos(B.size(), 0);
  // determine the end position of each row
  Num currentEnd = 0;
  for (size_t i = 0; i < B.size(); ++i) {
    for (size_t j = currentEnd; j < currentEnd + B[i] && j < endPos.size(); ++j) {
      endPos[j] = i;
    }
    currentEnd = currentEnd + B[i];
  }
  Num maxLength = 0;
  for (int i = 0; i < endPos.size(); ++i) maxLength = std::max(maxLength, std::abs(i - endPos[i]));
  cout << maxLength + 1<< "\n";
  cout << B << endl;
  cout << endPos << endl;
  vector<Num> rampCounter(B.size(), 0);
  Num ballCounter = 0;
  for (Num i = 0; i < endPos.length(); ++i) {
    rampCounter[i] = std::max
  }
  for (Num i = 0; i < maxLength; ++i) { 
    for (size_t i = 0; i < endPos.size(); ++i) {
      if (endPos[i] == i)    cout << ".";
      else if(endPos[i] < i) cout << "/";
      else                   cout << "\\";
    }
    cout << "\n";
  }
  for (Num i = 0; i < endPos.size(); ++i) cout << ".";
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
