#include <cstring>
#include <iomanip>
#include <iostream>

constexpr int cBoardHeight = 5;
constexpr int cBoardWidth = 10;
constexpr int cCommandNameLength = 32;
constexpr int cWordBufferSize = 256;

bool IsInsideBoard(int x, int y) {
  return x >= 0 && x < cBoardWidth && y >= 0 && y < cBoardHeight;
}

void ClearBoard(char board[][cBoardWidth]) {
  std::memset(board, ' ', sizeof(char) * cBoardHeight * cBoardWidth);
}

bool PutSymbol(char board[][cBoardWidth], int x, int y, char symbol) {
  if (!IsInsideBoard(x, y)) {
    return false;
  }
  board[y][x] = symbol;
  return true;
}

bool PutWord(char board[][cBoardWidth], int x, int y, const char* word) {
  int length = static_cast<int>(std::strlen(word));
  if (length == 0 || !IsInsideBoard(x, y) ||
      !IsInsideBoard(x + length - 1, y)) {
    return false;
  }
  for (int i = 0; i < length; ++i) {
    PutSymbol(board, x + i, y, word[i]);
  }
  return true;
}

void PrintBoard(const char board[][cBoardWidth]) {
  for (int y = 0; y < cBoardHeight; ++y) {
    std::cout.write(board[y], cBoardWidth);
    std::cout << '\n';
  }
}

int main() {
  char board[cBoardHeight][cBoardWidth];
  ClearBoard(board);

  char command_name[cCommandNameLength];
  while (std::cin >> std::setw(cCommandNameLength) >> command_name) {
    if (std::strcmp(command_name, "quit") == 0) {
      break;
    }

    bool is_successful = true;
    if (std::strcmp(command_name, "clear") == 0) {
      ClearBoard(board);
    } else if (std::strcmp(command_name, "print") == 0) {
      PrintBoard(board);
    } else if (std::strcmp(command_name, "put") == 0) {
      int x;
      int y;
      char symbol;
      std::cin >> x >> y >> symbol;
      is_successful = PutSymbol(board, x, y, symbol);
    } else if (std::strcmp(command_name, "text") == 0) {
      int x;
      int y;
      char word[cWordBufferSize];
      std::cin >> x >> y >> std::setw(cWordBufferSize) >> word;
      is_successful = PutWord(board, x, y, word);
    }

    if (!is_successful) {
      std::cout << "error\n";
    }
  }
}
