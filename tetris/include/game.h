#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <ncurses.h>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

namespace cgame {

const unsigned int WIDTH = 15;
const unsigned int HEIGHT = 20;

void printstr(const std::string &my_str);

enum Shape { Bar, Square, L, L_flipped, Z, Z_flipped, D, last };
enum class Orientation { Up, Down, Right, Left };

class TetrisBlock {
public:
  TetrisBlock(Shape shape);
  virtual ~TetrisBlock() {};
  void rotate();
  void rotate_back();
  int origin_x{WIDTH/2};
  int origin_y{0};
  char get_value(int x, int y);
  int bounding_square_size;
private:
  Shape type;
  std::vector<char> shape_v;
  Orientation orientation{Orientation::Up};
};

class BlockGenerator {
public:
  BlockGenerator(int seed);
  virtual ~BlockGenerator() {};
  Shape generate_block();
private:
  std::default_random_engine generator;
};

class Game {
private:
  bool quit{false};
  std::vector<std::string> game_screen_v;
  int score{0};
  int game_origin_x{5};
  int game_origin_y{3};
  BlockGenerator block_generator;
  void move_down();
  bool collision_detection();
  void new_active_block();
  void detect_full_line();
  std::mutex m;
  std::string generate_empty_line();
public:
  void start();
  void logic();
  void draw();
  void input();
  void run();
  void end();
  Game();
  virtual ~Game() {};
  std::unique_ptr<TetrisBlock> active_block;
};

}
#endif /* ifndef GAME_H */
