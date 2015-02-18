// https://code.google.com/codejam/contest/32013/dashboard
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_S = 100;

int first[MAX_S];
int last[MAX_S];
int queries[1000];
int S, Q;

bool update(int from) {
	fill_n(first, S, -1);
	for (int q = from; q < Q; ++q) {
		if (first[queries[q]] == -1) {
			first[queries[q]] = q;
		}
	}
	
	return true;
}

void solvecase() {

	cin >> S;
	cin.get();
	fill_n(first, S, -1);
	fill_n(last, S, -1);
	char names[MAX_S][100];
	for (int s = 0; s < S; ++s) {
		cin.getline(names[s], 100);
	}

	// read
	cin >> Q;
	cin.get();
	char query[100];
	for (int q = 0; q < Q; ++q) {
		cin.getline(query, 100);
		for (int s = 0; s < S; ++s) {
			int r = strcmp(names[s], query);
			if (strcmp(names[s], query) == 0) {
				if (first[s] == -1) {
					first[s] = q;
				}

				last[s] = q;
				queries[q] = s;
				break;
			}
		}
	}

	// calculate
	unsigned switches = 0;
	unsigned act = 0;
	for (int s = 0; s < S; ++s) {
		if (first[s] == -1) {
			// there is on "non-searched" SE
			cout << "0" << endl;
			return;
		}

		if (first[s] > first[act]) {
			act = s;
		}
	}

	while (first[act] >= 0) {
		update(first[act]);
		++switches;
		act = 0;
		// find next to switch to
		for (int s = 0; s < S; ++s) {
			if (first[s] == -1) {
				act = s;
				break;
			}
			if (first[s] > first[act]) {
				act = s;
			}
		}
	}

	cout << switches << endl;
}

int TEST_CASES;
int main() {
	cin >> TEST_CASES;
	for (int t = 1; t <= TEST_CASES; ++t) {
		cout << "Case #" << t << ": ";
		solvecase();
	}

	return 0;
}