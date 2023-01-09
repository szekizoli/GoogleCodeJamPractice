// 2015 Round 1B Problem B
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

typedef int N;

// brute force
// size limit R*C <= 16

bitset<17> grid;

bool next(N r, N c) {
  for (N i = 0; i < r*c; ++i) {
    if (grid[i] && !grid[i+1]) {
      grid.flip(i);
      grid.flip(i+1);
      grid[i-1] = grid[i-1] ^ grid[0];
      grid[0] = grid[i-1] ^ grid[0];
      grid[i-1] = grid[i-1] ^ grid[0];
      if (i != 0) swap(grid[i-1], grid[0]);
      return true;
    }
  }
  return false;
}

bool get(N R, N r, N c) {
  return grid[r*R + c];
}

N value(N r, N c) {
  N result = 0;
  // per coloumn
  for(N c0 = 0; c0 < c; ++c0)
    for(N r0 = 0; r0 < r - 1; ++r0) {
      if (get(r, r0, c0) && get(r, r0+1, c0)) ++result;
    }
  // per row
  for(N r0 = 0; r0 < r; ++r0)
    for(N c0 = 0; c0 < c - 1; ++c0) {
      if (get(r, r0, c0) && get(r, r0, c0+1)) ++result;
    }
  return result;
}

void print(N r, N c) {
  for(N c0 = 0; c0 < c; ++c0) {
    for(N r0 = 0; r0 < r; ++r0) {
      cout << (get(r, r0, c0) ? '*' : '_' );
    }
    cout << endl;
  }
  cout << endl;
}

N solve(N r, N c, N n) {
  grid.set();
  if (c < r) swap(c, r);
  while(n < r*c) grid[n++] = false;
  N result = 100; // a huge number
  cout << endl;
  do {
    N val = value(r, c);
    if (val < result) result = val;
    cout << grid << endl;
  }  while(next(r, c));
  return result;
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    N r, c, n;
    cin >> r >> c >> n;    
    cout << "Case #" << t+1 << ": " << solve(r, c, n) << endl;
  }
  return 0;
}
