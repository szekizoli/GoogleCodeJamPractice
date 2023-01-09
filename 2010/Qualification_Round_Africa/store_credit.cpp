#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int prices [1001];
int C, I, N;
int p;
char solved = 0;

int main() {
    cin >> N;
    for (int n = 1; n <= N; ++ n) {
        cin >> C >> I;
        solved = 0;
        for (int i = 1; i <= I; ++i) {
            cin >> p;
            if (p > C || solved == 1) continue;
            if (prices[p] == 0) {
                prices[C - p] = i;
            } else {
                cout << "Case #" << n << ": " << prices[p] << " " << i << endl;
                std::fill_n(prices, 1001, 0);
                solved = 1;
            }
        }
    }

    return 0;
}