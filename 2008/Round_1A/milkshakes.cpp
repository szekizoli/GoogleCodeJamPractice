// https://code.google.com/codejam/contest/32016/dashboard#s=p1
// solved after conest analysis.

#include <cstdio>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

const int MAX_N = 2000;  // flavor
const int MAX_M = 2000; // customer

int malted[MAX_M];			// the malted choice of a customer
char choice[MAX_N];			// the result
bool visited[MAX_M];		// the customer is satisfied
bool unmalted[MAX_M][MAX_N];// 
int num[MAX_M];				// number od unmalted available choices

int T, N, M;
void init() {
	fill_n(malted, MAX_M, -1);		// -1: unset, otherwise the set flavor
	fill_n(choice, MAX_N, '0');		// 0: not set, '0' unmalted, '1' malted
	fill_n(visited, MAX_M, false);
	fill_n(num, MAX_M, 0);
	for (int i = 0; i < MAX_M; ++i) {
		fill_n(unmalted[i], MAX_N, false);
	}
}

/*
Assume that the problem can be solved with only unmalted flavors.
Than we need to change to malted, where no other possibilities left.
*/

void solvecase() {
	cin >> N >> M;
	init();
	int x, y;
	for (int m = 0; m < M; ++m) {
		cin >> T;
		for (int t = 0; t < T; ++t) {
			cin >> x >> y;
			--x;
			if (y == 1) { // malted
				malted[m] = x;
			}
			else { // unmalted
				unmalted[m][x] = true;
				num[m]++;
			}
		}
	}

	bool impossible = false;
	bool found = false;
	
	do  {
		found = false;
		for (int c = 0; c < M; ++c) {				// check everyone
			if (!visited[c] && num[c] == 0) {		// not yet satisfied and doesn't have unmalted option
				visited[c] = true;					// is now satisfied
				found = true;						// found one that is satisfied
				int f = malted[c];
				if (f == -1) {						// if the malted
					impossible = true;
					break;
				}

				choice[f] = '1';
				for (int m = 0; m < M; ++m) {
					if (unmalted[m][f]) {
						unmalted[m][f] = false;
						--num[m];
					}
				}
			}
		}
	} while (found && !impossible);

	if (impossible) {
		cout << " IMPOSSIBLE";
	}
	else {
		for (int c = 0; c < N; ++c) {
			cout << " " << choice[c];
		}
	}
	cout << endl;
}

int C;
int main() {
	cin >> C;
	for (int t = 1; t <= C; ++t) {
		cout << "Case #" << t << ":";
		solvecase();
	}

	return 0;
}