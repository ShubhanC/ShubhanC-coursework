#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

class GrayscaleImage {
public:
  // write behavior declarations here; define in grayscale_image.cc.
  GrayscaleImage(const ElevationDataset& dataset);
  GrayscaleImage(const std::string& filename, size_t height, size_t width);
  void ToPpm(const std::string& name) const;
  const Color& ColorAt(int row, int col) const {
    return image_.at(row).at(col);
  };
  const std::vector<std::vector<Color>>& GetImage() const { return image_; };
  size_t Width() const { return width_; };
  size_t Height() const { return height_; };
  unsigned int MaxColorValue() const { return kMaxColorValue; };

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int kMaxColorValue = 255;
  std::vector<std::vector<Color>> ImageCreation(
      const std::vector<std::vector<int>>& data,
      double min_ele,
      double max_ele) const;
};

#endif