#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

#define TYPE char
#define f(i, N) for(unsigned i = 0; i < N; ++i)
#define fr(i, N) for(int i = N-1; i >= 0; --i) // reverse
#define ff(i, j, N) for(unsigned i = 0; i < N; ++i) for(unsigned j = 0; j < N; ++j)
#define V vector<TYPE>
#define VV vector<V>

void print(VV& t) {
	for(const auto& v : t) {
		copy(begin(v), end(v), ostream_iterator<TYPE>(std::cout, ""));
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void gravity(VV& t) {
	f(j, t.size()) {
		int c = 0;
		fr(i, t.size()) {
			if (t[i][j] == '.') ++c;
			else if (c > 0) { swap(t[i][j], t[i+c][j]); }
		}
	}
}

VV read(int N) {
	VV table(N);
	f(i, N) { table[i] = V(N); }
	ff(i, j, N) {
		cin >> table[j][N - 1 - i];
	}
	return table;
}

struct counter {
	const int count;
	const TYPE elem;
	int found;
	counter(const int c_, const TYPE e_) : count(c_), elem(e_) {}
	bool match(TYPE e) {
		if (e == elem) { ++found; }
		else { found = 0; }
		return count == found;
	}
};

int find(const VV& t, const TYPE elem, const int count) {
	auto N = t.size();
	counter c(count, elem);

	// vertical
	f(j, t.size()) {
		c.found = 0;
		fr(i, t.size()) {
			if (c.match(t[i][j])) return 1;
		}
	}
	
	// horizontal
	f(i, t.size()) {
		c.found = 0;
		f(j, t.size()) {
			if (c.match(t[i][j])) return 1;
		}
	}

	// this way -> '\'
	f(i, N - count + 1) {
		c.found = 0;
		// testing lower half
		f(j, N - i) {
			if (c.match(t[j+i][j])) return 1;
		}

		c.found = 0;
		// testing upper half
		f(j, N - i) {
			if (c.match(t[j][j + i])) return 1;
		}
	}

	// this way -> '/'
	fr(i, N) {
		c.found = 0;
		// testing upper half
		f(j, i+1) {
			if (c.match(t[i - j][j])) return 1;
		}
	}

	f(i, N) {
		c.found = 0;
		// testing lower half
		f(j, N - i) {
			if (c.match(t[N - j - 1][i + j])) return 1;
		}
	}

	return 0;
}

int main(){
	int T;
	int N, K;
	cin >> T;
	string result[2][2] = { {"Neither", "Red"},
						    {"Blue",    "Both"} };
	f(t, T) {
		cin >> N >> K;
		auto table = read(N);
		gravity(table);
		auto r_b = find(table, 'B', K);
		auto r_r = find(table, 'R', K);
		cout << "Case #" << t+1 << ": " << result[r_b][r_r] << endl;
	}
}