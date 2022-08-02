#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

enum class State {kEmpty, kObstacle};

// Parse line
std::vector<State> ParseLine(const std::string line)
{
  std::vector<State> board_row{};
  std::istringstream board_stream(line);
  char comma;
  int elem;
  while (board_stream >> elem >> comma) 
  {
      if (elem == 1)
      {
        board_row.push_back(State::kObstacle);
      }
      else
      {
        board_row.push_back(State::kEmpty);
      }
  }
  return board_row;
}

// Demarcate state for each cell in board
std::string CellString(State cell)
{
  switch(cell)
  {
    case State::kObstacle: return "#   ";
    default: return "0   ";
  }
}


// Print board
void PrintBoard(const std::vector<std::vector<State>> vect)
{
    for (auto row: vect)
    {
        for (auto elem: row)
        {
            std::string cell = CellString(elem);
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

// Read Board
std::vector<std::vector<State>> ReadBoardFile(const std::string loc)
{
    std::vector<std::vector<State>> board;
    std::ifstream board_file(loc);
    if (board_file)
    {
        std::string line;
        while(getline(board_file, line))
        {
            std::vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}

int main() {
  // File location
  std::string loc("input.board");

  // Read board
  auto board = ReadBoardFile(loc);

  // Print board
  PrintBoard(board);
}