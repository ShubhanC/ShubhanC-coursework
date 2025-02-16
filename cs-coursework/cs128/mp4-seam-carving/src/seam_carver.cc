#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here
int SeamCarver::GetDeltaCol(int row, int col) const {
  int col_left = 0;
  int col_right = 0;
  if (col == 0) {
    col_left = width_ - 1;
    col_right = col + 1;
  } else if (col == width_ - 1) {
    col_left = col - 1;
    col_right = 0;
  } else {
    col_left = col - 1;
    col_right = col + 1;
  }
  int r_left = image_.GetPixel(row, col_left).GetRed();
  int r_right = image_.GetPixel(row, col_right).GetRed();
  int g_left = image_.GetPixel(row, col_left).GetGreen();
  int g_right = image_.GetPixel(row, col_right).GetGreen();
  int b_left = image_.GetPixel(row, col_left).GetBlue();
  int b_right = image_.GetPixel(row, col_right).GetBlue();
  int d_col = ((r_left - r_right) * (r_left - r_right)) +
              ((g_left - g_right) * (g_left - g_right)) +
              ((b_left - b_right) * (b_left - b_right));
  return d_col;
}

int SeamCarver::GetDeltaRow(int row, int col) const {
  int row_up = 0;
  int row_down = 0;
  if (row == 0) {
    row_up = height_ - 1;
    row_down = row + 1;
  } else if (row == height_ - 1) {
    row_up = row - 1;
    row_down = 0;
  } else {
    row_up = row - 1;
    row_down = row + 1;
  }
  int r_up = image_.GetPixel(row_up, col).GetRed();
  int r_down = image_.GetPixel(row_down, col).GetRed();
  int g_up = image_.GetPixel(row_up, col).GetGreen();
  int g_down = image_.GetPixel(row_down, col).GetGreen();
  int b_up = image_.GetPixel(row_up, col).GetBlue();
  int b_down = image_.GetPixel(row_down, col).GetBlue();
  int d_row = ((r_up - r_down) * (r_up - r_down)) +
              ((g_up - g_down) * (g_up - g_down)) +
              ((b_up - b_down) * (b_up - b_down));
  return d_row;
}

int SeamCarver::GetEnergy(int row, int col) const {
  int d_row = GetDeltaRow(row, col);
  int d_col = GetDeltaCol(row, col);
  return d_row + d_col;
}

int SeamCarver::FindStartingRow(int** values, int best_value) const {
  int starting_row = 0;
  for (int row = 0; row < height_; row++) {
    if (values[row][0] == best_value) {
      starting_row = row;
      break;
    }
  }
  return starting_row;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** values = new int*[height_];
  int* seam = new int[height_];
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
    for (int col = 0; col < width_; col++) {
      values[row][col] = GetEnergy(row, col);
    }
  }
  int best_value = FindHorizontalSeam(values);
  int starting_row = FindStartingRow(values, best_value);

  seam[0] = starting_row;
  for (int col = 1; col < width_; col++) {
    int right = values[starting_row][col];
    if (starting_row == 0) {
      int down = values[starting_row + 1][col];
      if (down < right) starting_row++;
    } else if (starting_row == height_ - 1) {
      int up = values[starting_row - 1][col];
      if (up < right) starting_row--;
    } else {
      int down = values[starting_row + 1][col];
      int up = values[starting_row - 1][col];
      if ((up < right) && (up <= down))
        starting_row--;
      else if ((down < right) && (down < up))
        starting_row++;
    }
    seam[col] = starting_row;
  }
  for (int row = 0; row < height_; row++) {
    delete[] values[row];
  }
  delete[] values;
  return seam;
}

int SeamCarver::FindStartingCol(int** values, int best_value) const {
  int starting_col = 0;
  for (int col = 0; col < width_; col++) {
    if (values[0][col] == best_value) {
      starting_col = col;
      break;
    }
  }
  return starting_col;
}

int* SeamCarver::GetVerticalSeam() const {
  int** values = new int*[height_];
  int* seam = new int[height_];
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
    for (int col = 0; col < width_; col++) {
      values[row][col] = GetEnergy(row, col);
    }
  }
  int best_value = FindVerticalSeam(values);
  int starting_col = FindStartingCol(values, best_value);

  seam[0] = starting_col;
  for (int row = 1; row < height_; row++) {
    int down = values[row][starting_col];
    if (starting_col == 0) {
      int right = values[row][starting_col + 1];
      if (right < down) starting_col++;
    } else if (starting_col == width_ - 1) {
      int left = values[row][starting_col - 1];
      if (left < down) starting_col--;
    } else {
      int right = values[row][starting_col + 1];
      int left = values[row][starting_col - 1];
      if ((left < down) && (left <= right))
        starting_col--;
      else if ((right < left) && (right < down))
        starting_col++;
    }
    seam[row] = starting_col;
  }
  for (int row = 0; row < height_; row++) {
    delete[] values[row];
  }
  delete[] values;
  return seam;
}

int SeamCarver::FindHorizontalSeam(int**& values) const {
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      int right = GetEnergy(row, col + 1);
      int up = right + 1;
      int down = right + 1;
      if (row > 0) {
        up = GetEnergy(row - 1, col + 1);
      }
      if (row < height_ - 1) {
        down = GetEnergy(row + 1, col + 1);
      }
      int row_rightof_value = right;
      if (up < row_rightof_value && up <= down) {
        row_rightof_value = up;
      } else if (down < row_rightof_value && down < up) {
        row_rightof_value = down;
      }
      values[row][col] = GetEnergy(row, col) + row_rightof_value;
      // middle > left > right
      // if ((!(row == 0)) && (!(row == height_ - 1)))
    }
  }
  int best_value = values[0][0];
  for (int row = 0; row < height_; row++) {
    if (values[row][0] < best_value) best_value = values[row][0];
  }
  return best_value;
}
int SeamCarver::FindVerticalSeam(int**& values) const {
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      int down = GetEnergy(row + 1, col);
      int left = down + 1;
      int right = down + 1;
      if (col > 0) {
        left = GetEnergy(row + 1, col - 1);
      }
      if (col < width_ - 1) {
        right = GetEnergy(row + 1, col + 1);
      }
      int row_below_value = down;
      if ((left < down) && (left <= right)) {
        row_below_value = left;
      } else if ((right < left) && (right < down)) {
        row_below_value = right;
      }
      values[row][col] = GetEnergy(row, col) + row_below_value;
      // middle > left > right
      // if ((!(col == 0)) && (!(col == width_ - 1)))
    }
  }
  int best_value = values[0][0];
  for (int col = 0; col < width_; col++) {
    if (values[0][col] < best_value) best_value = values[0][col];
  }
  return best_value;
}

void SeamCarver::RemoveVerticalSeam() {
  int* seam = GetVerticalSeam();
  /*for (int i = 0; i < height_; i++) {
    std::cout << seam[i] << std::endl;
  }*/
  image_.RemoveVerticalSeam(seam);
  delete[] seam;
  height_ = image_.GetHeight();
  width_ = image_.GetWidth();
}

void SeamCarver::RemoveHorizontalSeam() {
  int* seam = GetHorizontalSeam();
  /*for (int i = 0; i < width_; i++) {
    std::cout << seam[i] << std::endl;
  }*/
  image_.RemoveHorizontalSeam(seam);
  delete[] seam;
  height_ = image_.GetHeight();
  width_ = image_.GetWidth();
}
// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}