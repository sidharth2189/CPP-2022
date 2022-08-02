#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

// Board cell state
enum class State {kStart, kEmpty, kObstacle, kClosed, kPath, kFinish};

// Directional deltas (motion model)
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

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

// Compare the f-value (cost+heuristic) of two nodes
bool Compare(const std::vector<int> node1, const std::vector<int> node2)
{
  int f_value1 = node1[2] + node1[3];
  int f_value2 = node2[2] + node2[3];
  return f_value1 > f_value2;
}

// Sort the two-dimensional vector of ints in descending order.
void CellSort(std::vector<std::vector<int>> *v) {
  std::sort(v->begin(), v->end(), Compare);
}

// Admissible heuristic function
int Heuristic(int x1, int y1, int x2, int y2)
{
  int dist;
  dist = std::abs(x1-x2) + std::abs(y1-y2);
  return dist;
}

// Check that the cell is on the grid and not an obstacle (i.e. equals kEmpty).
bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid)
{
  if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == State::kEmpty) {return true;}
  return false;
}

// Add node to open list of nodes to expand
void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &open_list, std::vector<std::vector<State>> &grid)
{
  std::vector<int> node = {x, y, g, h};
  open_list.push_back(node);
  grid[x][y] = State::kClosed;
}

// Expand current nodes's neighbors and add them to the open list
void ExpandNeighbors(std::vector<int> &current_node, int goal[2], std::vector<std::vector<int>> &open_list, std::vector<std::vector<State>> &grid)
{
  // Get current node data
  int x = current_node[0];
  int y = current_node[1];
  int g = current_node[2];

  // Loop through current node's potential neighbours using directional deltas
  for (auto delta_move : delta)
  {
    int x2 = x + delta_move[0];
    int y2 = y + delta_move[1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, grid))
    {
      // Increment g value, compute h value, and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, open_list, grid);
    }
  }
}

// A* Search
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int init[2], int goal[2])
{
  // Create the vector of open nodes.
  std::vector<std::vector<int>> open {};
  
  // Initialize the starting node.
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  
  // Use AddToOpen to add the starting node to the open vector.
  AddToOpen(x, y, g, h, open, grid);

  // While open list is non-empty
  while (open.size() > 0)
  {
    // Sort the open list using CellSort, and get the current node
    // Pop the last node from the sort (node with least f-value)
    CellSort(&open);
    auto current_node = open.back();
    open.pop_back();

    // Get the x and y values from the current node,
    // and set grid[x][y] to kPath.
    x = current_node[0];
    y = current_node[1];
    grid[x][y] = State::kPath;

    // Check if the goal is reached. If so, return grid.
    if (x == goal[0] && y == goal[1])
    {
      // Set the init grid cell to kStart, and 
      // set the goal grid cell to kFinish before returning the grid.
      grid[init[0]][init[1]] = State::kStart;
      grid[goal[0]][goal[1]] = State::kFinish;
      return grid;
    }

    // If not, expand search to current node's neighbour
    ExpandNeighbors(current_node, goal, open, grid);
  }
  
  // Print when search has run out of new nodes to expand and still has not found goal
  std::cout << "No path found!" << std::endl;
  return std::vector<std::vector<State>>{};
}

// Demarcate state for each cell in board
std::string CellString(State cell)
{
  switch(cell)
  {
    case State::kObstacle: return "Obs   ";
    case State::kPath: return "Car   ";
    case State::kStart: return "Str   ";
    case State::kFinish: return "Fin  ";
    default: return "000   ";  
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

int main() {
  // File location
  std::string loc("input.board");

  // Init and goal cells
  int init[2] = {0, 0};
  int goal[2] = {4, 5};

  // Read board
  auto board = ReadBoardFile(loc);

  // A* Search
  auto solution = Search(board, init, goal);

  // Print board
  PrintBoard(solution);
}
