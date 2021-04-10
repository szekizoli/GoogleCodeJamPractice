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
	vector<bitset<10000>> v;
	vector<int> c_p;
	vector<int> c_q;
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
	for (int i = 0; i < 100; ++i) {
		string s; is >> s;
		in.v.emplace_back(bitset<10000>(s));
	}
  return is;

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
	vector<int> c_p(100, 0);
	vector<int> c_q(10000, 0);
	for (int i = 0; i < 100; ++i) {
		c_p[i] = in.v[i].count();
		for (int j = 0; j < 10000; ++j) {
		  c_q[j] += in.v[i][j];
		}
	}
	
	auto it = max_element(begin(c_p), end(c_p));
	cout << endl << c_p << endl;
  cout << distance(begin(c_p), it) + 1; 
}

int main() {
  int T = 0, P = 0; cin >> T >> P;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": ";
    solve(in);
    cout << endl;
  }
  return 0;
}
