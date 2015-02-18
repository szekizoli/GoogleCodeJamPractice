//https://code.google.com/codejam/contest/32016/dashboard#s=p2
// solved after conest analysis.
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

unsigned C, N;


struct num {
	unsigned long long a, b;
	num operator*(num& o) const {
		num r = { a * o.a + 5 * b*o.b, a*o.b + b*o.a };
		r.mod();
		return r;
	}
	void mod() {
		a %= 1000;
		b %= 1000;
	}
};

num buff[32];

void init() {
	buff[0] = num{ 3, 1 };
	for (int i = 1; i < 32; ++i) {
		buff[i] = buff[i - 1] * buff[i - 1];
	}
}

void solvecase() {
	cin >> N;
	num result = { 1, 0 };
	for (int i = 0; i < 32 && N > 0; i++) {
		if (N & 1 == 1) {
			result = result * buff[i];
		}

		N = N >> 1;
	}

	cout << setfill('0') << setw(3) << (2*result.a-1)%1000 << endl;
}

int main() {
	cin >> C;
	init();
	for (int t = 1; t <= C; ++t) {
		cout << "Case #" << t << ": ";
		solvecase();
	}

	return 0;
}