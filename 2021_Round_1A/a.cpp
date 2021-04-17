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

using val_t = string;
struct input {
	int n;
	vector<val_t> v;
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
	is >> in.n;
	in.v.resize(in.n);
  return is >> in.v;
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

struct counter {
	val_t v;
	int c;

	counter inc() { add(); return *this; }
	void add() { add('0'); }
	void add(char ch) { v.push_back(ch); ++c; }

	counter inc_times(int t) {
		while(t-- > 0) add();
		return *this;
	}
};


int cmp(val_t a, val_t b) {
	for (int i = 0; i < a.size() && i < b.size(); ++i) {
		if (a[i] < b[i]) return -1;
		if (a[i] > b[i]) return 1;
	}
	return 0;
}

counter append(val_t a, val_t b) {
	counter c {b, 0};
	int comp = cmp(a, b);

	if (a.size() == b.size()) {
		if (comp < 0) return c;
		return c.inc();
	}

	if (comp < 0) {
		return c.inc_times(a.size() - b.size());
	} 

	if (comp > 0) {
		return c.inc_times(a.size() - b.size() + 1);
	}

	int idx = -1;
	for (int i = a.size() - 1; i >= b.size(); --i) {
		if (a[i] < '9') { idx = i; break; }
	}

  if (idx == -1) {
		return c.inc_times(a.size() - b.size() + 1);
	}

	for (int i = b.size(); i < a.size(); ++i) {
		if (i == idx) { c.add(a[i] + 1); }
		else if (i < idx){ c.add(a[i]); }
		else { c.add(); }
	}
	return c;
}

void solve(input const& in) {
	int count = 0;
	val_t f = in.v[0];
	for (int i = 1; i < in.v.size(); ++i) {
		auto p = append(f, in.v[i]);
		f = p.v;
		count += p.c;
	}
	cout << count;
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
