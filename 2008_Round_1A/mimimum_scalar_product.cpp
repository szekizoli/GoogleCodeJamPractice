// https://code.google.com/codejam/contest/32016/dashboard#s=p0

#include <cstdio>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

const int SIZE = 800;
long long numbers[2][SIZE];
int T, N;

void solvecase() {
	cin >> N;
	for (int n = 0; n < 2; ++n)
	{
		for (int i = 0; i < N; ++i) {
			cin >> numbers[n][i];
		}
	}

	sort(numbers[0], numbers[0] + N);
	sort(numbers[1], numbers[1] + N, [](long long i, long long j) { return i > j; });

	long long result = 0;

	for (int i = 0; i < N; ++i) {
		result += numbers[0][i] * numbers[1][i];
	}

	cout << result << endl;
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cout << "Case #" << t << ": ";
		solvecase();
	}

	return 0;
}