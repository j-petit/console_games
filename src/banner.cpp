#include "game.h"
#include <iostream>

using namespace cgame;

void Banner::inc_pos() {
  if (pos < width) {
    pos++;
  } else {
    pos = 0;
  }
}

void Banner::print_b() {

  move(row, pos - 1);
  printw(" ");

  move(row, pos);

  // amount of out of width
  int diff = width - text.length() - pos;

  if (diff < 0) {
    printstr(text.substr(0, text.length() + 1 * diff));
    move(row, 0);
    printstr(text.substr(text.length() + 1 * diff));
  } else {
    printstr(text);
  }

  inc_pos();
}
