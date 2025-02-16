#include "grayscale_image.hpp"
// shade_of_gray = std::round((elevation_point - min_ele) / (max_ele - min_ele)
// * 255)

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  height_ = dataset.Height();
  width_ = dataset.Width();
  double min_ele = dataset.MinEle();
  double max_ele = dataset.MaxEle();
  const std::vector<std::vector<int>>& data = dataset.GetData();
  image_ = ImageCreation(data, min_ele, max_ele);
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t height,
                               size_t width):
    width_(width), height_(height) {
  ElevationDataset dataset(filename, width, height);
  const std::vector<std::vector<int>>& data = dataset.GetData();
  height_ = height;
  width_ = width;
  double min_ele = dataset.MinEle();
  double max_ele = dataset.MaxEle();
  image_ = ImageCreation(data, min_ele, max_ele);
}

void GrayscaleImage::ToPpm(const std::string& ppmFileName) const {
  std::ofstream ofs{ppmFileName};
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

std::vector<std::vector<Color>> GrayscaleImage::ImageCreation(
    const std::vector<std::vector<int>>& data,
    double min_ele,
    double max_ele) const {
  std::vector<std::vector<Color>> image(
      height_, std::vector<Color>(width_, Color(0, 0, 0)));
  for (unsigned int i = 0; i < height_; i++) {
    for (unsigned int j = 0; j < width_; j++) {
      double elevation_point = data.at(i).at(j);
      double shade_of_gray = 0;
      if (!(min_ele == max_ele)) {
        shade_of_gray = std::round((elevation_point - min_ele) /
                                   (max_ele - min_ele) * kMaxColorValue);
      }
      if ((shade_of_gray <= kMaxColorValue) && (shade_of_gray >= 0)) {
        image.at(i).at(j) = Color(shade_of_gray, shade_of_gray, shade_of_gray);
      } else {
        throw std::invalid_argument("shade of gray is an invalid value");
      }
    }
  }
  return image;
}