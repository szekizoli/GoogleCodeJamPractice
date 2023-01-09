#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

char buffer[1000];
int N;

char codes[] = { '2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', '6', '7', '7', '7', '7',
					'8', '8', '8', '9', '9', '9', '9', };

int times[] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4,
1, 2, 3, 1, 2, 3, 4, };

char c;
int t;

void solvecase() {
	std::cin.getline(buffer, 1000);
	int i = 0;
	char prev = 0;
	while (buffer[i] != 0) {
		if (buffer[i] == ' ') {
			c = '0';
			t = 1;
		}
		else {
			c = codes[buffer[i] - 'a'];
			t = times[buffer[i] - 'a'];
		}
		
		if (prev == c) cout << ' ';
		for (int j = 0; j < t; ++j) cout << c;
		prev = c;
		++i;
	}
}

int main() {
	cin >> N;
	cin.get();
	for (int n = 1; n <= N; ++n) {
		cout << "Case #" << n << ": ";
		solvecase();
	}

	return 0;
}