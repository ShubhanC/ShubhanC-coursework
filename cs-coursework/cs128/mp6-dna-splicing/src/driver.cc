#include <iostream>

#include "dna_strand.hpp"
#include "utilities.hpp"

int main() {
  DNAstrand strand = DNAstrand();
  strand.PushBack('a');
  strand.PushBack('a');
  strand.PushBack('a');
  strand.PushBack('a');
  strand.PushBack('a');
  utilities::Print(strand);
  DNAstrand splice = DNAstrand();
  splice.PushBack('t');
  splice.PushBack('g');
  splice.PushBack('t');
  char pattern1[] = "aaa";
  strand.SpliceIn(pattern1, splice);
  utilities::Print(strand);
}