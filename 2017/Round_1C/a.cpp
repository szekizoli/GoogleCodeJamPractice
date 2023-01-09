// 2017  Round 1C Problem A
#include<algorithm>
#include<cmath>
#include<iostream>
#include<limits>
#include<utility>
#include<vector>

using namespace std;

// I/O

typedef long long Num;

struct input {
  Num N, K;
  vector< pair<Num, Num> > p; // pancakes
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
  is >> in.N >> in.K;
  in.p.resize(in.N);
  is >> in.p;
  return is;
}

template<typename T0, typename T1>
ostream& operator<<(ostream& os, pair<T0, T1> const& x) {
  os << x.first << ' ' << x.second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> const& x) {
  for(const T& t : x) os << t << " ";
  return os;
}


// Algorithm

Num side_area(const pair<Num, Num>& p) {
  return 2*p.first*p.second;
}

Num top_area(const pair<Num, Num>& p) {
  return p.first*p.first;
}

template<typename T>
struct side_greater{
constexpr bool operator()(const pair<T, T> &lhs, const pair<T, T> &rhs) const 
 {
   return side_area(lhs) > side_area(rhs);
   //return lhs.second == rhs.second ? lhs.first > rhs.first : lhs.second > rhs.second;
 }
};

template<typename T>
struct height_sum {
  T operator()(T a, pair<T, T> const&  b) {
    //cout << a << " " << b << ' ' << side_area(b) << endl;
    return a + side_area(b);
  }
};

void solve(input & in) {
  sort(begin(in.p), end(in.p), side_greater<Num>());
  //cout << in.p << endl;
  auto it = max_element(begin(in.p), end(in.p)); // max radius
  if (it - begin(in.p) >= in.K) {
    auto it1 = max_element(begin(in.p), begin(in.p) + in.K);
    //cout << *it1 << endl;
    Num r0 = side_area(*it) + top_area(*it); // choosing the largest radius
    Num r1 = side_area(in.p[in.K-1]) + top_area(*it1);
    if (r0 > r1) {
      swap(in.p[in.K-1], in.p[it - begin(in.p)]);
    }
  }
  
  //cout << "max " << *it << endl;
  Num result = accumulate(begin(in.p), begin(in.p) + in.K, Num{0}, height_sum<Num>());
  //cout << result << endl;
  result += top_area(*max_element(begin(in.p), begin(in.p) + in.K));
  double dr = M_PI * result;
  cout.precision(6);
  cout << fixed << dr;
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
