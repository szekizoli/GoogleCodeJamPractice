#include<algorithm>
#include<iostream>
#include<vector>

#include "min_element_1_2.h"

using namespace std;

// a tree
// full binary tree
// root: 0 parent, 2 children
// middle: 1 parent, 2 children
// leaf: 1 parent, 0 child

// group nodes by count?
// nodes with at least 3 nodes can be non-leaf
// brute-force
// try building largest tree from each node as root
// tree(root)
// tree.add(parent, child)
// build_from(root, exclude)
// if (size(root) <= 2) return 1;
// for(child c : children) {
//   if (c != exclude) result.add(build_from(c, root));
// }
// choose_two_largest
// return the sum of them

typedef size_t node_t;

vector<vector<node_t>> tree;

vector<node_t>& children(node_t node) {
  return tree[node-1];
}

size_t size(node_t node) {
  return children(node).size();
}

size_t build_from(node_t root, node_t exclude) {
  if (exclude == 0 && size(root) < 2) return 1;
  if (exclude > 0 && size(root) < 3) return 1;
  vector<size_t> result;
  result.reserve(size(root));
  for (node_t child : children(root)) {
    if (child != exclude) {
      size_t r = build_from(child, root);
      //cout << "(" << child << ", " << root << ") =" << r << endl;
      result.push_back(r);
    }
  }
  // find two largest
  auto max = min_two_element_binary(begin(result), end(result), std::greater<size_t>());
  return *max.first + *max.second + 1;
}

void read_tree() {
  tree.clear();
  int n; cin >> n;
  tree.resize(n);
  int x, y;
  for (int i = 0; i < n-1; ++i) {
    cin >> x >> y;
    children(x).push_back(y);
    children(y).push_back(x);
  }
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    read_tree();
    int max = 1;
    for (int n = 1; n <= tree.size(); ++n) {
      int r = build_from(n, 0);
      if (max < r) max = r;
    }
    cout << "Case #" << t+1 << ": " << tree.size() - max << endl;
  }
  //tree.reserve(7);
  //tree.emplace_back(vector<node_t>{2, 3});
  //tree.emplace_back(vector<node_t>{1, 4});
  //tree.emplace_back(vector<node_t>{1, 7});
  //tree.emplace_back(vector<node_t>{2, 5, 6});
  // tree.emplace_back(vector<node_t>{4});
  //tree.emplace_back(vector<node_t>{4});
  //tree.emplace_back(vector<node_t>{3});
  //  size_t n; cin >> n;
  //cout << build_from(n, 0) << endl;
  return 0;
}
