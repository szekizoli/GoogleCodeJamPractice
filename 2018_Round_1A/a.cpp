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

template<typename T>
bool operator==(vector<T> const& lhs, vector<T> const& rhs) {
	if (lhs.size() != rhs.size()) return false;
	for (size_t i = 0; i < lhs.size(); ++i) {
		if (lhs[i] != rhs[i]) return false;
	}
	return true;
}

template<typename T>
bool operator!=(vector<T> const& lhs, vector<T> const& rhs) {
	return !(lhs == rhs);
}	
// Algorithm

vector<int> cuts(vector<int> const& chips, int sum) {
	vector<int> result;
	int partial = 0;
	for(int i = 0; i < chips.size(); ++i) {
		partial += chips[i];
		if (partial == sum) { result.push_back(i+1); partial = 0; }
	}
	if (partial == sum) result.push_back(chips.size());
	else if(!result.empty()) result.back() = chips.size();
	return result;
}

void count_chips(vector<bool> chips_row, vector<int> const& col_cut, vector<int> & result) {
	size_t col_i = 0;
	for (size_t i = 0; i < chips_row.size(); i++) {
		if (i == col_cut[col_i]) ++col_i;
		if (chips_row[i]) ++result[col_i];
	}
}

bool is_valid_result(vector<int> const& result, int sum) {
	return std::all_of(begin(result), end(result), std::bind(std::equal_to<int>(), std::placeholders::_1, sum));
}

bool is_cut_valid(vector<vector<bool>> const& chips, vector<int> const& row_cut, vector<int> const& col_cut, int sum) {
	vector<int> result(col_cut.size(), 0);
	size_t row_cut_i = 0;
	for(size_t r = 0; r < chips.size(); ++r) {
		if (r == row_cut[row_cut_i]) {
			if (!is_valid_result(result, sum)) {
				return false;
			}
			std::fill(begin(result), end(result), 0);
			++row_cut_i;
		}
		count_chips(chips[r], col_cut, result);
	}
	return is_valid_result(result, sum);
}

void solve(input const& in) {
	int sumChips = accumulate(begin(in.rows), end(in.rows), 0);
	if (sumChips == 0) {
		cout << "POSSIBLE"; return;
	}
	int piece = (in.H+1)*(in.V+1);
	if (sumChips % piece != 0) {
		cout << "IMPOSSIBLE"; return;
	}
	vector<int> row_cuts = cuts(in.rows, sumChips / (in.H+1));
	if (row_cuts.size() !=  in.H + 1) {
		cout << "IMPOSSIBLE"; return;
	}
	vector<int> col_cuts = cuts(in.cols, sumChips / (in.V+1));
	if (col_cuts.size() !=  in.V + 1) {
		cout << "IMPOSSIBLE"; return;
	}
	if (is_cut_valid(in.board, row_cuts, col_cuts, sumChips / piece)) 
		cout << "POSSIBLE";
	else
		cout << "IMPOSSIBLE";
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
