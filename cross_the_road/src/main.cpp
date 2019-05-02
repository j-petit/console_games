#include "game.h"
#include <iostream>
#include <ncurses.h>
#include <string>

int main() {

  cgame::Game my_game(4, 30);

  my_game.run();

  return 0;
}
