#include<iostream>
#include<vector>

using namespace std;

template<typename T>
T gcd(T a, T b) {
  while(true) {
    if (b == 0) return a;
    a = a % b;
    if (a == 0) return b;
    b = b % a;
  }
}

template<typename T>
bool is_pow_2(T x) {
  int counter = 0;
  while(0 < x) {
    if ((x & 1) == 1) ++counter;
    x >>= 1;
  }
  return counter == 1;
}

template<typename T>
void solve(T p, T q) {
  T remainder = gcd(p, q);
  p /= remainder;
  q /= remainder;
  if (!is_pow_2(q)) {
    cout << "impossible";
    return;
  }
  while (0 < p/2) {
    p /= 2;
    q /= 2;
  }
  int counter = 0;
  while (0 < q) { ++counter; q >>= 1; }
  cout << counter-1;
}

int main() {
  int T; cin >> T;
  unsigned long long P, Q;
  char c;
  for (int t = 0; t < T; ++t) {
    cout << "Case #" << t+1 << ": ";
    cin >> P >> c >> Q;
    solve(P, Q);
    cout << endl;
  }
  return 0;
}
