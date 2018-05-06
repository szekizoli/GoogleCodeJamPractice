// 2018 Round Q Problem B
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
	int N;
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
  return is >> in.N;
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

void solve(input const& in) {
	int L = (in.N/2)*2;
	vector<int> odd(L+1, numeric_limits<int>::max());
	vector<int> even(L+1, numeric_limits<int>::max());
	bool isNOdd = in.N % 2 == 1;
	for (int i = 0; i < L; i += 2) {
		cin >> odd[i] >> even[i];
	}
	if (isNOdd) {
		cin >> odd[L];
	}
	std::sort(begin(odd), end(odd));
	std::sort(begin(even), end(even));
	// merge
	for (int i = 0; i < L; i++) {
		if (odd[i] > even[i]) {
			cout << 2*i; return;
		}
		if (even[i] > odd[i+1]) {
			cout << 2*i+1; return;
		}		
	}
	cout << "OK";
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
