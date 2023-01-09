// 2010  Round B Problem C - Your Rank is Pure
#include<algorithm>
#include<array>
#include<cmath>
#include<iostream>
#include<limits>
#include<numeric>
#include<utility>
#include<vector>

using namespace std;

// I/O

struct input {
	int n;
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
  return is >> in.n;
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

const size_t SIZE = 501;
const unsigned long MOD = 100003;
const unsigned long ZERO = 0;

template<typename T, size_t N>
void fill_row(array<array<T, N>, N> & matrix, const size_t n) {
	matrix[n][0] = 1;
	matrix[n][n] = 1;
	for (size_t k = 1; k < n; ++k) {
		matrix[n][k] = (matrix[n-1][k] + matrix[n-1][k-1]) % MOD;
	}
}

template<typename T, size_t N>
array<array<T, N>, N> create_combination_matrix() {
	array<array<T, N>, N> matrix;
	for (auto & row : matrix) row.fill(T{0});
	matrix[0][0] = 1;
	for (size_t n = 1; n < N; ++n)
		fill_row(matrix, n);
	return matrix;
}

template<typename T, size_t N>
struct Matrix {
	const array<array<T, N>, N> matrix;
	Matrix(array<array<T, N>, N> const& matrix ) : matrix(matrix) {}
	Matrix(array<array<T, N>, N> && matrix ) : matrix(matrix) {}
	T at(size_t x, size_t y) const {
		return matrix[x][y];
	}
};

template<typename T, size_t N>
array<array<T, N>, N> create_purity_matrix(Matrix<T, N> const& combination) {
	array<array<T, N>, N> matrix;
	for (auto & row : matrix) row.fill(T{0});
	matrix[2][1] = 1;
	for (size_t n = 3; n < N; ++n) {
		matrix[n][1] = 1; matrix[n][2] = 1;
		for (size_t k = 3; k < n; ++k) {
			for (size_t i = 1; i < k; ++i) {
				matrix[n][k] += (matrix[k][i] * combination.at(n - k - 1, k - i - 1)) % MOD ;
			}
		}
	}
	return matrix;
}

template<typename T, size_t N>
ostream& operator<<(ostream& o, array<array<T, N>, N> const& arr) {
	for (size_t i = 0; i < arr.size(); ++i) {
		for (size_t j = 0; j < arr[i].size(); ++j) {
			if (arr[i][j] == 0 && j > 0) break;
			o << arr[i][j] << " ";
		}
		o << endl;
	}
	return o;
}


void solve(input const& in, Matrix<unsigned long, SIZE> const& p) {
	cout << accumulate(p.matrix[in.n].begin(), p.matrix[in.n].end(), ZERO) % MOD;
}

int main() {
	Matrix<unsigned long, SIZE> c(create_combination_matrix<unsigned long, SIZE>());
	Matrix<unsigned long, SIZE> p(create_purity_matrix<unsigned long, SIZE>(c));
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    input in; cin >> in;
    cout << "Case #" << t+1 << ": ";
    solve(in, p);
    cout << endl;
  }
  return 0;
}
