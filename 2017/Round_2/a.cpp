// Fresh Chocolate
// https://code.google.com/codejam/contest/5314486/dashboard

#include <array>
#include <iostream>
#include <vector>

using namespace std;

bool even(int i) {
  return (i & 1) == 0;
}

int solve_2(int N) {
  int countEven = 0;
	for (int i = 0; i < N; ++i) {
    int n; cin >> n;
    if (even(n)) ++countEven;
  }
  int countOdd = N - countEven;
  return countEven + (countOdd + 1)/2;
}

int solve_3(int N) {
	array<int, 3> count{0, 0, 0};
	for (int i = 0; i < N; ++i) {
    int n; cin >> n;
    ++count[n % 3];
  }
	int count12 = min(count[1], count[2]);
  int rest1 = count[1] - count12;
  int rest2 = count[2] - count12;
  return count[0] + count12 + (rest1+2)/3 + (rest2+2)/3; 
}

int solve_4(int N) {
	array<int, 4> count{0, 0, 0};
	for (int i = 0; i < N; ++i) {
    int n; cin >> n;
    ++count[n % 4];
  }
	int count13 = min(count[1], count[3]);
  int rest13 = max(count[1], count[3]) - count13;
  int rest2 = even(count[2]) ? 0 : 2;
  return count[0] + count13 + (count[2])/2 + (rest13 + rest2 + 3) / 4;	
}

int solve(int N, int P) {
	if (P == 2) return solve_2(N);
	if (P == 3) return solve_3(N);
  return solve_4(N);
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
  	int N, P;
		cin >> N >> P;
    cout << "Case #" << t+1 << ": " << solve(N, P) << endl;
  }
	return 0;
}
