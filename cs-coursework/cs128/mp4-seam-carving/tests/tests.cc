// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "image_ppm.hpp"
#include "pixel.hpp"
#include "seam_carver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

// Energy
TEST_CASE("Energy image1.ppm", "") {
  std::ifstream infile("./images/image1.ppm");
  ImagePPM image;
  infile >> image;
  infile.close();
  SeamCarver carver(image);
  REQUIRE(carver.GetEnergy(0, 0) == 75);
  REQUIRE(carver.GetEnergy(2, 3) == 450);
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Seam Algorithm Check

TEST_CASE("Horiz Seam image1.ppm", "") {
  std::ifstream infile("./images/image1.ppm");
  ImagePPM image;
  infile >> image;
  infile.close();
  SeamCarver carver(image);
  for (int row = 0; row < carver.GetHeight(); row++) {
    for (int col = 0; col < carver.GetWidth(); col++) {
      std::cout << carver.GetEnergy(row, col) << std::endl;
    }
  }
  int* horiz_seam_check = new int[carver.GetWidth()];
  horiz_seam_check[0] = 1;
  horiz_seam_check[1] = 1;
  horiz_seam_check[2] = 1;
  horiz_seam_check[3] = 1;
  REQUIRE(horiz_seam_check[0] == carver.GetHorizontalSeam()[0]);
  REQUIRE(horiz_seam_check[3] == carver.GetHorizontalSeam()[3]);
  delete[] horiz_seam_check;
}

// Horiz Seam Carving
TEST_CASE("Horiz Seam Carving image1.ppm", "") {
  std::ifstream infile("./images/image1.ppm");
  ImagePPM image;
  infile >> image;
  infile.close();
  SeamCarver carver(image);

  std::ifstream infile1(
      "./images/"
      "image1_horiz_carve.ppm");
  ImagePPM image_check;
  infile1 >> image_check;
  infile1.close();
  SeamCarver carver_check(image_check);
  carver.RemoveHorizontalSeam();
  REQUIRE(carver.GetImage().GetPixel(0, 0) ==
          carver_check.GetImage().GetPixel(0, 0));
  REQUIRE(carver.GetImage().GetPixel(1, 3) ==
          carver_check.GetImage().GetPixel(1, 3));
}

// Vert Seam Carving
TEST_CASE("Vert Seam Carving image1.ppm", "") {
  std::ifstream infile("./images/image1.ppm");
  ImagePPM image;
  infile >> image;
  infile.close();
  SeamCarver carver(image);

  std::ifstream infile1(
      "./images/"
      "image1_vert_carve.ppm");
  ImagePPM image_check;
  infile1 >> image_check;
  infile1.close();
  SeamCarver carver_check(image_check);
  carver.RemoveVerticalSeam();
  REQUIRE(carver.GetImage().GetPixel(0, 0) ==
          carver_check.GetImage().GetPixel(0, 0));
  REQUIRE(carver.GetImage().GetPixel(2, 2) ==
          carver_check.GetImage().GetPixel(2, 2));
  REQUIRE(true == true);
}

TEST_CASE("Ocean Carving", "") {
  std::ifstream infile("./images/ocean.ppm");
  ImagePPM image;
  infile >> image;
  infile.close();
  SeamCarver carver(image);

  std::ifstream infile1(
      "./images/"
      "ocean-carved.ppm");
  ImagePPM image_check;
  infile1 >> image_check;
  infile1.close();
  SeamCarver carver_check(image_check);
  for (unsigned int i = 0; i < 170; i++) {
    carver.RemoveVerticalSeam();
  }
  for (unsigned int j = 0; j < 50; j++) {
    carver.RemoveHorizontalSeam();
  }
  REQUIRE(carver.GetImage().GetPixel(0, 0) ==
          carver_check.GetImage().GetPixel(0, 0));
  REQUIRE(carver.GetImage().GetPixel(234, 336) ==
          carver_check.GetImage().GetPixel(234, 336));
  REQUIRE(carver.GetImage().GetPixel(234, 0) ==
          carver_check.GetImage().GetPixel(234, 0));
  REQUIRE(carver.GetImage().GetPixel(0, 336) ==
          carver_check.GetImage().GetPixel(0, 336));
  REQUIRE(carver.GetImage().GetPixel(117, 168) ==
          carver_check.GetImage().GetPixel(117, 168));
  REQUIRE(carver.GetImage().GetPixel(143, 142) ==
          carver_check.GetImage().GetPixel(143, 142));
  REQUIRE(true == true);
}