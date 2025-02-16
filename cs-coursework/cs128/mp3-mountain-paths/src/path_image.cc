#include "path_image.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = image.Width();
  height_ = image.Height();
  path_image_ = image.GetImage();
  for (unsigned int i = 0; i < height_; i++) {
    Path path = MakePath(dataset, width_, i);
    if (i == 0) {
      best_path_ = path;
    }
    paths_.push_back(path);
    if (path.EleChange() < best_path_.EleChange()) {
      best_path_ = path;
    }
  }
  unsigned int correct_path = 0;
  for (unsigned int i = 0; i < paths_.size(); i++) {
    std::vector<size_t> path_placer = paths_[i].GetPath();
    if (paths_[i].StartingRow() == best_path_.StartingRow()) {
      correct_path = i;
    } else {
      for (unsigned int j = 0; j < path_placer.size(); j++) {
        size_t index = path_placer[j];
        path_image_[index][j] = Color(kRedR, kRedG, kRedB);
      }
    }
  }
  std::vector<size_t> path_placer = paths_[correct_path].GetPath();
  for (unsigned int j = 0; j < path_placer.size(); j++) {
    size_t index = path_placer[j];
    path_image_[index][j] = Color(kGreenR, kGreenG, kGreenB);
  }
}

Path PathImage::MakePath(const ElevationDataset& dataset,
                         size_t width,
                         size_t starting_row) const {
  Path path(width, starting_row);
  unsigned int j = starting_row;
  std::vector<std::vector<int>> data = dataset.GetData();
  for (unsigned int i = 1; i < width; i++) {
    unsigned int next_index = j;
    int ele_change = abs(data[j][i - 1] - data[j][i]);
    if (j == 0) {
      int ele_change_down = abs(data[j][i - 1] - data[j + 1][i]);
      if (ele_change > ele_change_down) next_index = j + 1;
    } else if (j == height_ - 1) {
      int ele_change_up = abs(data[j][i - 1] - data[j - 1][i]);
      if (ele_change > ele_change_up) next_index = j - 1;
    } else if ((j > 0) && (j < height_ - 1)) {
      int ele_change_up = abs(data[j][i - 1] - data[j - 1][i]);
      int ele_change_down = abs(data[j][i - 1] - data[j + 1][i]);
      if (ele_change > ele_change_down) {
        next_index = j + 1;
        ele_change = ele_change_down;
      }
      if (ele_change > ele_change_up) {
        next_index = j - 1;
        ele_change = ele_change_up;
      }
    }
    path.SetLoc(i, next_index);
    path.IncEleChange(ele_change);
    j = next_index;
  }
  return path;
}

void PathImage::ToPpm(const std::string& fileName) const {
  std::ofstream ofs{fileName};
  ofs << "P3\n";
  ofs << width_ << ' ' << height_ << '\n';
  ofs << kMaxColorValue << '\n';
  for (unsigned int i = 0; i < height_; i++) {
    for (unsigned int j = 0; j < width_; j++) {
      ofs << ColorAt(i, j).Red() << ' ' << ColorAt(i, j).Green() << ' '
          << ColorAt(i, j).Blue() << ' ';
    }
    ofs << '\n';
  }
}