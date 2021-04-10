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
    int t, n, q;
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
  return is >> in.t >> in.n >> in.q;
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

using I = vector<int>::iterator;

int T = 0, Q = 0;

int ask(int a, int b, int c) {
	++Q;
	cerr << "ask (" << T << ", "<< Q << "): " <<  a << " " << b << " " << c << endl;
  cout << a << " " << b << " " << c << endl;
  cin >> a;
	cerr << "answer: " << a << endl;
	return a;
}

pair<I, I> part(I f, I l) {
	vector<int> va;
	vector<int> vb;
  vector<int> vc;

	auto first = f;
	int x = *f; ++f;
	int y = *f; ++f;

	while (f != l) {
		int a = ask(x, y, *f);
		if (a == -1) return make_pair(l, l);
		if (a == x) va.push_back(*f);
		if (a == *f) vb.push_back(*f);
		if (a == y) vc.push_back(*f);
		++f;
	}

	I i1 = std::copy(begin(va), end(va), first);
	*i1 = x;
  I i2 = std::copy(begin(vb), end(va), i1+1);
	*i2 = y;
	std::copy(begin(vc), end(vc); i2+1);

	return make_pair(i1, i2);
}

pair<I, bool> place(int n, I f, I l) {
	auto dist = std::distance(f, l);
	cerr << "dist: " << dist << endl;
  I mid = f + (dist-1) / 2;
	int a = ask(n, *mid, *(mid+1));
	if (a == -1) {
		return make_pair(f, false);
	}
	if (a == n) {
		return make_pair(mid + 1, true);
	}
  if (a == *mid) {
		if (dist <= 2) return make_pair(mid, true);
		return place(n, f, mid);
	}

	if (dist <= 2)  return make_pair(mid + 2, true);
	return place(n, mid, l);
}

// Algorithm
bool solve(input const& in) {
  vector<int> v = {1, 2, 3};
  int a = ask(1, 2, 3);
  if (a == -1) { return true; }
  if (a != 2) { std::swap(v[1], v[a-1]); }
  for (int i = 3; i < in.n; ++i) {
		 cerr << "v: " <<  v << endl << endl;
     pair<I, bool> p = place(i + 1, begin(v), end(v));
     if (!p.second) { return true; }
     v.insert(p.first, i+1);
  }
	cerr << "guess: " << v << endl;
  cout << v << endl;
	cin >> a;
	cerr << "answer: " << a << endl;
  return a != 1;
}

int main() {
  input in; cin >> in;
	cerr << in.t << " " << in.n << " " << in.q << endl;
  for (int t = 0; t < in.t; ++t) {
		++T;
  	cerr << "test case: " << t+1 << endl;
    bool stop = solve(in);
    if (stop) { break; }
  }
  return 0;
}
