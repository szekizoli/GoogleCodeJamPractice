// 2018 Round 1A Problem B
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

using Time = unsigned long long;
using Bits = unsigned long long;

struct Cashier { 
	Bits M;
	Time S;
	Time P;
};

istream& operator>>(istream& i, Cashier& c) {
	return i >> c.M >> c.S >> c.P;
}

ostream& operator<<(ostream& o, Cashier const& c) {
	return o << "M= " << c.M << "; S=" << c.S << "; P=" << c.P;
}

struct Input {
	unsigned long long R;
  Bits B;
	unsigned long long C;
	vector<Cashier> cashiers;
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

istream& operator>>(istream& is, Input& in) {
  is >> in.R >> in.B >> in.C;
	in.cashiers.resize(in.C);
	return is >> in.cashiers;
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

Bits bitsWithin(Cashier c, Time time) {
	if (time < c.P) return 0;
	Bits bits = (time - c.P) / c.S;
	return std::min(bits, c.M);
}

struct mostWithin {
	Time time;
	bool operator()(Cashier const& lhs, Cashier const& rhs) {
		return bitsWithin(lhs, time) > bitsWithin(rhs, time);
	}
};

bool canPayWithin(Input & in, Time time) {
	std::sort(begin(in.cashiers), end(in.cashiers), mostWithin{time});
	Bits bits_left = in.B;
  unsigned long long robots_left = in.R;
	for (Cashier c : in.cashiers) {
		Bits bits_can_scan = std::min(bitsWithin(c, time), bits_left);
		if (bits_can_scan > 0) {
			bits_left -= bits_can_scan;
			--robots_left;
		}
		if (bits_left == 0 || robots_left == 0) break;
	}
	return bits_left == 0;
}

Time solve(Input & in) {
	Time lower{1};
	Time upper = Time{1};
	while(!canPayWithin(in, upper)) {
		upper *= 2;
	}
	if (upper == 1) return 1;
	lower = upper >> 1;
	Time n = lower + (upper - lower) / 2;
	do {
		if (canPayWithin(in, n)) {
			upper = n;
		} else {
			lower = n + 1;
		}
		n = (lower + upper) / 2;
	} while (upper > lower);
	return upper;	
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    Input in; cin >> in;
    cout << "Case #" << t+1 << ": " << solve(in) << endl;
  }
  return 0;
}
