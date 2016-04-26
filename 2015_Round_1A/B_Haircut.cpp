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

typedef long long value_type;
typedef vector<pair<value_type, value_type>> vecpair;

// which barber will start which client
auto get_next(const vector<int>& barbers, value_type t) {
	vecpair result;
	value_type count = 0;
	for (int i = 0; i < barbers.size(); ++i) {
		int m = barbers[i];
		count += ((t+m-1) / m);
		if (t % m == 0) {
			result.push_back(make_pair(i, 0));
		}
	}

	for (int i = 0; i < result.size(); ++i) {
		result[i].second = count + 1 + i;
	}

	return result;
}

auto contains_client(const vecpair& v, int n) {
	return find_if(v.begin(), v.end(), [n](const pair<int, int>& p) {return p.second == n;});
}

value_type guess_t(const vector<int>& barbers, int n) {
	double sum = 0;
	for (int b : barbers) {
		sum += 1.0 / (double)b;
	}
	return (value_type)((n - barbers.size()) / sum);
}

void print(vecpair& v) {
	cout << "[";
	for (auto p : v) {
		cout << "(" << p.first << ", " << p.second << "), ";
	}
	cout << "]";
}

void test_get_next() {
	cout << "t=5, ";
	print(get_next({ 10, 5 }, 5));
	cout << endl;
	cout << "t=10, ";
	print(get_next({ 10, 5 }, 10));
	cout << endl;
	cout << "t=15, ";
	print(get_next({ 10, 5 }, 15));
	cout << endl;
}

void test_contains_client(const vector<int>& v, int t, int n) {
	cout << "t="<< t << ", ";
	auto next = get_next(v, t);
	print(next);
	cout << " contains " << n << "? " << (contains_client(next, n) != next.end()) << endl;
}
void test_contains_client() {
	test_contains_client({ 10, 5, }, 5, 4);
	test_contains_client({ 10, 5, }, 10, 4);
	test_contains_client({ 10, 5, }, 15, 4);
}

void test_guess_t(const vector<int>& v, int n) {
	auto t = guess_t(v, n);
	cout << "n=" << n << ", t=" << t << endl;
	while (true) {
		auto pairs = get_next(v, t);
		auto found = contains_client(pairs, n);
		if (found != pairs.end()) {
			cout << "Found b=" << found->first + 1 << endl;
			return;
		}
		++t;
	}
}

void test_guess_t() {
	test_guess_t({ 10, 5 }, 4);
	test_guess_t({ 7, 7, 7 }, 12);
	test_guess_t({ 4, 2, 1 }, 8);
	test_guess_t({ 2, 3, 5, 7 }, 10);
	test_guess_t({ 25, 25, 25, 25, 25 }, 1000000000);
}

void test() {
	test_contains_client();
	test_guess_t();
}

vector<int> read(int N) {
	vector<int> v(N);
	for (int i{ 0 }; i < N; ++i) {
		cin >> v[i];
	}

	return v;
}

void solve(const vector<int>& m, int n) {
	auto t = guess_t(m, n);
	while (true) {
		auto pairs = get_next(m, t);
		auto found = contains_client(pairs, n);
		if (found != pairs.end()) {
			cout << found->first + 1 << endl;
			return;
		}
		++t;
	}
}

void loop(int T) {
	int B, N;
	f(t, T) {
		cin >> B >> N;
		cout << "Case #" << t + 1 << ": ";
		solve(read(B), N);
	}
}

int main() {
	try {
		//test();
		int T = 0;
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