#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#define TYPE int
#define f(i, N) for(unsigned i = 0; i < N; ++i)
#define fr(i, N) for(int i = N-1; i >= 0; --i) // reverse
#define ff(i, j, N) for(unsigned i = 0; i < N; ++i) for(unsigned j = 0; j < N; ++j)
#define V vector<TYPE>

TYPE get_max_diff(const V& v) {
	TYPE max_diff = 0;
	f(i, v.size() - 1) {
		max_diff =  std::max(max_diff, v[i] - v[i + 1]);
	}
	return max_diff;
}

TYPE get_sum_decr_diff(const V& v) {
	TYPE sum = 0;
	f(i, v.size() - 1) {
		sum += std::max(0, v[i] - v[i + 1]);
	}
	return sum;
}

TYPE get_by_second_assumption(const V& v, TYPE rate) {
	TYPE sum = 0;
	f(i, v.size() - 1) {
		sum += std::min(rate, v[i]);
	}
	return sum;
}

void test_max_diff(const V& v) {
	cout << "[";
	std::copy(v.begin(), v.end(), std::ostream_iterator<TYPE>(cout, ", "));
	cout << "] = " << get_max_diff(v) << endl;
}

void test_max_diff() {
	test_max_diff({ 10, 5, 15, 5 });
	test_max_diff({ 100, 100 });
	test_max_diff({ 81, 81, 81, 81, 81, 81, 0 });
	test_max_diff({ 23, 90, 40, 0, 100, 9 });
}

void test_get_sum_decr_diff(const V& v) {
	cout << "[";
	std::copy(v.begin(), v.end(), std::ostream_iterator<TYPE>(cout, ", "));
	cout << "] = " << get_sum_decr_diff(v) << endl;
}

void test_get_sum_decr_diff() {
	test_get_sum_decr_diff({ 10, 5, 15, 5 });
	test_get_sum_decr_diff({ 100, 100 });
	test_get_sum_decr_diff({ 81, 81, 81, 81, 81, 81, 0 });
	test_get_sum_decr_diff({ 23, 90, 40, 0, 100, 9 });
}

void test_get_by_second_assumption(const V& v) {
	cout << "[";
	std::copy(v.begin(), v.end(), std::ostream_iterator<TYPE>(cout, ", "));
	auto rate = get_max_diff(v);
	cout << "] = " << get_by_second_assumption(v, rate) << endl;
}

void test_get_by_second_assumption() {
	test_get_by_second_assumption({ 10, 5, 15, 5 });
	test_get_by_second_assumption({ 100, 100 });
	test_get_by_second_assumption({ 81, 81, 81, 81, 81, 81, 81, 0 });
	test_get_by_second_assumption({ 23, 90, 40, 0, 100, 9 });
}

vector<TYPE> read(int N) {
	vector<TYPE> v(N);
	for (int i{ 0 }; i < N; ++i) {
		cin >> v[i];
	}

	return v;
}

void solve(const vector<int>& v) {
	cout << get_sum_decr_diff(v) << " ";
	auto rate = get_max_diff(v);
	cout << get_by_second_assumption(v, rate);
}

void loop(TYPE T) {
	TYPE N;
	f(t, T) {
		cin >> N;
		cout << "Case #" << t + 1 << ": ";
		solve(read(N));
		std::cout << std::endl;
	}
}

void test() {
	test_get_sum_decr_diff();
	test_max_diff();
	test_get_by_second_assumption();
}

int main() {
	try {
		//test();
		unsigned T;
		cin >> T;
		loop(T);
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cout << "Unknown exception" << endl;
	}
}