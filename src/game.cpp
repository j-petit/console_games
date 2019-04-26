#include "game.h"
#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <mutex>

using namespace cgame;

Player::Player(int width) : y{0} { x = width / 2; }

void Game::logic() {
  if (player.y == no_lanes + 1) {
    quit = true;
    win = true;
  }
  if (player.y > 0 && player.y <= no_lanes) {
    if (!std::isspace(lanes[player.y - 1].occupied[player.x])) {
      quit = true;
      win = false;
    }
  }
}
void Game::lanes_move() {
  std::mutex mtx;
  while (!quit) {
    for (Lane &lane : lanes) {
      mtx.lock();
      lane.move_lane();
      mtx.unlock();
    }
    usleep(500000);
  }
}
void Game::draw() {
  erase();
  int i = 0;
  for (Lane &lane : lanes) {
    i++;
    move(i, 0);
    printstr(lane.occupied);
    //printstr("hello");
  }
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

  std::thread t1(&Game::lanes_move, this);
  t1.detach();
  
  initscr();
  noecho();
  curs_set(0);
  timeout(0);
  while (!quit) {
    input();
    logic();
    draw();
  }
  erase();
  if (win) {
    mvprintw(0, 0, "You won.");
  } else {
    mvprintw(0, 0, "You lost");
  }

  mvprintw(1, 0, "Press key to exit");
  timeout(-1);
  getch();
  endwin();
}

Game::Game(int no_lanes, int width)
    : no_lanes{no_lanes}, width{width}, player{Player(width)} {

  for (int i = 0; i < no_lanes; i++) {

    lanes.push_back(Lane(width));
  }
}
