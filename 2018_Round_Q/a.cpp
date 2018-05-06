// 2018 Round Q Problem A
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

using num_t = unsigned long long;

struct input {
	num_t D;
	string P;
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
  return is >> in.D >> in.P;
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

vector<num_t> convert(string const& p) {
	num_t value = 1;
	vector<num_t> result;
	for (char c : p) {
		if (c == 'C') value *= 2;
		else          result.push_back(value);
	}
	return result;
}

void solve(input const& in) {
	vector<num_t> shoots = convert(in.P);
 	if (shoots.size() > in.D) {
		cout << "IMPOSSIBLE";
		return;
	}
	
	num_t sum = std::accumulate(begin(shoots), end(shoots), num_t(0));
	num_t swaps = 0;
	while (sum > in.D) {
		auto next_swap = std::lower_bound(begin(shoots), end(shoots), shoots.back());
		*next_swap = (*next_swap/2);
		++swaps;
		sum -= *next_swap;
	}
	cout << swaps;
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
