#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  const std::string kTestInputFile =
      "./example-data/ex_input_data/prompt_5w_2h.dat";
  constexpr size_t kTestInputFileWidth = 5;
  constexpr size_t kTestInputFileHeight = 2;
  std::string k_test_output_file = "./student_out/prompt_5w_2h_test.ppm";
  std::string k_test_path_file = "./student_out/prompt_5w_2h_test_path.ppm";

  ElevationDataset ed(
      kTestInputFile, kTestInputFileWidth, kTestInputFileHeight);
  GrayscaleImage gi2(ed);
  gi2.ToPpm(k_test_output_file);
  PathImage pi(gi2, ed);
  pi.ToPpm(k_test_output_file);
}