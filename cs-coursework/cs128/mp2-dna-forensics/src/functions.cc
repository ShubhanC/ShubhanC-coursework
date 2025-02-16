#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "utilities.hpp"

std::string ProfileDNA(const std::string& dna_database,
                       const std::string& dna_sequence) {
  std::cout << "Input dna_database : " << dna_database << std::endl;
  std::cout << "Input dna_sequence : " << dna_sequence << std::endl;
  std::string name;

  // write your implementation here... we strongly encourage that you leverage
  // additional functions to define this behavior.
  std::ifstream ifs{dna_database};
  unsigned int count = 0;
  int number_of_matches = 0;
  std::vector<std::string> columns;
  std::string name_to_return;
  for (std::string line; std::getline(ifs, line); line = "") {
    std::cout << "line = \"" << line << '\"' << std::endl;
    if (count == 0) {
      columns = utilities::GetSubstrs(line, ',');
    } else {
      std::vector<std::string> personal_dna = utilities::GetSubstrs(line, ',');
      name = MatchName(dna_sequence, columns, personal_dna);
      if (!(name == "No match")) {
        number_of_matches++;
        name_to_return = name;
      }
    }
    count++;
  }
  if (number_of_matches == 1) {
    return name_to_return;
  }
  return "No match";
}

std::string MatchName(const std::string& dna_sequence,
                      const std::vector<std::string>& columns,
                      const std::vector<std::string>& personal_dna) {
  std::string name;
  unsigned int count = 0;
  std::vector<int> dna_string_counts = DNAStringToInt(personal_dna);
  for (unsigned int i = 1; i < columns.size(); i++) {
    unsigned int k_checker = 0;
    unsigned int count_singular = 0;
    std::string dna_consecutive_substring;
    for (int j = 0; j < dna_string_counts[i - 1]; j++) {
      dna_consecutive_substring += columns[i];
    }
    for (unsigned int k = 0; k < dna_sequence.size(); k++) {
      std::string tester =
          dna_sequence.substr(k, dna_consecutive_substring.size());
      if (tester == dna_consecutive_substring) {
        if (k > k_checker + dna_consecutive_substring.size()) {
          k_checker = k;
          count_singular = 0;
        }
        k += columns[i].size() - 1;
        count_singular++;
      }
    }
    if (count_singular == 1) {
      count++;
    }
  }
  if (count == dna_string_counts.size()) {
    return personal_dna[0];
  }
  return "No match";
}

std::vector<int> DNAStringToInt(const std::vector<std::string>& personal_dna) {
  std::vector<int> dna_string_counts;
  for (unsigned int i = 1; i < personal_dna.size(); i++) {
    int count = std::stoi(personal_dna[i]);
    dna_string_counts.push_back(count);
  }
  return dna_string_counts;
}