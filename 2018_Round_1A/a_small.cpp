// 2018 Round 1A Problem A
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
	int R, C, H, V;
	vector<vector<bool>> board;
	vector<int> rows;
	vector<int> cols;
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
	is >> in.R >> in.C >> in.H >> in.V;
	in.rows.resize(in.R);
	in.cols.resize(in.C);
	char c;
	for (int i = 0; i < in.R; ++i) {
		in.board.push_back(vector<bool>());
		for (int j = 0; j < in.C; ++j) {
			do { cin >> c; } while(std::isspace(static_cast<unsigned char>(c)));
			in.board.back().push_back(c == '@');
			if (c == '@') {
				++in.rows[i];
				++in.cols[j];
			}
		}
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

int cut(vector<int> const& v, int sum, int from, int to) {
	int partial = 0;
  for (int i = from; i < to; ++i) {
		partial += v[i];
		if (partial == sum) return i;
	}
	return -1;
}

int cut(vector<vector<bool>> const& v, int sum, int from, int to) {
	vector<int> cols(v[0].size(), 0);
	for (int i = from; i < to; ++i) {
		for(int j = 0; j < v[i].size(); ++j) {
			cols[j] += v[i][j] ? 1 : 0;
		}
	}
	return cut(cols, sum/2, 0, cols.size());
}

void solve(input const& in) {
	int sum = accumulate(begin(in.rows), end(in.rows), 0);
	if (sum == 0) {
		cout << "POSSIBLE"; return;
	}
	int piece = (in.H+1)*(in.V+1);
	if (sum % piece !=0) {
		cout << "IMPOSSIBLE"; return;
	}
	int row_half = cut(in.rows, sum / (in.V+1), 0, in.rows.size());
	if (row_half == -1) {
		cout << "IMPOSSIBLE"; return;
	}
	int col_half = cut(in.board, sum / piece, 0, row_half + 1);
	if (col_half == -1) {
		cout << "IMPOSSIBLE"; return;
	}
	cout << "POSSIBLE"; return;
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
