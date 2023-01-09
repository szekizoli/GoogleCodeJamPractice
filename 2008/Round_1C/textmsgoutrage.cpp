#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

using num = long long;

void solve(int c) {
	num P, K, L;
	cin >> P >> K >> L;
	vector<num> freq(L);
	for (int i = 0; i < L; ++i) {
		cin >> freq[i];
	}

	std::sort(freq.begin(), freq.end(), std::greater<num>());

	num sum = 0;

	int l = 0;
	for (int p = 1; p <= P; ++p) {
		for (int k = 0; k < K && l < L; ++k, ++l) {
			sum += freq[l] * p;
		}
	}

	cout << "Case #" << c << ": " << sum << endl;
}

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		solve(i+1);
	}

	return 0;
}
