#include "game.h"

using namespace cgame;

void TetrisBlock::rotate() {
  switch (orientation) {
  case Orientation::Up:
    orientation = Orientation::Right;
    break;
  case Orientation::Right:
    orientation = Orientation::Down;
    break;
  case Orientation::Down:
    orientation = Orientation::Left;
    break;
  case Orientation::Left:
    orientation = Orientation::Up;
    break;
  default:
    throw std::invalid_argument("Received wrong orientation");
  }
}

void TetrisBlock::rotate_back() {
  switch (orientation) {
  case Orientation::Up:
    orientation = Orientation::Left;
    break;
  case Orientation::Right:
    orientation = Orientation::Up;
    break;
  case Orientation::Down:
    orientation = Orientation::Right;
    break;
  case Orientation::Left:
    orientation = Orientation::Down;
    break;
  default:
    throw std::invalid_argument("Received wrong orientation");
  }
}

TetrisBlock::TetrisBlock(Shape shape) : type{shape} {
  switch (shape) {
  case Shape::Bar:
    bounding_square_size = 4;
    for (int i = 0; i < bounding_square_size * bounding_square_size; ++i) {
      shape_v.push_back(' ');
    }
    this->shape_v.at(1) = 'I';
    this->shape_v.at(5) = 'I';
    this->shape_v.at(9) = 'I';
    this->shape_v.at(13) = 'I';
    break;
  case Shape::Square:
    bounding_square_size = 2;
    for (int i = 0; i < bounding_square_size * bounding_square_size; ++i) {
      shape_v.push_back(' ');
    }
    this->shape_v.at(0) = 'O';
    this->shape_v.at(1) = 'O';
    this->shape_v.at(2) = 'O';
    this->shape_v.at(3) = 'O';
    break;
  case Shape::L:
    bounding_square_size = 3;
    for (int i = 0; i < bounding_square_size * bounding_square_size; ++i) {
      shape_v.push_back(' ');
    }
    this->shape_v.at(1) = 'L';
    this->shape_v.at(4) = 'L';
    this->shape_v.at(7) = 'L';
    this->shape_v.at(6) = 'L';
    break;
  case Shape::L_flipped:
    bounding_square_size = 3;
    for (int i = 0; i < bounding_square_size * bounding_square_size; ++i) {
      shape_v.push_back(' ');
    }
    this->shape_v.at(1) = 'L';
    this->shape_v.at(4) = 'L';
    this->shape_v.at(7) = 'L';
    this->shape_v.at(8) = 'L';
    break;
  case Shape::Z:
    bounding_square_size = 3;
    for (int i = 0; i < bounding_square_size * bounding_square_size; ++i) {
      shape_v.push_back(' ');
    }
    this->shape_v.at(3) = 'Z';
    this->shape_v.at(4) = 'Z';
    this->shape_v.at(7) = 'Z';
    this->shape_v.at(8) = 'Z';
    break;
  case Shape::Z_flipped:
    bounding_square_size = 3;
    for (int i = 0; i < bounding_square_size * bounding_square_size; ++i) {
      shape_v.push_back(' ');
    }
    this->shape_v.at(4) = 'Z';
    this->shape_v.at(5) = 'Z';
    this->shape_v.at(7) = 'Z';
    this->shape_v.at(8) = 'Z';
    break;
  case Shape::D:
    bounding_square_size = 3;
    for (int i = 0; i < bounding_square_size * bounding_square_size; ++i) {
      shape_v.push_back(' ');
    }
    this->shape_v.at(1) = 'D';
    this->shape_v.at(4) = 'D';
    this->shape_v.at(5) = 'D';
    this->shape_v.at(7) = 'D';
    break;
  default:
    throw std::invalid_argument("Received wrong shape");
  }
}

char TetrisBlock::get_value(int x, int y) {
  char return_char;
  switch (orientation) {
  case Orientation::Up:
    return_char = this->shape_v.at(x + bounding_square_size * y);
    break;
  case Orientation::Left:
    return_char =
        this->shape_v.at(bounding_square_size - 1 - y + bounding_square_size * x);
    break;
  case Orientation::Down:
    return_char = this->shape_v.at(bounding_square_size * bounding_square_size -
                                1 - x - bounding_square_size * y);
    break;
  case Orientation::Right:
    return_char =
        this->shape_v.at((bounding_square_size - 1) * bounding_square_size -
                      bounding_square_size * x + y);
    break;
  }
  return return_char;
}
