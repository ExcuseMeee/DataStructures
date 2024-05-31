#include "Board.h"
#include <string>
#include <iostream>


Board::Board() {
  board_size = 8;
  std::string row(board_size, ' ');
  for (int i = 0; i < board_size; i++) {
    board.push_back(row);
  }
}

void Board::print() const {
  int i = 0;
  int j = board_size;
  std::cout << "  ________\n";
  while (i < board_size) {
    std::cout << j << '|' << board[i] << '|' << std::endl;
    i++;
    j--;
  }
  std::cout << "  --------\n";
  std::cout << "  abcdefgh\n";
}



void Board::place_queens() {
  place_queens_helper(0, 0, 0);
}

void Board::place_queens_helper(int row, int col, int queens_placed) {

  if (queens_placed == 8) {
    print();
    return;
  }

  for (int i = row; i < board_size; i++) {
    for (int j = col; j < board_size; j++) {
      if (board[i][j] == ' ') {
        if (check_place(i, j)) {
          board[i][j] = '*';
          place_queens_helper(i + 1, 0, queens_placed + 1);
          board[i][j] = ' ';
        }
      }
    }
  }

}

// bool has_char(const std::string& s, const char c, int n) {
//   for (int i = 0; i < n; i++) {
//     if (s[i] == c) {
//       return true;
//     }
//   }
//   return false;
// }



bool Board::check_place(const int row, const int col) const {
  //NS
  int i = 0;
  int j = col;
  while (i < board_size) {
    if (board[i][j] == '*' && (i != row || j != col)) {
      return false;
    }
    i++;
  }

  i = row;
  j = col;


  //NE
  while (i >= 0 && j < board_size) {
    if (board[i][j] == '*' && (i != row || j != col)) {
      return false;
    }
    i--;
    j++;
  }

  i = row;
  j = 0;

  //WE
  while (j < board_size) {
    if (board[i][j] == '*' && (i != row || j != col)) {
      return false;
    }
    j++;
  }


  //SE
  i = row;
  j = col;

  while (i < board_size && j < board_size) {
    if (board[i][j] == '*' && (i != row || j != col)) {
      return false;
    }
    j++;
    i++;
  }

  i = row;
  j = col;

  //SW
  while (i < board_size && j >= 0) {
    if (board[i][j] == '*' && (i != row || j != col)) {
      return false;
    }
    j--;
    i++;
  }

  //NW
  i = row;
  j = col;

  while (i >= 0 && j >= 0) {
    if (board[i][j] == '*' && (i != row || j != col)) {
      return false;
    }
    j--;
    i--;
  }

  return true;
}