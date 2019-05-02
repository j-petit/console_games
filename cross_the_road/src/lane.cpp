#include "game.h"
#include <random>

using namespace cgame;

Lane::Lane(int width) : width{width} { 
  occupied.resize(width, ' ');
  generator.seed(rand());
}

void Lane::move_lane() {

  if (distribution(generator)) {
    occupied = "o" + occupied.substr(0, occupied.length() - 1);
  }
  else {
    occupied = " " + occupied.substr(0, occupied.length() - 1);
  }
}
