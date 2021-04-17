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
	int m;
	vector<pair<int, int>> v;
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
	is >> in.m;
	in.v.resize(in.m);
  return is >> in.v;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, const pair<T0, T1>& x) {
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

using val_t = unsigned long long;
const val_t MAX = 49900;
const int MAX_ITEM = 15;

val_t eval(vector<int> const& ps, int bitmask) {
	val_t sum = 0;
	val_t prd = 1;
	int prd_cnt = 0;
	for (int i = 0; i < ps.size(); ++i) {
		if (bitmask & 1) { sum = sum + ps[i]; }
		else             { prd = prd * ps[i]; ++prd_cnt; }
		bitmask >>= 1;

		if (prd_cnt > MAX_ITEM) return 0;
		if (sum > MAX || prd > MAX) return 0;
	}
	return sum == prd ? sum : 0;
}

val_t eval2(vector<int> const& ps) {
	vector<pair<val_t, val_t>> ss {{0, 1}};
	for (int p : ps) {
		size_t size = ss.size();
		for (size_t i = 0; i < size; ++i) {
			auto pr = ss[i];
			if (pr.first + p < MAX) {
				ss[i].first = pr.first + p;
				if (pr.second * p < MAX) {
					ss.push_back({pr.first, pr.second*p});
				}
			} else if (pr.second * p < MAX) {
				ss[i].second = pr.second * p;
			}
		}
	}

	val_t mx = 0;
	for (const auto pr: ss) {
		if (pr.first != pr.second) continue;
		mx = std::max(mx, pr.first);
	}
	return mx;
}

void solve(input const& in) {
	vector<int> ps;
	for (const auto p : in.v) {
		ps.insert(end(ps), p.second, p.first);
	}
	if (ps.size() > 100) { cout << 0; return; }
	// Seperate numbers in two groups in all possible ways
	cout << eval2(ps);
  /*
 	val_t limit = (1 << ps.size()) - 1;
	val_t mx = 0;
	for (val_t i = 1; i < limit; ++i) {
		val_t v = eval(ps, i);
		mx = std::max(mx, v);
	}
	cout << mx;*/
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
