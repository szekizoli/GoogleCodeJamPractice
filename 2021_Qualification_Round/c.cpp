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
#include<random>
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
  I i2 = std::copy(begin(vb), end(vb), i1+1);
	*i2 = y;
	std::copy(begin(vc), end(vc), i2+1);

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

bool sort_small_max(I f, I l, int max) {
	while (f != l) {
		I n = f;
	  while ((n+1) != l) {
 	    int a = ask(max, *n, *(n+1));
		  if (a == -1) return false;
		  if (a == *n) std::swap(*n, *(n+1));
		  ++n;
	  }
	  --l;
  }
  
	return true;
}

bool sort_small_min(I f, I l, int min) {
	while (f != l) {
		I n = f;
	  while ((n+1) != l) {
 	    int a = ask(min, *n, *(n+1));
		  if (a == -1) return false;
		  if (a == *(n+1)) std::swap(*n, *(n+1));
		  ++n;
	  }
	  --l;
  }
  
	return true;
}

bool sort_first_2_max(I f, int max) {
	int a = ask(max, *f, *(f+1));
	if (a == -1) return false;
	if (a == *f) std::swap(*f, *(f+1));
	return true;
}

bool sort_first_2_min(I f, int min) {
	int a = ask(min, *f, *(f+1));
	if (a == -1) return false;
	if (a != *f) std::swap(*f, *(f+1));
	return true;
}

bool sort_max_v2(I f, I l, int max) {
	bool ok = sort_first_2_max(f, max);
  if (!ok) return false;
	if (distance(f, l) == 2) return true;
	ok = sort_first_2_max(f+1, max);
	if (!ok) return false;
	if (distance(f, l) == 3) return true;
	for (I n = f + 3; n != l; ++n) {
		pair<I, bool> p = place(*n, f, n);
  	if (!p.second) { return true; }
		std::rotate(p.first, n, n);
	}
	return true;
}

const int PART_LIMIT = 5;

// Algorithm
bool sort(I f, I l) {
	pair<I, I> p = part(f, l);
	if (p.first == l) return false;
	int d0 = distance(f, p.first);
	if (d0 > PART_LIMIT) {
		bool ok = sort_first_2_max(f, *p.first);
		if (!ok) return false;	
    ok = sort(f, p.first);
		if (!ok) return false;
	} else if (d0 > 1) {
	  bool ok = sort_max_v2(f, p.first, *p.first);
		if (!ok) return false;
  }

	int d1 = distance(p.first, p.second);
	if (d1 > PART_LIMIT) {
		bool ok = sort(p.first, p.second);
		if (!ok) return false;
	} else if (d1 > 1) {
	  bool ok = sort_small_min(p.first+1, p.second, *p.first);
		if (!ok) return false;
  }

	int d2 = distance(p.second, l);
	if (d2 > PART_LIMIT) {
		bool ok = sort(p.second, l);
		if (!ok) return false;
	} else if (d2 > 1) {
	  bool ok = sort_small_min(p.second+1, l, *p.second);
		if (!ok) return false;
  }
	return true;
}

bool solve2(input const& in) {
	vector<int> v(in.n, 0);
	std::iota(begin(v), end(v), 1);
  std::random_device rd;
  std::mt19937 g(rd());
	std::shuffle(begin(v), end(v), g);
	bool ok = sort(begin(v), end(v));
	if (!ok) return false;
	cerr << "guess: " << v << endl;
  cout << v << endl;
	int a; cin >> a;
	cerr << "answer: " << a << endl;
  return a != 1;
}


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
    bool stop = solve2(in);
    if (stop) { break; }
  }
  return 0;
}
