// clang-format off
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2023/06/02                      Compiler ...: clang++                  //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// clang-format on

///////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
///////////////////////////////////////////////////////////////////////////////
#ifdef CATCH_CONFIG_MAIN
#  undef CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include "dna_strand.hpp"
#include "utilities.hpp"

///////////////////////////////////////////////////////////////////////////////
//                                 Includes //
///////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
///////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("Example 1 Prompt", "") {
  DNAstrand strand = DNAstrand();
  strand.PushBack('c');
  strand.PushBack('t');
  strand.PushBack('g');
  strand.PushBack('a');
  strand.PushBack('a');
  strand.PushBack('t');
  strand.PushBack('t');
  strand.PushBack('c');
  strand.PushBack('g');
  utilities::Print(strand);
  DNAstrand splice = DNAstrand();
  splice.PushBack('t');
  splice.PushBack('g');
  splice.PushBack('a');
  splice.PushBack('t');
  splice.PushBack('c');
  char pattern1[] = "gaattc";
  strand.SpliceIn(pattern1, splice);
  utilities::Print(strand);
  Node* iter = strand.GetHead();
  std::string check;
  while (iter != nullptr) {
    check += iter->data;
    iter = iter->next;
  }
  REQUIRE(check == "cttgatcg");
  REQUIRE(true == true);
}

TEST_CASE("Example 2 Prompt", "") {
  DNAstrand strand = DNAstrand();
  strand.PushBack('c');
  strand.PushBack('t');
  strand.PushBack('a');
  strand.PushBack('t');
  strand.PushBack('a');
  utilities::Print(strand);
  DNAstrand splice = DNAstrand();
  splice.PushBack('t');
  splice.PushBack('g');
  splice.PushBack('a');
  char pattern1[] = "ta";
  strand.SpliceIn(pattern1, splice);
  utilities::Print(strand);
  Node* iter = strand.GetHead();
  std::string check;
  while (iter != nullptr) {
    check += iter->data;
    iter = iter->next;
  }
  REQUIRE(check == "ctatga");
  REQUIRE(true == true);
}

TEST_CASE("AAAAA", "") {
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
  Node* iter = strand.GetHead();
  std::string check;
  while (iter != nullptr) {
    check += iter->data;
    iter = iter->next;
  }
  REQUIRE(check == "tgtaa");
  REQUIRE(true == true);
}
///////////////////////////////////////////////////////////////////////////////