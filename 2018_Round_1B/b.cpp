// 2018 Round 1B Problem B
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

using Num = long long;

struct Sign {
	Num D, A, B;
};

istream& operator>>(istream& is, Sign & s) {
	return is >> s.D >> s.A >> s.B;
}

struct input {
	Num S;
	vector<Sign> signs;
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
	is >> in.S;
	in.signs.resize(in.S);
  return is >> in.signs;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1>& x) {
  os << x.first << " " << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

struct Dist {
	Num value;
	bool isSet;
};

struct Locations {
	Num m;
	Num n;
};

bool operator==(Dist const& a, Dist const& b) {
	return a.isSet && b.isSet && a.value == b.value;
}

bool operator!=(Dist const& a, Dist const& b) {
	return !(a == b);
}

struct Result {
	Num value = 0;
	Num count = 0;
	void addResult(Num v) {
		if (v < value) return;
		if (value == v) { ++count; }
		else            { count = 0; value = v; }
	}
};

struct Sequence {
	Dist M;
	Dist N;
	Num m_index;
	Num n_index;
	Num length;
}

bool equalOrNotSet(Sequence const& s, Num value) {
	return !s.M.isSet || value == s.M.value;
}

void setIfNotSet(Sequence &s, Num value) {
	if (!s.M.isSet) {
		s.M.value = value;
		s.M.isSet = true;
	}
}

Result findLongest(vector<Locations> const& D) {
	Result result;
	Sequence s_m {Dist{D[0].m, true}, Dist{0, false}, 0, 0, 1};
	Sequence s_n {Dist{0, false}, Dist{D[0].n, true}, 0, 0, 1};

	for (size_t i = 1; i < D.size(); ++i) {
		if (equalOrNotSet(s_m, D[i].m)) {
			setIfNotSet(s_m, D[i].m);
			++result.length;	
		}
	}

	return result;	
}

void solve(input const& in) {
	if (in.S < 3) { cout << in.S << " 1"; return; }

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
