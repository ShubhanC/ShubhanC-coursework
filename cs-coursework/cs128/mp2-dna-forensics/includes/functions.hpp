#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

#include "utilities.hpp"

std::string ProfileDNA(const std::string& dna_database,
                       const std::string& dna_sequence);

std::string MatchName(const std::string& dna_sequence,
                      const std::vector<std::string>& columns,
                      const std::vector<std::string>& personal_dna);

std::vector<int> DNAStringToInt(const std::vector<std::string>& personal_dna);

#endif