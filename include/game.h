#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>

namespace cgame {

class Player {
public:
  int x, y;
  Player(int width);
  virtual ~Player(){};
};

class Lane {
private:
  int width;
  std::default_random_engine generator;
  std::bernoulli_distribution distribution{0.2};

public:
  Lane(int width);
  virtual ~Lane(){};
  void move_lane();
  std::string occupied;
};

class Game {
private:
  int iterations{0};
  bool quit{false};
  bool win{false};
  int no_lanes;
  int width;
  Player player;
  std::vector<Lane> lanes;

public:
  void logic();
  void draw();
  void input();
  void run();
  Game(int no_lanes, int width);
  virtual ~Game(){};
};

class Banner {
private:
  unsigned int width;
  unsigned int row;
  unsigned int pos{0};
  std::string text;

  void inc_pos();

public:
  Banner(unsigned int width, unsigned int row, unsigned int pos,
         std::string const &text)
      : width{width}, row{row}, pos{pos}, text{text} {};
  Banner(unsigned int width, unsigned int row, std::string const &text)
      : width{width}, row{row}, text{text} {};
  virtual ~Banner(){};
  void print_b();
};
}
#endif /* ifndef GAME_H */
