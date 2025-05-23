#ifndef ELEVATION_DATASET_H
#define ELEVATION_DATASET_H

#include <cstdlib>  // for size_t
#include <fstream>
#include <stdexcept>
#include <vector>

class ElevationDataset {
public:
  // write behavior declarations here; define in elevation_dataset.cc.
  ElevationDataset(const std::string& filename, size_t width, size_t height);
  size_t Width() const { return width_; };
  size_t Height() const { return height_; };
  int MinEle() const { return min_ele_; };
  int MaxEle() const { return max_ele_; };
  const std::vector<std::vector<int>>& GetData() const { return data_; };
  int DatumAt(size_t row, size_t col) const { return data_[row][col]; }

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<int>> data_;
  int max_ele_;
  int min_ele_;
};

#endif