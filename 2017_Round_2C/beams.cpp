#include<algorithm>
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<utility>


using namespace std;

using Cell = int;
using Beam = pair<int, int>;
using Position = pair<int, int>;
using Row = vector<Cell>;
using Table = vector<Row>;
enum class BeamStatus  { vertical, horizontal, not_set };

map<Beam, BeamStatus> beams;

bool isBeam(Cell c) {
  return c == '|' || c == '-'; 
}

bool isWall(Cell c) {
  return c == '#';
}

Table read(int C, int R) {
  Table t(R);
  fill(t.begin(), t.end(), Row(C));

  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
       Cell c; cin >> c;
       t[i][j] = c;
       if (isBeam(c)) {
         beams[make_pair(i, j)] = BeamStatus::not_set;
       }
    }
  }

  return t;
}

struct VerticalExtracter {
  int operator()(const Position& p) {
    return p.first;
  }
  int& operator()(Position& p) {
    return p.first;
  }
};

struct HorizontalExtracter {
  int operator()(const Position& p) const {
    return p.second;
  }
  int& operator()(Position& p) const {
    return p.second;
  }
};

template<typename Extractor>
struct Incrementer {
  const int limit;
  Extractor extractor;
  Incrementer(int limit) : limit(limit) {}
  bool canIncrement(const Position& p) {
    return extractor(p) < limit;
  }
  int distance(const Position& p0, const Position& p1) {
    return extractor(p1) - extractor(p0);
  }
  void operator()(Position & p) {
    ++extractor(p);
  }
};

template<typename Inc>
vector<Beam> findBeams(const Table& table, Position& p, Inc incrementer) {
  vector<Beam> result;
  while (incrementer.canIncrement(p)) {
    if (isWall(table[p.first][p.second])) { incrementer(p); break; }
    if (isBeam(table[p.first][p.second])) result.push_back(p);
    incrementer(p);
  }
  return result;
}

string solve(const Table table) {
  Incrementer<HorizontalExtracter> hi(table[0].size());
  // Step 1
  for (int r = 0; r < table.size(); ++r) {
    Position p(r, 0);
    while (hi.canIncrement(p)) {
      vector<Beam> beamsInRow = findBeams(table, p, hi);
      if (beamsInRow.size() < 2) continue;
      for (Beam b : beamsInRow) {
        if (beams[b] == BeamStatus::horizontal) return "IMPOSSIBLE";
        beams[b] = BeamStatus::vertical;
      }
    }
  }
  Incrementer<VerticalExtracter> vi(table.size());
  for (int c = 0; c < table[0].size(); ++c) {
    Position p(0, c);
    while (vi.canIncrement(p)) {
      vector<Beam> beamsInColumn = findBeams(table, p, vi);
      if (beamsInColumn.size() < 2) continue;
      for (Beam b : beamsInColumn) {
        if (beams[b] == BeamStatus::vertical) return "IMPOSSIBLE";
        beams[b] = BeamStatus::horizontal;
      }
    } 
  }  
  // Step 2
  for (int r = 0; r < table.size(); ++r) {
    Position p(r, 0);
    while (hi.canIncrement(p)) {
      Position s = p;
      vector<Beam> beamsInRow = findBeams(table, p, hi);
      if (beamsInRow.size() < 2) continue;
      for (Beam b : beamsInRow) {
        if (beams[b] == BeamStatus::horizontal) return "IMPOSSIBLE";
        beams[b] = BeamStatus::vertical;
      }
    }
  }
 
  return "POSSIBLE";
}

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    int C, R; cin >> C >> R;
    Table table = read(C, R);
    cout << "Case #" << t+1 << ": ";
    cout << solve(table);
    cout << endl;
  } 
  return 0;
}
