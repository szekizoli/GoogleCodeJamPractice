#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef double t_t;
typedef unsigned d_t; // distance type
typedef double s_t; // speed type

t_t when(d_t d,  s_t s) {
  return double(d) / s;
}

s_t max_speed(d_t d, t_t t) {
  return d/t;
}

s_t solve() {
  d_t D; int N;
  cin >> D >> N;
  d_t K; s_t S;
  vector<t_t> times;
  times.reserve(N);
  for (int n = 0; n < N; ++n) {
    cin >> K >> S;
    times.push_back(when(D-K, S));
  }
  return max_speed(D, *max_element(begin(times), end(times)));
}

int main () {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    cout.precision(6);
    cout << "Case #" << t+1 << ": " << fixed << solve() << endl;
  }
  return 0;
}
