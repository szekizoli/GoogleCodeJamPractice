// 2017 Round 1B Problem C

#include<iostream>
#include<limits>
#include<vector>
#include<bitset>

using namespace std;

// <distance, speed>
typedef pair<long long, int> horse;
typedef pair<int, int> query;

struct input {
  int N;
  int Q;
  vector< vector<long long> > distance;
  vector<horse> horses;
  vector<query> queries;
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
  is >> in.N >> in.Q;
  in.horses.resize(in.N);
  in.distance.resize(in.N, vector<long long>(in.N, -1));
  in.queries.resize(in.Q);
  is >> in.horses >> in.distance >> in.queries;
  return is;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T>  const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

template<typename T>
void floyd_warshall(vector< vector<T> > &g) {
  for (auto & v : g) for(T& i : v) if (i == T(-1)) i = numeric_limits<T>::max();
  for (size_t i = 0; i < g.size(); ++i) g[i][i] = 0;
  
  for (size_t k = 0; k < g.size(); ++k) {
    for (size_t i = 0; i < g.size(); ++i) {
      for (size_t j = 0; j < g.size(); ++j)
	if (g[i][j] - g[i][k] >  g[k][j]) g[i][j] = g[i][k] + g[k][j];
    }
  }  
}

vector< vector<double> > create_time_graph(input const& in) {
  vector< vector<double> > m (in.N, vector<double>(in.N, numeric_limits<double>::max()));
  for (size_t i = 0; i < in.N; ++i) {
    for (size_t j = 0; j < in.N; ++j) {
      if (in.distance[i][j] != numeric_limits<long long>::max() && in.distance[i][j] <= in.horses[i].first) {
	m[i][j] = in.distance[i][j] / static_cast<double>(in.horses[i].second);
      }
    }
  }
  return m;
}

void solve(input & in) {
  floyd_warshall<long long>(in.distance);
  auto time_graph = create_time_graph(in);
  floyd_warshall<double>(time_graph);
  for (int q = 0; q < in.Q; ++q) {
    cout.precision(6);
    cout << fixed << time_graph[in.queries[q].first-1][in.queries[q].second-1];
    if (q < in.Q -1) cout << " ";
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
