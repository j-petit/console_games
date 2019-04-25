#include "game.h"
#include <random>

using namespace cgame;

Lane::Lane(int width) : width{width} { occupied.resize(width, ' '); }

void Lane::move_lane() {
  std::default_random_engine generator;
  std::bernoulli_distribution distribution(0.5);

  if (distribution(generator)) {
  }
  else {
  }
}
