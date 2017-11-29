#include <algorithm>
#include <iostream>

using namespace std;

using num = long long;

num solve(num r, num t) {
  num count = 0;
  num current_ring = 2*r+4*count+1;
  while (current_ring <= t) {
    t -= current_ring;
    current_ring += 4;
    ++count;
  }
  return count;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    num r, t; cin >> r >> t;
    cout << "Case #" << i+1 << ": " << solve(r, t) << endl;
  }
  return 0;
}
