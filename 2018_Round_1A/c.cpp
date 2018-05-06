// 2018 Round 1A Problem C
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

using Num = unsigned long long;

struct Cookie {
	Num W;
	Num H;
};

istream& operator>>(istream& i, Cookie& c) {
	return i >> c.W >> c.H;
}

struct input {
	Num N, P;
	vector<Cookie> cookies;
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
  is >> in.N >> in.P;
	in.cookies.resize(in.N);
	return is >> in.cookies;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1> const& x) {
  os << x.first << ' ' << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

// Algorithm

template<typename Iterator>
struct iteratorPredicate {
	Iterator it;
	template<typename T>
	bool operator()(T const& x) {
		return *(it++);
	}
};

bool intersects(pair<double, double> a, pair<double, double> b) {
	return a.second >= b.first;
}

void merge(pair<double, double> &a, pair<double, double> const& b) {
	a.second = a.second + b.second;
}

void merge(vector<pair<double, double>> &intervals) {
	std::sort(begin(intervals), end(intervals));
	vector<bool> dirty(intervals.size(), false);
	for(size_t i = 0; i < intervals.size() - 1; ++i) {
		if (dirty[i]) continue;
		for(size_t j = i + 1; j < intervals.size() && intersects(intervals[i], intervals[j]); ++j) {
			dirty[j] = true;
			merge(intervals[i], intervals[j]);
		}
	}
	auto last = remove_if(begin(intervals), end(intervals), iteratorPredicate<vector<bool>::const_iterator>{begin(dirty)});
	intervals.erase(last, end(intervals));
}

vector<pair<double, double>> createIntervals(input const& in, double& goal, double& sum_min, double& sum_max) {
	vector<pair<double, double>> intervals;
	for (Cookie c : in.cookies) {
		goal -= 2*(c.W+c.H);
		double min_val = 2*std::min(c.W, c.H);
		double max_val = 2*sqrt(c.W*c.W + c.H*c.H);
		sum_min += min_val;
		sum_max += max_val;
		intervals.push_back(make_pair(min_val, max_val));
	}
	return intervals;
}

double solve(input const& in) {
	double sum = 0;
	double goal = static_cast<double>(in.P);
	double sum_min = 0;
	double sum_max = 0;
  auto intervals = createIntervals(in, goal, sum_min, sum_max);	
	if (goal < 0.000001) {
		return static_cast<double>(in.P);
	}
	if (goal > sum_max) {
		return static_cast<double>(in.P) - goal + sum_max;
	}
	if (goal >= sum_min) {
		return static_cast<double>(in.P);
	}
	merge(intervals);
	for(size_t i = 0; i < intervals.size() - 1; ++i) {
		intervals[i+1].second += intervals[i].second;
	}
	cout << intervals << endl << "goal=" << goal << endl;
	if (intervals.empty() || intervals.front().first > goal) {
		return static_cast<double>(in.P) - goal;
	}
	// fix this
	auto it = begin(intervals);
	while(it != end(intervals) && goal >= it->first) ++it;
	--it;
	if (it->first <= goal) goal -= std::min(goal, it->second);
	return static_cast<double>(in.P) - goal;
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": ";
		cout.precision(6);
    cout << std::fixed << solve(in) << endl;
  }
  return 0;
}
