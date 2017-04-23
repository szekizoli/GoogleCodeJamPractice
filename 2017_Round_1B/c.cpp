#include<iostream>
#include<limits>
#include<vector>

using namespace std;

// <distance, speed>
typedef pair<int, int> horse;
typedef pair<int, int> point;

struct input {
  int N;
  int Q;
  vector< vector<int> > distance;
  vector<horse> horses;
  vector<point> points;
};

template<typename T>
istream& operator>>(istream& is, pair<T, T>& x) {
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
  in.distance.resize(in.N, vector<int>(in.N, -1));
  in.points.resize(in.Q);
  is >> in.horses >> in.distance >> in.points;
  return is;
}

struct path_unit {
  int distance;
  horse h;
  path_unit(int d = 0, horse h = horse(0, 0)) : distance(d), h(h) {}
  path_unit(path_unit const& x) = default;
  path_unit(path_unit && x) = default;
  path_unit& operator=(path_unit const& x) = default;
  path_unit& operator=(path_unit && x) = default;
};

typedef vector<path_unit> path;

double get_travel_time(path const& p) {
  vector<double> best_from(p.size() + 1, std::numeric_limits<double>::max());
  best_from[p.size()] = 0;

  for (int s = p.size() - 1; s >= 0; --s) {
    double distance = 0;
    for (int m = s; m < p.size(); ++m) {
      distance += p[m].distance;
      if (distance <= p[s].h.first) {
	best_from[s] = min(best_from[s], distance / double(p[s].h.second) + best_from[m + 1]);
      }
    }
  }

  return best_from[0];
}

path to_path(input const& in) {
  path p;
  for (size_t i = 0; i < in.N-1; ++i) {
    p.push_back(path_unit(in.distance[i][i+1], in.horses[i]));
  }
  return p;
}

void solve(input const& in) {
  cout.precision(6);
  cout << fixed << get_travel_time(to_path(in));
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
