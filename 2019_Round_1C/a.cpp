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
  vector<string> programs;
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
  int n;
	is >> n;
	in.programs.resize(n);
	return is >> in.programs;
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

char get_n(string const& s, size_t n) {
	if (n < s.size()) return s[n];
	return 0;
}

int as_int(char c) {
	if (c == 0) return 0;
	if (c == 'R') return 1;
	if (c == 'P') return 2;
	return 4;
}

char missing(int n) {
	if (n == 3) return 'P';
	if (n == 5) return 'S';
	if (n == 6) return 'R';
	if (n == 1) return 'P';
	if (n == 2) return 'S';
	if (n == 4) return 'R';
	if ((n & 1) == 0) return 'R';
	if ((n & 2) == 0) return 'P';
	if ((n & 4) == 0) return 'S';
	return 'N';
}

bool beats(char x, char y) {
	if (x == 'P' && y =='R') return true;
	if (x == 'R' && y =='S') return true;
	if (x == 'S' && y =='P') return true;
	return false;
}

void solve(input const& in) {
  	string sol;
  	size_t max = 0;
  	for (const auto& p : in.programs) {
  		if (p.size() > max) max = p.size();
  	}
  	bool beaten[255];
	std::fill(beaten, beaten+255, false);
	for (size_t i = 0; i < max; ++i) {
		int found = 0;
		for (size_t j = 0; j < in.programs.size(); ++j) {
			if (!beaten[j]) {
				found = found | as_int(get_n(in.programs[j], i));
			}
		}
		if (found == 7) {
			cout << "IMPOSSIBLE";
			return;
		}
		char result = missing(found);
		sol.push_back(result);
		for (size_t j = 0; j < in.programs.size(); ++j) {
			if(beats(result, get_n(in.programs[j], i))) {
				beaten[j] = true;
			}
		}
	}
	cout << sol;
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": ";
    solve(in);
    cout << endl;
  }
  return 0;
}
