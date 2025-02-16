#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include <cassert>
#include <stdexcept>

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  Node* GetHead() { return head_; };

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void Splice(unsigned int count, const char* pattern, DNAstrand& to_splice_in);
  void PushBack(char data);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif