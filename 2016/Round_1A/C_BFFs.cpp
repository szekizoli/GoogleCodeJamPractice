#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#define TYPE unsigned
#define f(i, N) for(unsigned i = 0; i < N; ++i)
#define fr(i, N) for(int i = N-1; i >= 0; --i) // reverse
#define ff(i, j, N) for(unsigned i = 0; i < N; ++i) for(unsigned j = 0; j < N; ++j)
#define V vector<TYPE>

class graph {
public:
	graph() {}
	graph(const vector<int>& input) {
		for (int i = 0; i < input.size(); ++i) {
			data[i + 1] = input[i];
		}
	}
	friend ostream& operator<<(ostream& out, const graph&);
	size_t size() const { return data.size(); }
	int next(int id) const { return data.at(id); }
	bool contains(int id) const { return data.find(id) != data.end(); }
	void add_edge(int from, int to) { data[from] = to; }
	map<int, int>::iterator begin() { return data.begin(); }
	map<int, int>::const_iterator begin() const { return data.cbegin(); }
	map<int, int>::iterator end() { return data.end(); }
	map<int, int>::const_iterator end() const { return data.cend(); }
private:
	map<int, int> data;
};

graph get_circle_from(int from, const graph& g) {
	graph result;
	int start = from;
	while (!result.contains(from)) {
		int next = g.next(from);
		result.add_edge(from, next);
		from = next;
	}

	return start == from ? result : graph{};
}

vector<graph> get_all_circles(const graph& g) {
	vector<graph> vg;
	for (auto edge : g) {
		vg.push_back(get_circle_from(edge.first, g));
	}
	return vg;
}

int get_longest_circle(const vector<graph>& circles) {
	int max = 0;
	for (auto g : circles) {
		if (max < g.size()) max = g.size();
	}
	return max;
}

int get_longest_circle(const graph& g) {
	return get_longest_circle(get_all_circles(g));
}

set<int> get_bicircles(const vector<graph>& circles) {
	set<int> node_ids;
	for (const auto& g : circles) {
		if (g.size() == 2) {
			for (auto edge : g) {
				node_ids.insert(edge.first);
			}
		}
	}
	if (node_ids.size() & 1 == 1) {
		throw std::runtime_error("Binodes size is odd!");
	}
	return node_ids;
}

bool binodes_contains(int from, const set<int>& binodes) {
	return binodes.find(from) != binodes.end();
}

bool add(set<int>& visited, int node) {
	return visited.insert(node).second;
}

const pair<int, int> invalid_node = { -1, -1 };

// to, distance
pair<int, int> get_distance(const graph& g, int from, const set<int>& binodes) {
	if (binodes_contains(from, binodes)) return {from, 0};
	set<int> visited;
	int distance = 0;
	while (true) {
		if (!add(visited, from)) break;
		++distance;
		from = g.next(from);
		if (binodes_contains(from, binodes)) {
			return {from, distance};
		}
	}
	return invalid_node;
}

int get_sum_distance(const graph& g, const set<int>& binodes) {
	map<int, int> all_dist;
	for (const auto& edge : g) {
		auto distance_pair = get_distance(g, edge.first, binodes);
		if (distance_pair != invalid_node) {
			auto current_max = max(all_dist[distance_pair.first], distance_pair.second);
			all_dist[distance_pair.first] = current_max;
		}
	}

	int sum = 0;
	for (const auto& p : all_dist) {
		sum += p.second;
	}
	return sum;
}

ostream& operator<<(ostream& out, const graph& g) {
	out << "[";
	for (const auto& p : g.data) {
		out << "(" << p.first << "->" << p.second << "), ";
	}
	out << "]";
	return out;
}

void test_get_all_circles() {
	//graph g(vector<int>{ 2, 1, 4, 5, 3, 7, 8, 9, 10, 6, 10, 11, 12});
	graph g(vector<int>{ 4, 5, 8, 3, 4, 8, 9, 6, 1 });
	auto circles = get_all_circles(g);
	for (auto circle : circles) {
		cout << circle << endl;
	}
	cout << "Max=" << get_longest_circle(g) << endl;
}
void test_get_circle_from() {
	//graph g(vector<int>{ 3, 3, 4, 1 });
	graph g(vector<int>{ 4, 5, 8, 3, 4, 8, 9, 6, 1 });
	cout << "input=" << g << endl;
	for (int i = 1; i <= g.size(); ++i) {
		auto r = get_circle_from(i, g);
		cout << "from=" << i << ", graph=" << r << endl;
	}
}

void test_contains() {
	//graph g(vector<int>{ 2, 3, 4, 1 });
	graph g(vector<int>{ 4, 5, 8, 3, 4, 8, 9, 6, 1 });
	cout << "g contains 1 " << g.contains(1) << endl;
	cout << "g contains 3 " << g.contains(3) << endl;
	cout << "g contains 5 " << g.contains(5) << endl;
	cout << "g contains 5 " << g.contains(5) << endl;
}

void test_get_bicircles() {
	//graph g(vector<int>{ 2, 3, 2, 3, 2, 5, 6, 3, 8, 4, 10, 11, 14, 13, 16, 17, 15, 19, 18 });
	graph g(vector<int>{ 4, 5, 8, 3, 4, 8, 9, 6, 1 });
	cout << "input=" << g << endl;
	const auto circles = get_all_circles(g);
	const auto binodes = get_bicircles(circles);
	for (int i : binodes) {
		cout << i << ", " << endl;
	}
}

void test_get_distance() {
	graph g(vector<int>{ 2, 3, 2, 3, 2, 5, 6, 3, 8, 4, 10, 11, 14, 13, 16, 17, 15, 19, 18 });
	cout << "input=" << g << endl;
	const auto circles = get_all_circles(g);
	const auto binodes = get_bicircles(circles);

	for (int i = 1; i < g.size(); ++i) {
		auto dist = get_distance(g, i, binodes);
		cout << "distance("<<i<<")=[to="<<dist.first<<" is " << dist.second << "]" << endl;
	}

	for (int i : binodes) {
		cout << i << ", " << endl;
	}
}

void test_get_sum_distance() {
	graph g(vector<int>{ 2, 3, 2, 3, 2, 5, 6, 3, 8, 4, 10, 11, 14, 13, 16, 17, 15, 19, 18 });
	cout << "input=" << g << endl;
	const auto circles = get_all_circles(g);
	const auto binodes = get_bicircles(circles);

	cout << "sum=" << get_sum_distance(g, binodes) << " + " << binodes.size() << endl;
}

void test_print() {
	cout << graph(vector<int>{ 4, 5, 8, 3, 4, 8, 9, 6, 1 }) << endl;
}

vector<int> read(int N) {
	vector<int> v;
	int in;
	for (int i{ 0 }; i < N; ++i) {
		cin >> in;
		v.push_back(in);
	}

	return v;
}

void solve(const vector<int>& v) {
	graph g(v);
	const auto circles = get_all_circles(g);
	const auto binodes = get_bicircles(circles);
	const int longest_circle = get_longest_circle(circles);
	const int binodes_sum = get_sum_distance(g, binodes) + binodes.size();
	cout << max(longest_circle, binodes_sum);
}

int main() {
	/*test_print();
	test_contains();
	test_get_circle_from();
	test_get_all_circles();
	test_get_bicircles();
	test_get_distance();
	test_get_sum_distance();*/
	try {
		unsigned T;
		TYPE N;
		cin >> T;
		f(t, T) {
			cin >> N;
			cout << "Case #" << t + 1 << ": ";
			solve(read(N));
			std::cout << std::endl;
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cout << "Unknown exception" << endl;
	}
}