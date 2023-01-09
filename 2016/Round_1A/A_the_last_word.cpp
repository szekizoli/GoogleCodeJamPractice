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

const size_t input_size = 1000;
const size_t word_size = 2 * input_size + 1;

struct Word {
	array<char, word_size> word;
	unsigned _first = input_size, _last = input_size;

	void push_back(char c) {
		word[_last] = c;
		++_last;
	}

	void push_front(char c) {
		--_first;
		word[_first] = c;
	}

	char first() {
		return word[_first];
	}

	bool empty() {
		return _first == _last;
	}

	char* begin() {
		return &word[_first];
	}

	char* end() {
		return &word[_last];
	}
};

void solve(const string& input)
{
	Word w;
	for (auto c : input) {
		if (w.empty() || c >= w.first())
			w.push_front(c);
		else
			w.push_back(c);
	}

	std::copy(w.begin(), w.end(), std::ostream_iterator<char>(std::cout, ""));
}

int main() {
	unsigned T;
	string s;
	cin >> T;
	f(t, T) {
		cin >> s;
		try {
			cout << "Case #" << t + 1 << ": ";
			solve(s);
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