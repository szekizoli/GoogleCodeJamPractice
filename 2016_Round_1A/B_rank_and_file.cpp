#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <bitset>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#define TYPE unsigned long long
#define f(i, N) for(unsigned i = 0; i < N; ++i)
#define fr(i, N) for(int i = N-1; i >= 0; --i) // reverse
#define ff(i, j, N) for(unsigned i = 0; i < N; ++i) for(unsigned j = 0; j < N; ++j)
#define V vector<TYPE>

const unsigned MAX_HEIGHT = 2501;

inline
bool odd(unsigned i) {
	return i & 1 == 1;
}

array<unsigned, MAX_HEIGHT> heights;

void solve(TYPE N)
{
	heights.fill(0);
	TYPE max = N * (2 * N - 1);
	unsigned h;
	for (TYPE i{ 0 }; i < max; ++i) {
		cin >> h;
		++heights[h];
	}

	TYPE i{ 1 };
	while (N > 0 && i < MAX_HEIGHT) {
		if (odd(heights[i])) {
			cout << " " << i;
			--N;
		}
		++i;
	}
}

int main() {
	unsigned T;
	TYPE N;
	cin >> T;
	f(t, T) {
		cin >> N;
		try {
			cout << "Case #" << t + 1 << ":";
			solve(N);
			std::cout << std::endl;
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}
		catch (...) {
			cout << "Unknown exception" << endl;
		}
	}
}