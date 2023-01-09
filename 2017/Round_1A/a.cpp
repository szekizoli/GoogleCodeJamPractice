#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(vector<vector<char>> const& x) {
  for (const auto& v : x) {
    for (char c : v) {
      cout << c;
    }
    cout << endl;
  }
}

bool pred(char c) {
  return c == '?';
}

void copy(vector<vector<char>>& x, size_t from, size_t to) {
  for (size_t i = 0; i < x[from].size(); ++i)
    x[to][i] = x[from][i];
}

int find_nonempty_up(vector<vector<char>>& x, int row) {
  while (--row >= 0) {
    if (x[row][0] != '?') return row;
  }
  return -1;
}

int find_nonempty_down(vector<vector<char>>& x, int row) {
  while (++row < x.size()) {
    if (x[row][0] != '?') return row;
  }
  return -1;
}

void solve () {
  vector<int> empty;
  int R, C;
  cin >> R >> C;
  string s;
  char filling;
  vector<vector<char>> x(R, vector<char>(C, '?'));
  for (int r = 0; r < R; ++r) {
    cin >> s;
    auto pos = find_if_not(s.begin(), s.end(), pred);
    if (pos == s.end()) {
      empty.push_back(r);
      continue;
    }
    int n = pos - s.begin();
    filling = *pos;
    fill(x[r].begin(), x[r].begin()+n, filling);
    while (pos != s.end()) {
      if (*pos != filling && *pos != '?') filling = *pos;
      x[r][n] = filling;
      ++n;
      ++pos;
    }
  }
  // fill empty lines
  for (int e : empty) {
    if (x[e][0] != '?') continue;
    int r = find_nonempty_up(x, e);
    if (r != -1) {
      for (; r < e; --e) copy(x, r, e);
      continue;
    }
    r = find_nonempty_down(x, e);
    if (r != -1) {
      for (; e < r; e++) copy(x, r, e);
    }
  }
  print(x);
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    cout << "Case #" << t+1 << ": " << endl;
    solve();  
  }
  return 0;
}

