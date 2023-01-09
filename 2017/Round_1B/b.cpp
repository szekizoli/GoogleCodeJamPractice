#include <array>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef size_t ref_t;
typedef array<ref_t, 6> a_t;

enum type { red, yellow, orange, blue, violet, green };

char color []= {'R', 'Y', 'O', 'B', 'V', 'G'};
a_t horses;
a_t choosen;

vector<char> result;

ref_t choose(ref_t i) {
  result.push_back(color[i]);
  --horses[i];
  ++choosen[i];
  return i;
}

/*
void max(a_t& a) {
  if (horses[a[2]] < horses[a[1]]) swap(a[0], a[1]);
  else                             swap(a[0], a[2]);
}

void solve() {
  int N, R, O, Y, G, B, V;
  cin >> N >> R >> O >> Y >> G >> B >> V;
  if (N/2 < R || N/2 < Y || N/2 < B) {
    cout << "IMPOSSIBLE"; return;
  }
  fill(begin(choosen), end(choosen), 0);
  horses[red] = R; horses[yellow] = Y; horses[blue] = B;
  a_t c {0, 1, 2};
  if (Y >= R && Y >= B) swap(c[0], c[1]);
  else if (B >= R && B >= Y) swap(c[0], c[2]);
  ref_t first = c[0];
  choose(c[0]);
  for (int i = 1; i < N-2; ++i) {
    max(c);
    choose(c[0]);
  }
  if (0 < horses[first]) {
    choose(first);
    if (c[1] == first) swap(c[0], c[1]);
    else if (c[2] == first) swap(c[0], c[2]);
  }
  else { max(c); choose(c[0]); }
  max(c);
  choose(c[0]);
  if (choosen[0] != R || choosen[1] != Y || choosen[2] != B || first == c[0]) {
    cout << "!!!ERROR!!!" << endl;
  }
}
*/

bool can_stand(ref_t a, ref_t b) {
  return ((a+1)&(b+1)) == 0;
}

ref_t max(a_t const& a, ref_t prev) {
  ref_t i = 0;
  for (; i < 6; ++i) if (can_stand(prev, i)) break;
  ref_t result = i;
  for (; i < 6; ++i) if (can_stand(prev, i) && horses[i] > horses[result]) result = i;
  return result;
}

void solve(int N, int R, int Y, int B, int O = 0, int G = 0, int V = 0) {
  result.clear(); result.reserve(N);
  fill(begin(choosen), end(choosen), 0);
  horses[red] = R; horses[yellow] = Y; horses[blue] = B;
  horses[orange] = O; horses[green] = G; horses[violet] = V;
  ref_t prev = distance(begin(horses), max_element(begin(horses), end(horses)));
  ref_t first = choose(prev);
  if (N == 2) {
    prev = choose(max(horses, prev));
    return;
  }
  for (int i = 1; i < N-2; ++i) {
    prev = choose(max(horses, prev));
  }
  if (0 < horses[first]) {
    prev = choose(first);
  } else {
    prev = choose(max(horses, prev));
  }
  prev = choose(max(horses, prev));
  if (choosen[red] != R || choosen[yellow] != Y || choosen[blue] != B ||
      choosen[yellow] != Y || choosen[orange] != O || choosen[green] != G || first == prev) {
    cout << "!!!ERROR!!!" << endl;
  }
}

void print(int n, char a, char b) {
  while (n > 0) { cout << a << b; n -= 2; }
}

void solve_greedy() {
  int N, R, O, Y, G, B, V;
  cin >> N >> R >> O >> Y >> G >> B >> V;

  if (R < G || Y < V || B < O) {
    cout << "IMPOSSIBLE"; return;
  }

  if (G != 0 && R == G) {
    if (Y+B == 0) { print(N, 'R', 'G'); return; }
    else { cout << "IMPOSSIBLE"; return; }
  }
  if (V != 0 && Y == V) {
    if (R+B == 0) { print(N, 'Y', 'V'); return; }
    else { cout << "IMPOSSIBLE"; return; }
  }
  if (O != 0 && B == O) {
    if (R+Y == 0) { print(N, 'B', 'O'); return; }
    else { cout << "IMPOSSIBLE"; return; }
  }
  
  int R2 = R - G;
  int Y2 = Y - V;
  int B2 = B - O;
  N = R2 + Y2 + B2;
  
  if (N/2 < R2 || N/2 < Y2 || N/2 < B2) {
    cout << "IMPOSSIBLE"; return;
  }

  solve(N, R2, Y2, B2);
  for (char c : result ) {
    cout << c;
    if (c == 'R') while(0 < G--) cout << "GR";
    if (c == 'Y') while(0 < V--) cout << "VY";
    if (c == 'B') while(0 < O--) cout << "OB";
  }
}

int main () {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    cout.precision(6);
    cout << "Case #" << t+1 << ": ";
    solve_greedy();
    cout << endl;
  }
  return 0;
}
