#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"
bool CompareFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1);
  std::ifstream f2(p2);

  if (f1.fail() || f2.fail()) {
    return false;  // file problem
  }

  std::string f1_read;
  std::string f2_read;
  while (f1.good() || f2.good()) {
    f1 >> f1_read;
    f2 >> f2_read;
    if (f1_read != f2_read || (f1.good() && !f2.good()) ||
        (!f1.good() && f2.good()))
      return false;
  }
  return true;
}

// Elevation Dataset Tests

TEST_CASE("Elevation Dataset forward 2-3", "[ED-forward-2-3]") {
  const std::string kTestInputFile =
      "./example-data/ex_input_data/forward-2-3.dat";
  constexpr size_t kTestInputFileWidth = 2;
  constexpr size_t kTestInputFileHeight = 3;
  std::vector<std::vector<int>> correct_data = {{9, 12}, {8, 10}, {7, 14}};
  ElevationDataset ed(
      kTestInputFile, kTestInputFileWidth, kTestInputFileHeight);
  std::vector<std::vector<int>> ed_data = ed.GetData();
  REQUIRE(ed_data == correct_data);
  REQUIRE(ed.MaxEle() == 14);
  REQUIRE(ed.MinEle() == 7);
}

TEST_CASE("Elevation Dataset prompt_5w_2h", "[ED-prompt_5w_2h]") {
  const std::string kTestInputFile =
      "./example-data/ex_input_data/prompt_5w_2h.dat";
  constexpr size_t kTestInputFileWidth = 5;
  constexpr size_t kTestInputFileHeight = 2;
  std::vector<std::vector<int>> correct_data = {{10, 20, 30, 40, 35},
                                                {25, 20, 15, 18, 20}};
  ElevationDataset ed(
      kTestInputFile, kTestInputFileWidth, kTestInputFileHeight);
  std::vector<std::vector<int>> ed_data = ed.GetData();
  REQUIRE(ed_data == correct_data);
  REQUIRE(ed.MaxEle() == 40);
  REQUIRE(ed.MinEle() == 10);
}

// Grayscale Image Tests

TEST_CASE("PPM Example Test: Grayscale image from prompt_5w_2h.ppm",
          "[ppm_ex_grayscale_prompt_5w_2h]") {
  const std::string kStudentOutput =
      "./student_out/ex_grayscale_prompt_5w_2h.ppm";
  const std::string kTestFile = "./example-data/ex_input_data/prompt_5w_2h.dat";
  const std::string kGroundTruth =
      "./example-data/ex_output_grayscale/prompt_5w_2h.ppm";
  constexpr size_t kTestFileWidth = 5;
  constexpr size_t kTestFileHeight = 2;
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  gi.ToPpm(kStudentOutput);
  REQUIRE(CompareFiles(kStudentOutput, kGroundTruth));
}

TEST_CASE("Example Grayscale Data Test", "[gi-forward-2-3]") {
  const std::string kTestFile = "./example-data/ex_input_data/forward-2-3.dat";
  constexpr size_t kTestFileWidth = 2;
  constexpr size_t kTestFileHeight = 3;
  const std::vector<std::vector<Color>> kImageGroundTruth = {
      {Color(73, 73, 73), Color(182, 182, 182)},
      {Color(36, 36, 36), Color(109, 109, 109)},
      {Color(0, 0, 0), Color(255, 255, 255)}};

  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  const auto& student_image_data = gi.GetImage();

  // Are the vectors kImageGroundTruth and student_image_data
  // identical? If so, pass test.
  REQUIRE(std::equal(student_image_data.begin(),
                     student_image_data.end(),
                     kImageGroundTruth.begin()));
}

TEST_CASE("PPM Example Test: Grayscale image from map-input-w51-h55.ppm",
          "[ppm_map-input-w51-h55]") {
  const std::string kStudentOutput =
      "./student_out/ex_grayscale_map-input-w51-h55.ppm";
  const std::string kTestFile =
      "./example-data/ex_input_data/map-input-w51-h55.dat";
  const std::string kGroundTruth =
      "./example-data/ex_output_grayscale/map-input-w51-h55.ppm";
  constexpr size_t kTestFileWidth = 51;
  constexpr size_t kTestFileHeight = 55;
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  gi.ToPpm(kStudentOutput);
  REQUIRE(CompareFiles(kStudentOutput, kGroundTruth));
}

// PathImage

TEST_CASE("Example Test: Path image from prompt_5w_2h.ppm",
          "ex_path_image_prompt_5w_2h]") {
  const std::string kStudentOutput =
      "./student_out/ex_path_image_prompt_5w_2h.ppm";
  const std::string kTestFile = "./example-data/ex_input_data/prompt_5w_2h.dat";
  const std::string kGroundTruth =
      "./example-data/ex_output_paths/prompt_5w_2h.ppm";
  constexpr size_t kTestFileWidth = 5;
  constexpr size_t kTestFileHeight = 2;
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  pi.ToPpm(kStudentOutput);
  REQUIRE(CompareFiles(kStudentOutput, kGroundTruth));
}

TEST_CASE("Example Test: Path image from map-input-w51-h55.ppm",
          "ex_path_image_map-input-w51-h55]") {
  const std::string kStudentOutput =
      "./student_out/ex_path_image_map-input-w51-h55.ppm";
  const std::string kTestFile =
      "./example-data/ex_input_data/map-input-w51-h55.dat";
  const std::string kGroundTruth =
      "./example-data/ex_output_paths/map-input-w51-h55.ppm";
  constexpr size_t kTestFileWidth = 51;
  constexpr size_t kTestFileHeight = 55;
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  pi.ToPpm(kStudentOutput);
  REQUIRE(CompareFiles(kStudentOutput, kGroundTruth));
}

/* TEST_CASE("Example Test: Path image from map-input-w480-h480.ppm",
          "ex_path_image_map-input-w480-h480]") {
  const std::string kStudentOutput =
      "./student_out/ex_path_image_map-input-w480-h480.ppm";
  const std::string kTestFile =
      "./example-data/ex_input_data/map-input-w480-h480.dat";
  const std::string kGroundTruth =
      "./example-data/ex_output_paths/path-input-480-480.ppm";
  constexpr size_t kTestFileWidth = 480;
  constexpr size_t kTestFileHeight = 480;
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  pi.ToPpm(kStudentOutput);
  REQUIRE(CompareFiles(kStudentOutput, kGroundTruth));
} */

// Paths

TEST_CASE("Example Navigation Test: Go forward.", "[forward-2-3]") {
  const std::string kTestFile = "./example-data/ex_input_data/forward-2-3.dat";
  constexpr size_t kTestFileWidth = 2;
  constexpr size_t kTestFileHeight = 3;
  const std::vector<size_t> kPathToEvaluateGroundTruth = {1, 1};
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);

  // Let's get the path's vector from `pi`
  const auto& student_paths = pi.Paths();

  // We want to analyze the program's behavior on the path starting from Row 1,
  // so let's get the path we created for that row.
  const auto& student_path_to_evaluate = student_paths.at(1).GetPath();

  // Now let's compare that path to the expected path stored in
  // kPathToEvaluateGroundTruth.
  REQUIRE(std::equal(student_path_to_evaluate.begin(),
                     student_path_to_evaluate.end(),
                     kPathToEvaluateGroundTruth.begin()));
}

TEST_CASE("Example Navigation Test: Go Up.", "[forward-up-2-3]") {
  const std::string kTestFile =
      "./example-data/ex_input_data/forward-up-2-3.dat";
  constexpr size_t kTestFileWidth = 2;
  constexpr size_t kTestFileHeight = 3;
  const std::vector<size_t> kPathToEvaluateGroundTruth = {1, 0};
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  const auto& student_paths = pi.Paths();
  const auto& student_path_to_evaluate = student_paths.at(1).GetPath();
  REQUIRE(std::equal(student_path_to_evaluate.begin(),
                     student_path_to_evaluate.end(),
                     kPathToEvaluateGroundTruth.begin()));
}

// Full Path

TEST_CASE("Example Navigation Test: Full Path 5x2.", "[prompt_5w_2h]") {
  const std::string kTestFile = "./example-data/ex_input_data/prompt_5w_2h.dat";
  constexpr size_t kTestFileWidth = 5;
  constexpr size_t kTestFileHeight = 2;
  const std::vector<size_t> kPathToEvaluateGroundTruth = {1, 1, 1, 1, 1};
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  const auto& student_path = pi.BestPath();
  const auto& student_path_to_evaluate = student_path.GetPath();
  REQUIRE(student_path_to_evaluate == kPathToEvaluateGroundTruth);
}