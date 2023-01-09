#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

char buffer[1000];
char letters[1000];
int N;

void solvecase() {
	std::cin.getline(buffer, 1000);
	int len = strlen(buffer);
	int lpos = 0;
	letters[len] = 0;
	int wl = 0;
	for (int i = len-1; i >= 0; --i) {
		if (buffer[i] != ' ') {
			++wl;
			continue;
		}

		for (int j = i + 1; j <= i + wl; ++j) {
			letters[lpos] = buffer[j];
			++lpos;
		}

		wl = 0;

		letters[lpos] = ' ';
		++lpos;
	}

	for (int j = 0; j <= wl; ++j) {
		letters[lpos] = buffer[j];
		++lpos;
	}

	letters[lpos] = 0;
	++lpos;

	cout << letters << endl;
}

int main() {
	cin >> N;
	cin.get();
	for (int n = 1; n <= N; ++n) {
		cout << "Case #" << n << ": ";
		solvecase();
		std::fill_n(letters, 1001, 0);
	}

	return 0;
}