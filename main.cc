#include <iostream>

#include <bitset>

class TicTacToeProgram
{
protected:

  std::bitset<9> x;
  std::bitset<9> o;

  char get_game_cell (const size_t& i, const size_t& j)
  {
    if (x.test(i * 3 + j)) return 'X';
    if (o.test(i * 3 + j)) return 'O';
    return '0' + (i * 3 + j + 1);
  }

  void print_game_row (const size_t& i)
  {
    std::cout << ' ' << get_game_cell(i, 0) << " | " << get_game_cell(i, 1) << " | " << get_game_cell(i, 2) << ' ' << std::endl;
  }

  void print_game (void)
  {
    print_game_row(0);
    std::cout << "-----------" << std::endl;
    print_game_row(1);
    std::cout << "-----------" << std::endl;
    print_game_row(2);
  }

public:

  TicTacToeProgram ()
  {}

};

signed main (void)
{
  return 0;
}
