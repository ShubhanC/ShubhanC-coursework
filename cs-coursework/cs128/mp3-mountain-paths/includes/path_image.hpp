#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  void ToPpm(const std::string& name) const;
  Color ColorAt(unsigned int row, unsigned int column) const {
    return path_image_.at(row).at(column);
  };
  const std::vector<Path>& Paths() const { return paths_; };
  const std::vector<std::vector<Color>>& GetPathImage() const {
    return path_image_;
  };
  unsigned int MaxColorValue() const { return kMaxColorValue; };
  size_t Width() const { return width_; };
  size_t Height() const { return height_; };
  Path BestPath() const { return best_path_; };

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  Path best_path_ = Path(1, 0);
  static const int kRedR = 252;
  static const int kRedG = 25;
  static const int kRedB = 63;
  static const int kGreenR = 31;
  static const int kGreenG = 253;
  static const int kGreenB = 13;
  Path MakePath(const ElevationDataset& dataset,
                size_t width,
                size_t starting_row) const;
};

#endif