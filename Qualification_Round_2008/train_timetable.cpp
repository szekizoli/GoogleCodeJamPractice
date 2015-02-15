// https://code.google.com/codejam/contest/32013/dashboard#s=p1
#include <iostream>

using namespace std;
const int MAX_TRAIN = 100;

int SA[MAX_TRAIN];
int FA[MAX_TRAIN];
int SB[MAX_TRAIN];
int FB[MAX_TRAIN];

int compare_ints(const void* a, const void* b)   // comparison function
{
	int arg1 = *reinterpret_cast<const int*>(a);
	int arg2 = *reinterpret_cast<const int*>(b);
	return arg1 - arg2;
}

void solvecase(){
	int turnaround, NA, NB;
	cin >> turnaround >> NA >> NB;

	int hour, minute;
	char c;
	for (int i = 0; i < NA; ++i) {
		cin >> hour >> c >> minute;
		SA[i] = hour * 60 + minute;
		cin >> hour >> c >> minute;
		FA[i] = hour * 60 + minute + turnaround;
	}

	for (int i = 0; i < NB; ++i) {
		cin >> hour >> c >> minute;
		SB[i] = hour * 60 + minute;
		cin >> hour >> c >> minute;
		FB[i] = hour * 60 + minute + turnaround;
	}

	std::qsort(SA, NA, sizeof(int), compare_ints);
	std::qsort(FA, NA, sizeof(int), compare_ints);
	std::qsort(SB, NB, sizeof(int), compare_ints);
	std::qsort(FB, NB, sizeof(int), compare_ints);

	int trains_needed_a = 0;
	int a, b;
	a = b = 0;
	while (a < NA && b < NB) {
		if (SA[a] >= FB[b]) {
			++a, ++b;
		}
		else {
			++trains_needed_a;
			++a;
		}
	}

	if (a < NA) trains_needed_a += NA - a;

	int trains_needed_b = 0;
	a = b = 0;
	while (a < NA && b < NB) {
		if (SB[b] >= FA[a]) {
			++a, ++b;
		}
		else {
			++trains_needed_b;
			++b;
		}
	}

	if (b < NB) trains_needed_b += NB - b;

	cout << trains_needed_a << " " << trains_needed_b << endl;

}

int C;
int main() {
	cin >> C;
	for (int t = 1; t <= C; ++t) {
		cout << "Case #" << t << ": ";
		solvecase();
	}

	return 0;
}