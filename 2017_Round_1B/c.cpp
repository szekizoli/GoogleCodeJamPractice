#include<iostream>
#include<limits>
#include<vector>
#include<bitset>

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

template<typename T>
ostream& operator<<(ostream& os, vector<T>  const& x) {
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
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

path create_path(input const& in, vector<int> const& cp) {
  path p;
  for (size_t i = 0; i < cp.size()-1; ++i) {
    p.push_back(path_unit(in.distance[cp[i]][cp[i+1]], in.horses[cp[i]]));
  }
  return p;
}

vector<path> get_all_path(input const& in, size_t point_index) {
  int f = in.points[point_index].first - 1;
  int l = in.points[point_index].second - 1;
  vector<path> result;

  vector<int> cp;
  vector<int> visited(100, 0);
  cp.reserve(in.N);
  cp.push_back(f);
  ++visited[f];
  int fn = 0;
  int tn = 0;

  do {
  next:
    fn = cp.back();
    for (; tn < in.N; ++tn) {
      if(in.distance[fn][tn] != -1 && visited[tn] < 2) {
	cp.push_back(tn);
        if (tn == l) {
	  result.push_back(create_path(in, cp));
	  cp.pop_back();
        } else {
	  ++visited[tn];
	  tn = 0;
          goto next;
        }
      }
    }
    tn = cp.back() + 1;
    cp.pop_back();
    --visited[tn - 1];
  } while (!cp.empty());

  return result;
}

void solve(input const& in) {
  for (int q = 0; q < in.Q; ++q) {
    vector<path> paths = get_all_path(in, q);
    double min = numeric_limits<double>::max();
    for (path const& p : paths) {
      double r = get_travel_time(p);
      if (r < min) min = r;
    }
    cout.precision(6);
    cout << fixed << min;
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
