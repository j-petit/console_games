#include "game.h"
#include <mutex>
#include <ncurses.h>
#include <thread>
#include <unistd.h>

using namespace cgame;

void cgame::printstr(const std::string &my_str) {
  for (char ch : my_str) {
    addch(ch);
  }
}

void Game::logic() {}

void Game::draw() {
  erase();
  // draw playing field
  int i = 0;
  for (auto line : game_screen_v) {
    move(game_origin_y + i, game_origin_x);
    printstr(line);
    i++;
  }
  // draw active block
  for (int i = 0; i < active_block->bounding_square_size; i++) {
    for (int j = 0; j < active_block->bounding_square_size; j++) {
      char value = active_block->get_value(i, j);
      if (value != ' ') {
        mvaddch(game_origin_y + active_block->origin_y + j,
                game_origin_x + active_block->origin_x + i,
                active_block->get_value(i, j));
      }
    }
  }

  move(game_origin_y, game_origin_x + WIDTH + 10);
  printstr("Score");
  move(game_origin_y + 1, game_origin_x + WIDTH + 10);
  printstr(std::to_string(score));
  refresh();
}

void Game::input() {
  if (getch() == '\033') { // if the first value is esc
    getch();               // skip the [
    switch (getch()) {     // the real value
    case 'A':
      // Up
      active_block->rotate();
      if (collision_detection())
        active_block->rotate_back();
      break;
    case 'B':
      // Down
      active_block->origin_y++;
      if (collision_detection()) {
        active_block->origin_y--;
        new_active_block();
      }
      break;
    case 'C':
      // Right
      active_block->origin_x++;
      if (collision_detection())
        active_block->origin_x--;
      break;
    case 'D':
      // Left
      active_block->origin_x--;
      if (collision_detection())
        active_block->origin_x++;
      break;
    }
  }
}

void Game::start() {
  initscr();
  noecho();
  curs_set(0);
  timeout(0);
}

void Game::end() {
  erase();
  mvprintw(0, 0, "You scored ");
  printw("%d", score);
  mvprintw(1, 0, "Press key to exit");
  timeout(-1);
  getch();
  endwin();
}

void Game::run() {
  start();
  Shape shape = block_generator.generate_block();
  TetrisBlock block(shape);
  active_block = std::make_unique<TetrisBlock>(block);

  std::thread thread_move(&Game::move_down, this);
  thread_move.detach();

  while (!quit) {
    usleep(1000);
    input();
    logic();
    draw();
  }
  end();
}

void Game::move_down() {
  while (true) {
    active_block->origin_y++;
    if (collision_detection()) {
      active_block->origin_y--;
      new_active_block();
    }
    usleep(700000);
  }
}

Game::Game() : block_generator(1) {
  for (unsigned int i = 0; i < HEIGHT; ++i) {
    game_screen_v.push_back(generate_empty_line());
  }
  game_screen_v.push_back(std::string(WIDTH + 2, '#'));
}

std::string Game::generate_empty_line() {
    std::string s(WIDTH, ' ');
    s.insert(0, 1, '#');
    s.append("#");
    return s;
}

bool Game::collision_detection() {
  for (int i = 0; i < active_block->bounding_square_size; i++) {
    for (int j = 0; j < active_block->bounding_square_size; j++) {
      if (active_block->get_value(i, j) != ' ') {
        if (game_screen_v.at(active_block->origin_y +
                             j)[active_block->origin_x + i] != ' ') {
          return true;
        }
      }
    }
  }
  return false;
}

void Game::new_active_block() {

  for (int i = 0; i < active_block->bounding_square_size; i++) {
    for (int j = 0; j < active_block->bounding_square_size; j++) {
      char value = active_block->get_value(i, j);
      if (value != ' ') {
        game_screen_v.at(active_block->origin_y +
                         j)[active_block->origin_x + i] = value;
      }
    }
  }

  for (int i = active_block->origin_y;
       i < active_block->origin_y + active_block->bounding_square_size; ++i) {
    if (i < HEIGHT && !(game_screen_v.at(i).find(' ') != std::string::npos)) {
      game_screen_v.erase(game_screen_v.begin() + i);
      game_screen_v.insert(game_screen_v.begin(), generate_empty_line());
      score = score + 50;
    }
  }

  Shape shape = block_generator.generate_block();
  TetrisBlock block(shape);
  m.lock();
  active_block = std::make_unique<TetrisBlock>(block);
  m.unlock();
}
