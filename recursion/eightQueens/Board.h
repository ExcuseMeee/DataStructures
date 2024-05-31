#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>

class Board {
public:
  Board();

  void print() const;

  void place_queens();

private:
  bool check_place(const int row, const int col) const;
  void place_queens_helper(int row, int col, int queens_placed);
  std::vector<std::string> board;
  unsigned board_size;
};
#endif