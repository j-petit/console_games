#include "game.h"

using namespace cgame;

BlockGenerator::BlockGenerator(int seed) { generator.seed(seed); }

Shape BlockGenerator::generate_block() {
  Shape shape = static_cast<Shape>(generator() % last);
  return shape;
}
