#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void read_input(vector<int>& tpp, vector<int>& tpc, int m) {
	for (int i = 0; i < m; ++i) {
  	int p, b; cin >> p >> b;
  	++tpp[p-1];
		++tpc[b-1];
	}
}

int calculateRidesPerCustomer(vector<int> const& tpc) {
  return *max_element(begin(tpc), end(tpc));
}

int calculateRidesPerPosition(vector<int> const& tpp) {
  size_t rides = 0;
  size_t sum = 0;
  for (size_t i = 0; i < tpp.size(); ++i) {
    sum += tpp[i];
    rides = max(rides, (sum+i)/(i+1));
  }
  return rides;
}

void solve(const int n, const int c, const int m) {
  vector<int> tpp(n, 0); // tickets per position
  vector<int> tpc(c, 0); // tickets per customer
  read_input(tpp, tpc, m);
  int rpc = calculateRidesPerCustomer(tpc);
  int rpp = calculateRidesPerPosition(tpp);
  int rides = max(rpc, rpp); 
  int promotions = accumulate(begin(tpp), end(tpp), 0, [rides](auto a, auto b) { return a + max(0, b - rides); });
  cout << rides << " " << promotions;
}

int main() {
  int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, C, M; cin >> N >> C >> M;
    cout << "Case #" << t+1 << ": ";
    solve(N, C, M);
    cout << endl;
  }
  return 0;
}
