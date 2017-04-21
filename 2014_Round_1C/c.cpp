#include<cmath>
#include<iostream>
#include<utility>
#include<vector>

using namespace std;

typedef pair<int, int> pair_t;

ostream& operator<<(ostream& o, pair_t l) {
  cout << l.first << " " << l.second;
  return o;
}

pair_t find_closest_limit(int k) {
  int x = static_cast<int>(sqrt(k+4) - 2);
  return pair_t(x, x);
}

int value(pair_t l) {
  return (l.first * l.second) + 2*(l.first + l.second);
}

void increase(pair_t & l, pair_t const& limit) {
  if (l.first < l.second && l.first < limit.first) ++l.first;
  else                                             ++l.second;
}

int stones(pair_t l) {
  return 2*(l.first + l.second);
}

int solve(int n, int m, int k) {
  if (min(n, m) < 3) return k;
  pair_t limit(min(n - 2, m - 2), max(n - 2, m - 2));
  pair_t current = find_closest_limit(k);
  if (limit < current) current.first = limit.first;
  while (value(current) <= k - 2 && current < limit) increase(current, limit);
  int extra = k - value(current);
  if (current.first >= 2 && extra <= -2) return stones(current) - 1; // cut off edge
  return stones(current) + max(0, extra);
}

int main() {
  int T; cin >> T;
  for(int t = 0; t < T; ++ t) {
    int n, m, k;
    cin >> n >> m >> k;
    cout << "Case #" << t+1 << ": " << solve(n, m, k) << endl;
  }
  return 0;
}
