// 2018 Round Q Problem C
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
	int A;
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
  return is >> in.A;
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

pair<int, int> digging_area(int a) {
	if (a <= 9) return make_pair(1, 1);
	int s = static_cast<int>(sqrt(a));
	if (s*s >= a) return make_pair(s-2, s-2);
	if (s*(s+1) >= a) return make_pair(s-2, s-1);
	return make_pair(s-1, s-1);
}

bool done(pair<int, int> respond) {
	return respond.first == 0 && respond.second == 0;
}

bool error(pair<int, int> respond) {
	return respond.first == -1 && respond.second == -1;
}

bool is_filled(vector<vector<bool>> const& matrix, pair<int, int> cell) {
	int x = cell.first;
	int y = cell.second;
	return matrix[x-1][y-1] && matrix[ x ][y-1] && matrix[x+1][y-1] &&
				 matrix[x-1][ y ] && matrix[ x ][ y ] && matrix[x+1][ y ] &&
				 matrix[x-1][y+1] && matrix[ x ][y+1] && matrix[x+1][y+1];
}

void solve(input const& in) {
	vector<vector<bool>> matrix(1001, vector<bool>(1001, false));
	pair<int, int> respond;
	pair<int, int> area = digging_area(in.A);
	pair<int, int> current(2, 2);
	int limit_x = 2 + area.first - 1;
	int limit_y = 2 + area.second - 1;
	cout << current << endl;
	cin >> respond;
	while (!done(respond)){
		matrix[respond.first][respond.second] = true;
		if (is_filled(matrix, current)) {
			if (current.second < limit_y) current.second = min(current.second + 3, limit_y);
			else current = make_pair(min(current.first + 3, limit_x), 2);
		}
		cout << current << endl;
		cin >> respond;
	}
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    solve(in);
  }
  return 0;
}
