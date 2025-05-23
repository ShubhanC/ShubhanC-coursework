#include "image_ppm.hpp"

// implement the rest of ImagePPM's functions here
Pixel ImagePPM::GetPixel(int row, int col) const { return pixels_[row][col]; }
int ImagePPM::GetMaxColorValue() const { return max_color_value_; }

void ImagePPM::RemoveHorizontalSeam(const int* seam) {
  ImagePPM copy = ImagePPM(*this);
  Clear();
  pixels_ = new Pixel*[copy.height_ - 1];
  for (int row = 0; row < copy.height_ - 1; row++) {
    pixels_[row] = new Pixel[copy.width_];
  }
  // seam[col] = row
  for (int col = 0; col < copy.width_; col++) {
    int row_new = 0;
    for (int row = 0; row < copy.height_; row++) {
      if (!(seam[col] == row)) {
        pixels_[row_new][col] = copy.pixels_[row][col];
        // << pixels_[row_new][col].GetRed() << std::endl;
        row_new++;
      }
    }
  }
  width_ = copy.width_;
  height_ = copy.height_ - 1;
}

void ImagePPM::RemoveVerticalSeam(const int* seam) {
  ImagePPM copy = ImagePPM(*this);
  Clear();
  pixels_ = new Pixel*[copy.height_];
  for (int row = 0; row < copy.height_; row++) {
    pixels_[row] = new Pixel[copy.width_ - 1];
  }
  for (int row = 0; row < copy.height_; row++) {
    int col_new = 0;
    for (int col = 0; col < copy.width_; col++) {
      if (!(seam[row] == col)) {
        pixels_[row][col_new] = copy.pixels_[row][col];
        // std::cout << pixels_[row][col_new].GetRed() << std::endl;
        col_new++;
      }
    }
  }
  width_ = copy.width_ - 1;
  height_ = copy.height_;
}
// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3" << '\n';
  os << image.GetWidth() << ' ' << image.GetHeight() << '\n';
  os << image.GetMaxColorValue() << '\n';
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      Pixel current_pixel = image.pixels_[row][col];
      os << current_pixel.GetRed() << '\n';
      os << current_pixel.GetGreen() << '\n';
      os << current_pixel.GetBlue() << '\n';
    }
  }
  return os;
}