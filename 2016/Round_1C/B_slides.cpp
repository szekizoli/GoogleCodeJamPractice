#include <array>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

#define f(i, N) for(unsigned i = 0; i < N; ++i)

using namespace std;

typedef unsigned long long value_type;
typedef vector<pair<value_type, value_type>> vecpair;
typedef vector<bool> matrix;

void set(matrix& m, int i, int j, int size, bool value) {
	m.at(i*size + j) = value;
}

void print(const matrix& m, int size) {

}

bool is_odd(value_type t) {
	return t & 1 == 1;
}

vector<pair<int, int>> to_path(value_type subset, int B) {
	vector<pair<int, int>> result;
	pair<int, int> current = { 0, 0 };
	for (int i = 1; i < B - 1; ++i) {
		if (is_odd(subset)) {
			current.second = i;
			result.push_back(current);
			current.first = i;
		}
		subset >>= 1;
	}
	current.second = B - 1;
	result.push_back(current);
	return result;
}

bool next(vector<bool>& v) {
	for (int i = v.size() - 1; i >= 0; --i) {
		if (!v[i]) {
			v[i] = true;
			return true;
		}
		else {
			v[i] = false;
		}
	}
	return false;
}

void print(vector<pair<int, int>>& v) {
	for (auto& p : v)
		cout << "(" << p.first << " -> " << p.second << ")";
	cout << endl;
}

void test_to_path() {
	auto r0 = to_path(0, 5);
	print(r0);
	auto r1 = to_path(1, 5);
	print(r1);
	auto r2 = to_path(2, 5);
	print(r2);
}

void test() {
	test_to_path();
}

void print_matrix(const matrix& m, value_type B) {
	for (value_type i = 0; i < B; ++i) {
		for (value_type j = 0; j < B; ++j) {
			if (m.at(i*B + j)) {
				cout << "1";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}
}

vector<int> read(int N) {
	return vector<int>();
}

bool can_solve(value_type B, value_type M) {
	value_type v = 1;
	return M <= (v << (B - 2));
}

void solve(value_type B, value_type M) {
	if (!can_solve(B, M)) {
		cout << "IMPOSSIBLE" << endl;
		return;
	}
	else {
		cout << "POSSIBLE" << endl;
	}

	// first
	value_type m = M - 1;
	value_type b = 1;
	b = b << (B - 3);
	cout << "0";
	for (int i = 0; i < B - 2; ++i) {
		if ((m&b) > 0) cout << "1";
		else cout << "0";
		b >>= 1;
	}
	cout << "1" << endl;
	// middle
	for (int i = 1; i < B - 1; ++i) {
		for (int j = 0; j <= i; ++j) {
			cout << "0";
		}
		for (int j = i+1; j < B; ++j) {
			cout << "1";
		}
		cout << endl;
	}

	// last
	for (int i = 0; i < B; ++i) {
		cout << "0";
	}
	cout << endl;
}

void loop(value_type T) {
	value_type B, M;
	for (value_type t = 0; t < T; ++t) {
		cin >> B >> M;
		cout << "Case #" << t + 1 << ": ";
		solve(B, M);
	}
}

int main() {
	try {
		//test();
		value_type T = 0;
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