// 201  Round Problem
#include<algorithm>
#include<cmath>
#include<iostream>
#include<limits>
#include<map>
#include<memory>
#include<utility>
#include<set>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

// I/O

struct input {
	vector<string> existing;
	vector<string> tocreate;
	input(size_t N, size_t M) : existing(vector<string>(N)), tocreate(vector<string>(M)) {}
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
  return is >> in.existing >> in.tocreate;
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

struct node {
	string data;
	node(string const& d) : data(d) {}
	map<string, unique_ptr<node>> successors;
};

struct tree {
	node root{""};
};

struct NoopCounter {
	void operator++() {}
};

template<typename Counter>
void add_to_tree(tree & t, string const& path, Counter& counter) {
	stringstream ss(path);
	node* n = &t.root;
	string result;
	while(getline(ss, result, '/')) {
		if (result.empty()) continue;
		//cout << "read " << result << endl;
		auto it = n->successors.find(result);
		if (it != n->successors.end()) {
			n = it->second.get();
		} else {
			n->successors.emplace(make_pair(result, make_unique<node>(result)));
			//cout << "add " << result << " to " << n->data <<  endl;
			++counter;
			n = n->successors[result].get();
		}
	}
}

template<typename Counter>
tree build_tree(vector<string> const& leafs, Counter& counter) {
	tree t;
	for (string const& s: leafs) add_to_tree(t, s, counter);
	return t;
}

void solve(input const& in) {
	unsigned long long counter = 0;
	tree t = build_tree(in.existing, counter);
	counter = 0;
	for (string const& s : in.tocreate) add_to_tree(t, s, counter);
	cout << counter; 
}

int main() {
  int T = 0; cin >> T;
  for (int t = 0; t < T; ++t) {
		size_t N, M;
		cin >> N >> M;
    input in(N, M); cin >> in;
    cout << "Case #" << t+1 << ": ";
    solve(in);
    cout << endl;
  }
  return 0;
}
