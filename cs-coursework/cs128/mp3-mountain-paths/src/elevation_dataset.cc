#include "elevation_dataset.hpp"

#include <iostream>

ElevationDataset::ElevationDataset(const std::string& fileName,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs(fileName);
  int value = 0;
  int max_ele = 0;
  int min_ele = 0;
  std::vector<std::vector<int>> data(height, std::vector<int>(width, 0));
  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      ifs >> value;
      if (ifs.fail()) {
        throw std::runtime_error(
            "read format error or too little data for the given height and "
            "width");
      }
      data.at(i).at(j) = value;
      if ((i == 0) && (j == 0)) {
        max_ele = value;
        min_ele = value;
      }
      if (value > max_ele) {
        max_ele = value;
      }
      if (value < min_ele) {
        min_ele = value;
      }
    }
  }
  ifs >> value;
  if (ifs.good()) {
    throw std::runtime_error(
        "there is too much data for the given height and width");
  }
  max_ele_ = max_ele;
  min_ele_ = min_ele;
  data_ = data;
}