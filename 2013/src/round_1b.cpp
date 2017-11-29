#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

using Num = long long;
using Value = long long;
using Energy = long long;

using I = vector<Value>::const_iterator;

Value solve_single(Energy start, Energy end, Energy regain, Value value) {
  //cout << "single input: " << start << ", " << end << ", " << regain << ", " << value << endl;
  if (end <= regain) return start*value;
  return max(Value(0), start - (end - regain)) * value;
}

Value solve_recursive(Energy start, Energy end, const Energy total, const Energy regain, I first, const I last) {
  if (first == last) return 0;
  auto n = distance(first, last);
  if (n == 1) return solve_single(start, end, regain, *first);
  I max_e = max_element(first, last);
  //cout << "Max Element: " << *max_e << endl;
  // which max to choose?
  auto d_m = distance(first, max_e);
  Energy reduction = max(Value(0), end - (n-d_m) * regain);
  //cout << "reduction: " << reduction << endl;
  Energy max_energy = min(total, start + d_m * regain) - reduction;
  Value result = max_energy * (*max_e);
  //cout << "Value from max: " << result << endl;
  result += solve_recursive(start, max_energy + reduction, total, regain, first, max_e);
  //cout << "Value with first: " << result << endl;
  result += solve_recursive(regain, end, total, regain, max_e + 1, last);
  //cout << "Final result: " << result << endl;
  return result;
}

Value solve(Energy max, Energy regain, vector<Value> const& values) {
  return solve_recursive(max, 0, max, regain, begin(values), end(values));
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    Energy e, r;
    Num n; 
    cin >> e >> r >> n;
    vector<Value> values(n);
    for (int j = 0; j < n; ++j) cin >> values[j];
    cout << "Case #" << i+1 << ": " << solve(e, r, values) << endl;
  }
  return 0;
}
