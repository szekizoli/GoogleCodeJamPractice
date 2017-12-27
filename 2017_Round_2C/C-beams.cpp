// Google Code Jam https://code.google.com/codejam/contest/5314486/dashboard#s=p2

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

enum class State {POSSIBLE, IMPOSSIBLE};

struct coloumn {
  vector<vector<char>> const& table;
  const size_t col;
  coloumn(vector<vector<char>> const& table, const size_t col) : table(table), col(col) {}
  char operator[](size_t row) const {
    return table[row][col];
  }
  size_t size() const {
    return table.size();
  }
};

struct board {
  vector<vector<char>> _board;
  int R;
  int C;
  State state;
  board() : state(State::POSSIBLE) {}
  vector<char> const& operator[](size_t i) const {
    return _board[i];
  }
  vector<char> & operator[](size_t i) {
    return _board[i];
  }

  vector<char> const& row(size_t r) {
    return _board[r];
  }
  coloumn col(size_t c) {
    return coloumn(_board, c);
  }
};

bool is_wall(char c) {
  return c == '#';
}

bool is_set_beam(char c) {
  return c == '-' || c == '|'; 
}

bool is_beam(char c) {
  return is_set_beam(c) || c == '*';
}

bool is_empty(char c) {
  return c == ',';
}

bool is_covered(char c) {
  return c == '.';
}

std::istream& operator>>(std::istream& i, board & b) {
  b._board.clear();
  b.state = State::POSSIBLE;
  i >> b.R >> b.C;
  for (int r = 0; r < b.R; ++r) {
    b._board.push_back(vector<char>(b.C));
    for (int c = 0; c < b.C; ++c) {
      i >> b[r][c];
      if (is_beam(b[r][c])) b[r][c] = '*';
      if (is_covered(b[r][c])) b[r][c] = ',';
    }
  }
  return i;
}

std::ostream& operator<<(std::ostream& o, board const& b) {
  if (b.state == State::IMPOSSIBLE) {
    return o << "IMPOSSIBLE";
  }
  o << "POSSIBLE" << endl;
  for (int r = 0; r < b.R; ++r) {
    for (int c = 0; c < b.C; ++c) o << b._board[r][c];
    o << endl;
  }
  return o;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, vector<T> v) {
  std::copy(begin(v), end(v), std::ostream_iterator<T>(o, " "));
  return o;
}

int to_absolute(board const & b, int x, int y) {
    return x * b.R + y;
}

template<typename Line, typename P>
// requires operator[] & size
vector<int> list_from(Line const& line, const int x, P p) {
  vector<int> result;
  
  for (int i = x; i >= 0 && !is_wall(line[i]); --i)
    if (p(line[i])) result.push_back(i);

  for (int i = x + 1; i < line.size() && !is_wall(line[i]); ++i)
    if (p(line[i])) result.push_back(i);

  return result;
}

template<typename Line>
// requires operator[] & size
vector<int> list_beams_from(Line const& line, const int x) {
  return list_from(line, x, is_beam);
}

template<typename Line>
// requires operator[] & size
vector<int> list_empty_from(Line const& line, const int x) {
  return list_from(line, x, is_empty);
}

void set_vertical(board& b, const int r, const int c) {
  b[r][c] = '|';
  vector<int> empty_cells = list_empty_from(b.col(c), r);
  for (int ec : empty_cells) b[ec][c] = '.';
}

void set_horizontal(board& b, const int r, const int c) {
  b[r][c] = '-';
  vector<int> empty_cells = list_empty_from(b.row(r), c);
  for (int ec : empty_cells) b[r][ec] = '.';
}

bool set_colined_beams(board& b, const int r, const int c) {
  vector<int> row = list_beams_from(b.row(r), c);
  vector<int> col = list_beams_from(b.col(c), r);
  if (row.size() > 1 && col.size() > 1) { b.state = State::IMPOSSIBLE; return false; }
  if (row.size() < 2 && col.size() < 2) { return true; }
  if (row.size() > 1) {
    for (int x : row) {
        if (b[r][x] == '-') { b.state = State::IMPOSSIBLE; return false; }
        set_vertical(b, r, x);
      }
  } else {
    for (int x : col) {
      if (b[x][c] == '|') { b.state = State::IMPOSSIBLE; return false; }
      set_horizontal(b, x, c);
    }
  }
  return true;
}

bool cover_empty_cells(board& b, const int r, const int c) {
  vector<int> row = list_beams_from(b.row(r), c);
  vector<int> col = list_beams_from(b.col(c), r);
  if ((row.size() != 1 || b[r][row[0]] == '|') && (col.size() != 1 || b[col[0]][c] == '-')) {
    b.state = State::IMPOSSIBLE; 
    return false;
  }
  if ((row.size() == 1 && b[r][row[0]] != '|') && (col.size() != 1 || b[col[0]][c] == '-')) {
    set_horizontal(b, r, row[0]);
  }
  if ((row.size() != 1 || b[r][row[0]] == '|') && (col.size() == 1 && b[col[0]][c] != '-')) {
    set_vertical(b, col[0], c);
  }
  return true; 
}

void solve(board & b) {
  for (int r = 0; r < b.R; ++r) {
    for (int c = 0; c < b.C; ++c) {
      if (is_beam(b[r][c])) {
        if (!set_colined_beams(b, r, c)) return;
      }
    }
  }
  for (int r = 0; r < b.R; ++r) {
    for (int c = 0; c < b.C; ++c) {
      if (is_empty(b[r][c])) {
        if (!cover_empty_cells(b, r, c)) return;
      }
    }
  }
  for (int r = 0; r < b.R; ++r) {
    for (int c = 0; c < b.C; ++c) {
      if (b[r][c] == '*') set_horizontal(b, r, c);
    }
  }
  for (int r = 0; r < b.R; ++r) {
    for (int c = 0; c < b.C; ++c) {
      if (is_empty(b[r][c])) {
        b.state = State::IMPOSSIBLE; 
        return;
      }
    }
  }
}

int main() {
  int T;
  board b;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> b;
    solve(b);
    cout << "Case #" << t+1 << ": " << b << endl;
  }
}

