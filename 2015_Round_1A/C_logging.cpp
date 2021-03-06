#include <array>
#include <exception>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#define f(i, N) for(unsigned i = 0; i < N; ++i)

using namespace std;

template<typename T>
class safe_int {
public:
	safe_int() : x(0) {}
	safe_int(T x) : x(x) {}
	safe_int(const safe_int& o) : x(o.x) {}
	safe_int(safe_int&& o) : x(o.x) {}

	bool operator==(const safe_int& o) const {
		return x == o.x;
	}
	safe_int operator+(const safe_int& o) const {
		if (0 < min(x, o.x)) {
			if (x > std::numeric_limits<T>::max() - o.x) {
				cout << "x=" << x << ", o.x=" << o.x << ", max=" << std::numeric_limits<T>::max() << endl;
				throw std::runtime_error("max overflow");
			}
		}
		if (max(x, o.x) < 0) {
			if (x < std::numeric_limits<T>::min() - o.x) {
				cout << "x=" << x << ", o.x=" << o.x << ", min=" << std::numeric_limits<T>::max() << endl;
				throw std::runtime_error("min overflow");
			}
		}
		return safe_int{ x + o.x };
	}
	bool operator<(const safe_int& o) const {
		return x < o.x;
	}
	safe_int operator-() const {
		return safe_int(-x);
	}
	safe_int operator-(const safe_int& o) const {
		return operator+(-o);
	}
	safe_int operator*(const safe_int& o) const {
		return x*o.x;
	}
	friend ostream& operator<<(ostream& out, safe_int& i) {
		out << i.x;
		return out;
	}
	friend istream& operator>>(istream& in, safe_int& i) {
		in >> i.x;
		return in;
	}
private:
	T x;
};

struct v2d {
	typedef long long value_type;
	v2d() : coord(make_pair(0, 0)) {}
	v2d(value_type x, value_type y) : coord(make_pair(x, y)) {}
	bool operator==(const v2d& other) const {
		return x() == other.x() && y() == other.y();
	}
	v2d operator-(const v2d& other) const {
		return v2d(x() - other.x(), y() - other.y());
	}
	value_type operator*(const v2d& other) const {
		return x()*other.x() + y()*other.y();
	}
	friend istream& operator>>(istream& in, v2d& v) {
		in >> v.coord.first >> v.coord.second;
		return in;
	}
	v2d normal() const {
		return v2d(-y(), x());
	}
	value_type x() const { return coord.first; }
	value_type y() const { return coord.second; }
private:
	std::pair<value_type, value_type> coord;
};

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

struct side_counter {
	side_counter() {
		counts.fill(0);
	}
	void add(v2d::value_type side) {
		++counts[DIFF + sgn(side)];
	}
	int get_min() {
		return min(counts[0], counts[2]);
	}
private:
	array<int, 3> counts;
	const int DIFF = 1;
};

template<int N>
bool next_tuple(array<int, N>& tuple, const int max) {
	for (int i = 0; i < N; ++i) {
		if (tuple[i] < max - i) {
			++tuple[i];
			for (int j = i-1; j >= 0; --j)
				tuple[j] = tuple[j + 1] + 1;
			return true;
		}
 	}
	return false;
}

v2d::value_type get_side(const v2d& a, const v2d& b, const v2d& c) {
	auto line = b - a;
	auto norm = line.normal();
	return norm * (c - a);
}

int get_min_side(const vector<v2d>& vecs, const v2d& a, const v2d& b) {
	side_counter sc;
	const auto line = b - a;
	const auto norm = line.normal();
	for (const auto& v : vecs) {
		if (a == v || b == v) continue;
		sc.add(norm * (v - a));
	}
	
	return sc.get_min();
}

vector<int> solve_with_tuples(const vector<v2d>& vecs) {
	if (vecs.size() < 4) {
		return vector<int>(vecs.size(), 0);
	}
	vector<int> result(vecs.size(), 3000);
	array<int, 2> tuple = { 1, 0 };
	const int max = vecs.size() - 1;
	do {
		int min_side = get_min_side(vecs, vecs[tuple[0]], vecs[tuple[1]]);
		result[tuple[0]] = min(min_side, result[tuple[0]]);
		result[tuple[1]] = min(min_side, result[tuple[1]]);
	} while (next_tuple<2>(tuple, max));
	return result;
}

void test_side_detection(const vector<v2d>& vecs) {
	v2d v0(5, 5);
	v2d v1(10, 0);
	v2d v2(0, 10);

	v2d v3(10, 10);
	v2d v4(10, 5);
	v2d v5(5, 10);
	
	v2d v6(0, 0);
	v2d v7(5, 0);
	v2d v8(0, 5);
	cout << get_side(v0, v1, v2) << endl;
	cout << endl;
	cout << get_side(v0, v1, v3) << endl;
	cout << get_side(v0, v1, v4) << endl;
	cout << get_side(v0, v1, v5) << endl;
	cout << endl;
	cout << get_side(v0, v1, v6) << endl;
	cout << get_side(v0, v1, v7) << endl;
	cout << get_side(v0, v1, v8) << endl;
}

void test_get_min_side(const vector<v2d>& vecs) {
	cout << "Min side: " << get_min_side(vecs, vecs.at(0), vecs.at(1)) << endl;
}

void print(array<int, 3>& a) {
	cout << a[0] << ", " << a[1] << ", " << a[2] << endl;
}

void test_next_triple() {
	array<int, 3> a = { 3, 2, 1 };
	int max = 10;
	do {
		print(a);
	} while (next_tuple<3>(a, max));
}

void test() {
	test_next_triple();
	vector<v2d> vecs;
	vecs.push_back(v2d(833861, 816827));
	vecs.push_back(v2d(-996936, 498468));
	vecs.push_back(v2d(-156117, 175725));
	vecs.push_back(v2d(187519, 158769));
	vecs.push_back(v2d(521283, 247));
	vecs.push_back(v2d(-200240, 219857));
	vecs.push_back(v2d(811296, 75302));
	vecs.push_back(v2d(-520568, 540434));
	vecs.push_back(v2d(-147251, 908782));
	test_side_detection(vecs);
	test_get_min_side(vecs);
}

vector<v2d> read(int N) {
	vector<v2d> v(N);
	for (int i{ 0 }; i < N; ++i) {
		cin >> v[i];
	}

	return v;
}

void solve(const vector<v2d>& v) {
	auto result = solve_with_tuples(v);
	std::copy(result.begin(), result.end(), std::ostream_iterator<int>(cout, " \n"));
}

void loop(int T) {
	int N;
	f(t, T) {
		cerr << "Test: " << t << endl;
		cin >> N;
		cout << "Case #" << t + 1 << ": " << endl;
		solve(read(N));
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