// https://code.google.com/codejam/contest/32017/dashboard#s=p0
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

long long trees[3][3];
void init() {
	for (int i = 0; i < 3; ++i)
		fill_n(trees[i], 3, 0);
}

int order[6][3] = {
		{ 0, 1, 2},
		{ 0, 2, 1},
		{ 1, 0, 2},
		{ 1, 2, 0},
		{ 2, 0, 1},
		{ 2, 1, 0}
};

void addVal(long long X, long long Y) {
	trees[X % 3][Y % 3]++;
}

long long countit(long long x, long long y, long long z) {
	return x * y * z;
}

long long countsame(long long x) {
	if (x < 3) return 0;
	return (x * (x-1) * (x-2))/6;
}

void solvecase(){
	init();
	long long n, A, B, C, D, x0, y0, M;
	cin >> n >> A >> B >> C >> D >> x0 >> y0 >> M;
	long long X, Y;
	X = x0;
	Y = y0;
	addVal(X, Y);
	for (int i = 1; i < n ; ++i) {
		X = (A*X + B) % M;
		Y = (C*Y + D) % M;
		addVal(X, Y);
	}

	long long count = 0;
	for (int i = 0; i < 6; ++i) {
		count += countit(trees[order[i][0]][0], trees[order[i][1]][1], trees[order[i][2]][2]);
	}
	for (int i = 0; i < 3; ++i) {
		count += countit(trees[i][0], trees[i][1], trees[i][2]);
		count += countit(trees[0][i], trees[1][i], trees[2][i]);
	}

	for (int i = 0; i < 9; ++i) {
		count += countsame(trees[i / 3][i % 3]);
	}

	cout << count << endl;
}

int N;
int main() {
	cin >> N;
	init();
	for (int t = 1; t <= N; ++t) {
		cout << "Case #" << t << ": ";
		solvecase();
	}

	return 0;
}