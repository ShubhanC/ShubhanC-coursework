#include "utilities.hpp"

#include <iostream>

void utilities::Print(DNAstrand& d) {
  Node* iter = d.GetHead();
  while (iter->next != nullptr) {
    std::cout << iter->data << ' ';
    iter = iter->next;
  }
  std::cout << iter->data << std::endl;
}