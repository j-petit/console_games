#include "game.h"
#include <ncurses.h>

using namespace cgame;

Player::Player(int width) : y{0} { x = width / 2; }

void Game::logic() {
  if (player.y == no_lanes + 1) {
    quit = true;
  }
}
void Game::draw() {
  erase();
  mvaddch(player.y, player.x, 88);
  refresh();
}
void Game::input() {
  if (getch() == '\033') { // if the first value is esc
    getch();               // skip the [
    switch (getch()) {     // the real value
    case 'A':
      // Up
      if (player.y > 0) {
        player.y--;
      }
      break;
    case 'B':
      // Down
      if (player.y <= no_lanes) {
        player.y++;
      }
      break;
    case 'C':
      // Right
      if (player.x < width) {
        player.x++;
      }
      break;
    case 'D':
      if (player.x > 0) {
        player.x--;
      }
      // Left
      break;
    }
  }
}
void Game::run() {
  initscr();
  noecho();
  curs_set(0);
  while (!quit) {
    input();
    logic();
    draw();
  }
  erase();
  mvprintw(0, 0, "Won");
  mvprintw(1, 0, "Press key to exit");
  timeout(-1);
  getch();
  endwin();
}

Game::Game(int no_lanes, int width)
    : no_lanes{no_lanes}, width{width}, player{Player(width)} {}
