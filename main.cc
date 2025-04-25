#include <iostream>

#include <bitset>

class TicTacToeProgram
{
protected:

  std::bitset<9> x;
  std::bitset<9> o;

  char get_table_cell (const size_t& i, const size_t& j)
  {
    if (x.test(i * 3 + j)) return 'X';
    if (o.test(i * 3 + j)) return 'O';
    return '0' + (i * 3 + j + 1);
  }

  void print_table_row (const size_t& i)
  {
    std::cout << ' ' << get_table_cell(i, 0) << " | " << get_table_cell(i, 1) << " | " << get_table_cell(i, 2) << ' ' << std::endl;
  }

  void ui_print_table (void)
  {
    print_table_row(0);
    std::cout << "-----------" << std::endl;
    print_table_row(1);
    std::cout << "-----------" << std::endl;
    print_table_row(2);
  }

  bool occupy_pos_w_x (const size_t& i)
  {
    if (i > 9 || o.test(i - 1)) return false;
    x.set(i - 1);
    return true;
  }

  bool occupy_pos_w_o (const size_t& i)
  {
    if (i > 9 || x.test(i - 1)) return false;
    o.set(i - 1);
    return true;
  }

  bool test_result_for (const std::bitset<9>& b)
  {
    for (size_t i = 0; i < 3; i ++)
    {
      if (x.test(i)     && x.test(3 + i)     && x.test(6 + i)
      ||  x.test(3 * i) && x.test(3 * i + 1) && x.test(3 * i + 2)) return true;
    }

    if (x.test(4) && (x.test(0) && x.test(8) || x.test(6) && x.test(2))) return true;

    return false;
  }

  bool test_draw (void)
  {
    for (size_t i = 0; i < 9; i ++)
      if (!(x.test(i) || o.test(i))) return false;

    return true;
  }

  short test_result (void)
  {
    return test_result_for(x) ? 1 : test_result_for(o) ? 2 : test_draw() ? -1 : 0;
  }

  void ui_request_position_for_x (void)
  {
    size_t p;
    std::cout << std::endl << "Jogador 1 (X), escolha uma posição: ";
    if (!(std::cin >> p && occupy_pos_w_x(p)))
    {
      std::cout << "Posição inválida ou já ocupada! Escolha outra posição." << std::endl;
      ui_request_position_for_x();
    }
  }

  void ui_request_position_for_o (void)
  {
    size_t p;
    std::cout << std::endl << "Jogador 2 (O), escolha uma posição: ";
    if (!(std::cin >> p && occupy_pos_w_o(p)))
    {
      std::cout << "Posição inválida ou já ocupada! Escolha outra posição." << std::endl;
      ui_request_position_for_o();
    }
  }

  bool ui_game_end (void)
  {
    short r = test_result();

    switch (r)
    {
    case 1:
    case 2:
      std::cout << "Parabéns! Jogador " << r << " venceu!" << std::endl;
      return true;

    case 0:
      return false;

    case -1:
      std::cout << "Empate! Nenhum jogador venceu." << std::endl;
      return true;

    }
    return false;
  }

  void ui_restart_prompt (void)
  {
    char c;

    std::cout << "Deseja reiniciar o jogo? (S/N): ";
    std::cin >> c;

    while (true)
    {
      switch (c)
      {
      case 'S':
      case 's':
        run_program_user_interface();
        return;

      case 'N':
      case 'n':
        return;

      default:
        std::cout << "Opção inválida. Deseja reiniciar o jogo? (S/N): ";
      }
    }
  }

public:

  TicTacToeProgram ()
  {}

  void run_program_user_interface ()
  {
    ui_print_table();
    do
    {
      ui_request_position_for_x();
      ui_print_table();
      if (ui_game_end()) break;

      ui_request_position_for_o();
      ui_print_table();
    } while (!ui_game_end());

    ui_restart_prompt();
  }

};

signed main (void)
{
  TicTacToeProgram().run_program_user_interface();

  return 0;
}
