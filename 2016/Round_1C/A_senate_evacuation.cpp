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


typedef pair<int, char> party;
typedef vector<party> vecpair;

bool less_p(const party& a, const party& b) {
	return a.first < b.first;
}

void remove_next(vecpair& v, vector<char>& result) {
	auto& x = v.back();
	result.push_back(x.second);
	--x.first;
	if (x.first == 0) {
		v.pop_back();
	}
}

void test() {
	vecpair v = { {3, 'A'},{ 2, 'B' },{ 2, 'C' } };
	vector<char> result;
	for (int i = 0; i < 7; i++) {
		std::sort(v.begin(), v.end(), less_p);
		remove_next(v, result);
	}
	std::copy(begin(result), end(result), std::ostream_iterator<char>(cout, ", "));
	cout << endl;

}

vector<int> read(int N) {
	vector<int> r;
	int n;
	f(i, N) {
		cin >> n;
		r.push_back(n);
	}
	return r;
}

void solve_for_2(int num_by_party) {
	for (int i = 0; i < num_by_party - 1; ++i) {
		cout << "AB ";
	}
	cout << "AB";
	cout << endl;
}

vecpair generate(const vector<int>& m) {
	vecpair v;
	char c = 'A';
	for (auto i : m) {
		v.push_back({ i, c });
		++c;
	}
	return v;
}

void test_invariant(const vecpair& v) {
	if (v.size() < 2) return;
	int sum = 0;
	for (auto& n : v) {
		sum += n.first;
	}
	if (v.front().first * 2 > sum) {
		throw runtime_error("majority happened");
	}
}

void solve(const vector<int>& m, int n) {
	if (n == 2) {
		solve_for_2(m.at(0));
		return;
	}
	vector<char> result;
	vecpair v = generate(m);
	while (v.size()> 0) {
		std::sort(v.begin(), v.end(), less_p);
		remove_next(v, result);
		test_invariant(v);
	}
	
	auto size = result.size();
	for (int i = 0; i < size - 2; ++i) {
		cout << result[i] << " ";
	}

	cout << result[size - 2] << result[size - 1] << endl;
}

void loop(unsigned T) {
	int N;
	f(t, T) {
		cin >> N;
		cout << "Case #" << t + 1 << ": ";
		solve(read(N), N);
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