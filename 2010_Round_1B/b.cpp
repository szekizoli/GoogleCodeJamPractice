// 2010  Round B Problem B - Picking Up Chicks
#include<algorithm>
#include<cmath>
#include<iostream>
#include<limits>
#include<utility>
#include<vector>

using namespace std;

// I/O

struct input {
	int N, K, B, T;
	vector<bool> items;
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
	is >> in.N >> in.K >> in.B >> in.T;
	vector<int> X(in.N);
	vector<int> V(in.N);
	is >> X >> V;
	for (size_t i = 0; i < V.size(); ++i) {
		in.items.push_back((in.B - X[i]) <= in.T*V[i]);
	}
  return is;
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

void solve(input & in) {
	auto ones = count(in.items.begin(), in.items.end(), true);
	if (ones < in.K) {
		cout << "IMPOSSIBLE";
		return;
	}
	unsigned swaps = 0;
	auto zero = find(in.items.rbegin(), in.items.rend(), false);
	auto one = find(zero, in.items.rend(), true);
	while (distance(in.items.rbegin(), zero) < in.K) {
		swaps += distance(zero, one);
		iter_swap(zero, one);
		zero = find(in.items.rbegin(), in.items.rend(), false);
		one = find(zero, in.items.rend(), true);
	}
		
	cout << swaps; 
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
