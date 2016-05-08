#include <array>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

#define f(i, N) for(unsigned i = 0; i < N; ++i)

using namespace std;

typedef long long value_type;
typedef vector<pair<value_type, value_type>> vecpair;


bool incr(int& v, int max) {
	if (v == max) {
		v = 1;
		return false;
	}
	++v;
	return true;
}

void validate(const set<int>& s, int val) {
	if (s.count(val) != 0)
		throw runtime_error("already generated");
}

void solve(int J, int P, int S, int K) {
	if (S == 1) {
		cout << "1" << endl;
		cout << "1 1 1" << endl;
		return;
	}
	K = min(K, S);
	cout << J*P*K << endl;
	int s = 1;
	for (int j = 1; j <= J; ++j) {
		s = j;
		for (int p = 1; p <= P; ++p) {
			for (int i = 0; i < K; ++i) {
				cout << j << " " << p << " " << s << endl;
				incr(s, S);
			}
		}
	}
}

void loop(unsigned T) {
	int J, S, P, K;
	f(t, T) {
		cin >> J >> P >> S >> K;
		cout << "Case #" << t + 1 << ": ";
		solve(J, P, S, K);
	}
}

int main() {
	try {
		//test();
		unsigned T = 0;
		cin >> T;
		loop(T);
	}
	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
	catch (...) {
		cout << "Unknown failure!" << endl;
	}
}