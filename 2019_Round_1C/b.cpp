#include<algorithm>
#include<cmath>
#include<cstdint>
#include<cctype>
#include<iostream>
#include<iomanip>
#include<iterator>
#include<limits>
#include<map>
#include<memory>
#include<numeric>
#include<set>
#include<sstream>
#include<string>
#include<utility>
#include<vector>

using namespace std;

// I/O

struct input {
	int F;
};

template<typename T0, typename T1>
istream& operator>>(istream& is, pair<T0, T1>& x) {
  is >> x.first >> x.second;
  return is;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& x) {
  for(size_t i = 0; i < x.size(); ++i) is >> x[i];
  return is;
}

istream& operator>>(istream& is, input& in) {
  return is >> in.F;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1>& x) {
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm
const int FIGURES = 5;
const int SETS = 119;
bool solve(input const& in) {
	char shelf[FIGURES*SETS];
	std::fill(shelf, shelf+FIGURES*SETS, 0);
	// find first
	int count[5] = {0, 0, 0, 0, 0};
	char c;
	string sol;
	set<char> found;
	for (int j = 0; j < SETS; ++j) {
		cout << 1 + j * FIGURES << endl;
		cin >> c;
		if (c == 'N') return false;
		++count[c - 'A'];
		shelf[1 + j *FIGURES - 1] = c;
	}
	for (int i = 0; i < FIGURES; ++i) {
		if (count[i] < 24) {
			// cerr << count[0] << " "<< count[1] << " " << count[2] << " " << count[3] << " " << count[4] << endl;
			// cerr << char('A' + i) << endl;
			sol.push_back('A' + i);
			found.insert('A' + i);
			break;
		}
	}

	// find second
	std::fill(count, count+5, 0);
	for (int j = 0; j < SETS; ++j) {
		if (shelf[1 + j *FIGURES - 1] == sol[0]) {
			cout << 2 + j * FIGURES << endl;
			cin >> c;
			if (c == 'N') return false;
			++count[c - 'A'];
			shelf[2 + j *FIGURES - 1] = c;
		}
	}
	for (int i = 0; i < FIGURES; ++i) {
		if (count[i] < 6 && found.count('A' + i) == 0) {
			// cerr << count[0] << " "<< count[1] << " " << count[2] << " " << count[3] << " " << count[4] << endl;
			// cerr << char('A' + i) << endl;
			sol.push_back('A' + i);
			found.insert('A' + i);
			break;
		}
	}

	// find third
	std::fill(count, count+5, 0);
	for (int j = 0; j < SETS; ++j) {
		if (shelf[1 + j *FIGURES - 1] == sol[0] && shelf[2 + j *FIGURES - 1] == sol[1]) {
			cout << 3 + j * FIGURES << endl;
			cin >> c;
			if (c == 'N') return false;
			++count[c - 'A'];
			shelf[3 + j *FIGURES - 1] = c;
		}
	}
	for (int i = 0; i < FIGURES; ++i) {
		if (count[i] < 2 && found.count('A' + i) == 0) {
			// cerr << count[0] << " "<< count[1] << " " << count[2] << " " << count[3] << " " << count[4] << endl;
			// cerr << char('A' + i) << endl;
			sol.push_back('A' + i);
			found.insert('A' + i);
			break;
		}
	}

	// find fourth
	std::fill(count, count+5, 0);
	for (int j = 0; j < SETS; ++j) {
		if (shelf[1 + j *FIGURES - 1] == sol[0] && shelf[2 + j *FIGURES - 1] == sol[1] && shelf[3 + j *FIGURES - 1] == sol[2]) {
			cout << 4 + j * FIGURES << endl;
			cin >> c;
			if (c == 'N') return false;
			++count[c - 'A'];
			shelf[4 + j *FIGURES - 1] = c;
		}
	}
	for (int i = 0; i < FIGURES; ++i) {
		if (count[i] < 1 && found.count('A' + i) == 0) {
			// cerr << count[0] << " "<< count[1] << " " << count[2] << " " << count[3] << " " << count[4] << endl;
			// cerr << char('A' + i) << endl;
			sol.push_back('A' + i);
			found.insert('A' + i);
			break;
		}
	}

	set<char> all = {'A', 'B', 'C', 'D', 'E'};
	for (char c : sol) {
		auto it = all.find(c);
		if (it != all.end()) all.erase(it);
	}

	if (all.size() == 1) {
		for (char c : all) sol.push_back(c);
	}

	cout << sol << endl;
	// cerr << endl;
	cin >> c;
	return c == 'Y';
}

int main() {
  int T = 0; cin >> T;
  int F = 0; cin >> F;
  input in;	
  for (int t = 0; t < T; ++t) {
    if (!solve(in)) break;
  }
  return 0;
}
