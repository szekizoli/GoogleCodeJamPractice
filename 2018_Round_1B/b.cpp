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
  os << x.first << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

Num longestSeqFrom(vector<pair<Num, Num>> const& D, size_t i) {
	Num count = 1;
	Num second = 0;
	bool hasSecond = false;
	for (size_t j = i + 1; j < D.size(); ++j) {
		if (D[i].first == D[j].first || (hasSecond && second == D[j].second)) {
			++count;
		} else if(!hasSecond) {
			hasSecond = true;
			second = D[j].second;
			++count;
		}	else {
			break;
		}
	}
	return count;
}

pair<Num, Num> longestSeq(vector<pair<Num, Num>> const& D) {
	vector<Num> result(D.size()+1, 0);
	
	for (size_t i = 0; i < D.size(); ++i) {
		Num count = longestSeqFrom(D, i);
		result[count]++;
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
	if (in.S == 1) { cout << "1 1"; return; }
	vector<pair<Num, Num>> D;
	for (Sign s : in.signs) {
		D.push_back(make_pair(s.D+s.A, s.D-s.B));
	}
	auto r0 = longestSeq(D);
	for (auto & elem : D) {
		std::swap(elem.first, elem.second);
	}
	auto r1 = longestSeq(D);
	if (r0 > r1) {
		cout << r0.first << " " << r0.second;
	} else {
		cout << r1.first << " " << r1.second;
	}
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
