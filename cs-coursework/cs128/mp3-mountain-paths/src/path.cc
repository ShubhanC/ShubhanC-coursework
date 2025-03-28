#include "path.hpp"

Path::Path(size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  path_ = std::vector<size_t>(length);
  path_[0] = starting_row;
}

void Path::IncEleChange(unsigned int value) { ele_change_ += value; }

void Path::SetLoc(size_t column, size_t row) { path_.at(column) = row; }