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
	Num val;
	bool isSet;
};

struct Locations {
	Num m;
	Num n;
};

bool operator==(Dist const& a, Dist const& b) {
	return a.isSet && b.isSet && a.val == b.val;
}

bool operator!=(Dist const& a, Dist const& b) {
	return !(a == b);
}

Num longestSeqFromM(vector<Locations> const& D, size_t i) {
	Num count = 1;
	Dist M {D[i].m, true};
	Dist N {0, false};
	for (size_t j = i + 1; j < D.size(); ++j) {
		if (M.val == D[j].m || (N.isSet && N.val == D[j].n)) {
			++count;
		} else if(!N.isSet) {
			N = {D[j].n, true};
			++count;
		}	else {
			break;
		}
	}
	return count;
}

Num longestSeqFromN(vector<Locations> const& D, size_t i) {
	Num count = 1;
	Dist M {0, false};
	Dist N {D[i].n, true};
	for (size_t j = i + 1; j < D.size(); ++j) {
		if (N.val == D[j].n || (M.isSet && M.val == D[j].m)) {
			++count;
		} else if(!M.isSet) {
			M = {D[j].m, true};
			++count;
		}	else {
			break;
		}
	}
	return count;
}

pair<Num, Num> longestSeq(vector<Locations> const& D) {
	vector<Num> result(D.size()+1, 0);
	
	for (size_t i = 0; i < D.size(); ++i) {
		Num countM = longestSeqFromM(D, i);
		Num countN = longestSeqFromN(D, i);
		result[std::max(countM, countN)]++;
	}
	for (Num i = result.size()-1; i >= 0; --i) {
		if (result[i] > 0) {
			return make_pair(i, result[i]);
		}
	}
	cerr << "ERROR" << endl;
	return make_pair(0, 0);	
}

void solve(input const& in) {
	if (in.S < 3) { cout << in.S << " 1"; return; }
	vector<Locations> D;

	for (Sign s : in.signs) {
		D.push_back(Locations{s.D+s.A, s.D-s.B});
	}
	auto r = longestSeq(D);
	cout << r;
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
