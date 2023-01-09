#include<array>
#include<algorithm>
#include<bitset>
#include<iostream>
#include<utility>
#include<vector>

using namespace std;

class input;

typedef unsigned long long N;
typedef input input_t;

N mul(N x, N y) {
  return (x * y) % 1000000007;
}

N factor(N value) {
  N result = 1;
  while (1 < value) {
    result = mul(result, value);
    --value;
  }
  return result;  
}

inline size_t index(char c) { return c - 'a'; }
inline char to_char(size_t i) { return i + 'a'; }

class input {
private:
  array<unsigned, 26> doubles;
  array<char, 26> first_second;
  array<char, 26> second_first;
  bool good;
public:
  input() {
    good = true;
    fill(begin(first_second), end(first_second), 0);
    fill(begin(second_first), end(second_first), 0);
    fill(begin(doubles), end(doubles), 0);
  }
  void print() {
    print_char_array(first_second);
    print_char_array(second_first);
  }
  bool is_good() { return good; }
  void make_bad() { good = false; }
  bool has_non_double() {
    for(char c : first_second) if (c != 0) return true;
    return false;
  }
  void add_car(char f, char l) {
    if (f == l) doubles[index(f)]++;
    else {
      if (first_second[index(f)] != 0) good = false;
      else if (second_first[index(l)] != 0) good = false;
      else {
	first_second[index(f)] = l;
	second_first[index(l)] = f;
      }
    }
  }
  pair<char, char> last(){
    return make_pair(0, 0);
  }
  pair<char, char> find_first_doesnt_appear_second() {
    for (size_t i = 0; i < 26; ++i) {
      char current = first_second[i];
      if (current != 0 && second_first[i] == 0) {
	//cout << to_char(i) << " " << current << endl;
	return make_pair(to_char(i), current);
      }
    }
    return last();
  }
  void mark_used(pair<char, char> const& p) {
    first_second[index(p.first)] = 0;
    second_first[index(p.second)] = 0;
    doubles[index(p.first)] = 0;
    doubles[index(p.second)] = 0;
  }
  unsigned get_doubles(char c) {
    return doubles[index(c)];
  }
  pair<char, char> find_starts_with(char c) {
    char next = first_second[index(c)];
    return next == 0 ? last() : make_pair(c, next);
  }
  vector<N> get_remaining_doubles() {
    vector<N> r;
    r.reserve(16);
    for(auto i : doubles) if (i != 0) r.push_back(factor(i));
    return r;
  }
};

N find_group(input_t& input) {
  auto x = input.find_first_doesnt_appear_second();
  if (x == input.last()) return 0;
  int counter = 1;
  counter = mul(counter, factor(input.get_doubles(x.first)));
  do {
    counter = mul(counter, factor(input.get_doubles(x.second)));
    input.mark_used(x);
    x = input.find_starts_with(x.second);
  } while(x != input.last());
  return counter;
}

bool validate(bitset<26>& seen, bitset<26>& seen_e, string const& s){
  char f = s[0];
  char l = s[s.size()-1];
  if (seen[index(f)] || seen[index(l)]) return false;

  for (size_t i = 1; i < s.size(); ++i)
    if (s[i] == f) { if (s[i-1] == f) continue; else { return false; } }    

  for (size_t i = 0; i < s.size() - 1; ++i)
    if (s[i] == l) { if (s[i+1] == l) continue; else { return false; } }
  
  for (size_t i = 1; i < s.size() - 1; ++i) {
    if (s[i] == f || s[i] == l) continue;
    if (seen[index(s[i])] && s[i] != s[i-1]) return false;
    if (seen_e[index(s[i])]) return false;
    seen[index(s[i])] = true;
  }
  seen_e[index(f)] = true;
  seen_e[index(l)] = true;
  return true;
}

istream& operator>>(istream& i, input& in) {
  int N; i >> N;
  bitset<26> seen_middle(false);
  bitset<26> seen_edge(false);
  for (int n = 0; n < N; ++n) {
    string s; i >> s;
    if (!in.is_good()) continue;
    in.add_car(s[0], s[s.size()-1]);
    if (!validate(seen_middle, seen_edge, s)) in.make_bad();
  }
  return i;
}

N solve() {
  input in;
  cin >> in;
  if (!in.is_good()) { return 0; }
  N group_count = find_group(in);
  vector<N> groups;
  groups.reserve(10);
  while(group_count != 0) {
    groups.push_back(group_count);
    group_count = find_group(in);
  }
  vector<N> remaining = in.get_remaining_doubles();
  groups.insert(end(groups), begin(remaining), end(remaining));
  N result = factor(groups.size());
  if (in.has_non_double()) result = 0;
  for (N n : groups) {
    result = mul(result, n);
  }
  return result;
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
    cout << "Case #" << t+1 << ": " << solve() << endl;
  }
  return 0;
}
