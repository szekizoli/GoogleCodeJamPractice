// 2018 Round 1B Problem A
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

struct input {
	Num N, L;
	vector<Num> choice;
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
	is >> in.N >> in.L;
	in.choice.resize(in.L);
  return is >> in.choice;
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

double getFraction(Num C, Num N) {
	double one = static_cast<double>(C)*(100.0/static_cast<double>(N));
	return one - std::floor(one);
}

Num countForFraction(double fraction, double from) {
	Num count = 0;
	while (from < 0.5) {
		from += fraction;
		//cout << "CFF " << from << " " << fraction << endl;
		++count;
	}	
	return count;
}

Num countOne(Num C, Num N) {
	if (C % N == 0) return 0;
	double F = getFraction(C, N);
	return F >= 0.5 ? 1 : (F == 0 ? 0 : -1);
}

void solve(input & in) {
	Num R = in.N - std::accumulate(begin(in.choice), end(in.choice), Num{0});
	double F = getFraction(1, in.N);
	if (F == 0) { cout << "100"; return; }
	vector<pair<Num, size_t>> counts;
	for (size_t i = 0; i < in.choice.size(); ++i) {
		Num CFF = countForFraction(F, getFraction(in.choice[i], in.N));
		counts.push_back(make_pair(CFF, i));
	}
	std::sort(begin(counts), end(counts));
	Num CFF = countForFraction(F, 0.0);
	for (auto& p : counts) {
		Num n = in.choice[p.second];
		if (p.first > 0 && p.first <= CFF && p.first <= R) {
			in.choice[p.second] += p.first;
			R -= p.first;
		}	
	}
	if (R > 0) {
		while(R >= CFF) {
			in.choice.push_back(CFF);
			R -= CFF;
		}
		if (R > 0) in.choice.push_back(R);
	}
	Num result = 0;
	for (Num C : in.choice) {
		result += std::round(static_cast<double>(C)*(100.0/static_cast<double>(in.N)));
	}
	cout << result;
}

/*void bla(input const& in) {
	Num R = 0;
	cout << "R=" << R << endl;
	double fraction = getFraction(in.N);
	cout << "F=" << fraction << endl;
	if (fraction == 0) { cout << "100"; return; }
	Num C = countForFraction(fraction);
	cout << "C=" << C << endl;
	vector<pair<Num, Num>> current;
	long long currCount = 0;
	for(Num choice : in.choice) {
		Num c = countOne(C, in.N, choice);
		currCount += c;
		if (c != 1) {
			current.push_back(make_pair(choice % in.N, c));
		}
	}
	cout << "Current count=" << currCount << endl;
	std::sort(begin(current), end(current), std::greater<pair<Num, Num>>());
	Num zeros = 0;
	Num ones = 0;
	for (auto &p : current) {
		if (R <= 0) break;
		Num missing = C - p.first;
		cout << "R= " << R << ", M=" << missing << endl;
		if (missing <= R) {
			currCount += (1 - p.second);
			R -= C;
			p.second = 1;
		}
		if (p.second == 0) ++zeros;
		if (p.second == -1) ++ones;
	}
	if (R > 0 && ones == 0) {
		if (zeros == 0) --currCount;
		else            currCount -= 2;	
	}
	cout << 100 + currCount;	
}*/

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
