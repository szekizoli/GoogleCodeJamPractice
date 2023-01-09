// 2015 Round 1B Problem C
// https://code.google.com/codejam/contest/8224486/dashboard#s=p2
#include <iostream>
#include <vector>

using namespace std;

struct start_pos
{
  int degree;
  int hikers;
  int minute;
};

struct input
{
  vector<start_pos> sps;
};

istream& operator>>(istream& i, start_pos& sp)
{
  cin >> sp.degree >> sp.hikers >> sp.minute;
  return i;
}

template<typename T0, typename T1>
istream& operator>>(istream& is, pair<T0, T1>& x)
{
  is >> x.first >> x.second;
  return is;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& x)
{
  for(size_t i = 0; i < x.size(); ++i) is >> x[i];
  return is;
}

istream& operator>>(istream& is, input& in)
{
  int n; cin >> n;
  in.sps.resize(n);
  cin >> in.sps;
  return is;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1>& x)
{
  os << x.first << " " << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x)
{
  for(size_t i = 0; i < x.size(); ++i) os << x[i] << " ";
  return os;
}

double time(int degree, int minute)
{
  return (((double)minute)*(360-degree))/360.0;
}

pair<int, int> slower(input const& in)
{
  if (in.sps.size() == 1) return make_pair(in.sps[0].degree, in.sps[0].minute+1);
  if (in.sps[0].minute < in.sps[1].minute)
    return make_pair(in.sps[1].degree, in.sps[1].minute);
  else
    return make_pair(in.sps[0].degree, in.sps[0].minute);
}

pair<int, int> faster(input const& in)
{
  if (in.sps.size() == 1) return make_pair(in.sps[0].degree, in.sps[0].minute);
  if (in.sps[0].minute < in.sps[1].minute)
    return make_pair(in.sps[0].degree, in.sps[0].minute);
  else
    return make_pair(in.sps[1].degree, in.sps[1].minute);
}

int solve(input const& in)
{
  if (in.sps.size() == 1) {
    return 0;
  }
  
  auto slower_hiker = slower(in);
  auto faster_hiker = faster(in);
  double slower_time = time(slower_hiker.first, slower_hiker.second);
  double faster_time = time(faster_hiker.first, faster_hiker.second);
  return (slower_time < double(faster_hiker.second) + faster_time) ? 0 : 1;
}

int main()
{
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    cout << "Case #" << t+1 << ": ";
    input in;
    cin >> in;
    cout << solve(in) << endl;
  }
  return 0;
}
