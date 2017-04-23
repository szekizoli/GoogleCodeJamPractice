// 2015 Round 1B Problem A
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long N;

N flip(N n) {
  N result = 0;
  while (0 < n) {
    result *= 10;
    result += n % 10;
    n /= 10;    
  }
  return result;
}

N length(N n) {
  int length = 0;
  while (0 < n) {
    ++length;
    n /= 10;
  }
  return length;
}

N pow10(N n) {
  N result = 1;
  while(0 < n) { result *= 10; --n; }
  return result;
}

N next_flip_point(N n, N c) {
  N l = length(c);
  N next = pow10(l) + pow10((l+1)/2)-1;
  return next;
}

void print(const char* s, N n) {
  //cout << s << " " << n << endl;
}

N find_optimal_next(N next, N n) {
  while (flip(next) > n) {
    --next;
  }
  N result = next;
  N lower_limit = pow10(length(next)-1);
  while (next > lower_limit) {
    if (flip(next) <= n && flip(next) > flip(result)) result = next;
    --next;
  }
  return result;
}

N solve(const N n) {
  N result = 1;
  N counter = 1;
  while (counter < n) {
    N next = next_flip_point(n, counter);
    //print("next", next);
    if (next >= n) return result + (n - counter);
    // find next that flip(next) is maximal, but less then n
    next = find_optimal_next(next, n);
    if (next == flip(next)) return result + (n - counter);
    print("next", next);
    result += (next - counter) + 1;
    print("result", result);
    counter = flip(next);
    print("counter", counter);
  }
  return result;
}

int main() {
  int T=0;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    N n; cin >> n;
    cout << "Case #" << t+1 << ": " << solve(n) << endl;
  }
  return 0;
}
