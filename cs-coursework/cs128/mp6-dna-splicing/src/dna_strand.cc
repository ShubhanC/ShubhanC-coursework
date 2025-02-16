#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
  Node* curr = head_;
  while (curr != nullptr) {
    Node* tmp = curr->next;
    delete curr;
    curr = tmp;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern == nullptr || to_splice_in.head_ == nullptr) return;
  if (&to_splice_in == this) return;
  unsigned int pattern_len = 0;
  for (unsigned int i = 0; pattern[i] != '\0'; i++) {
    pattern_len++;
  }
  bool check = false;
  Node* iter = head_;
  unsigned int count = 0;
  unsigned int count_to_send = 0;
  while (iter != nullptr) {
    Node* tmp = iter;
    count++;
    for (unsigned int i = 0; i < pattern_len && tmp != nullptr; i++) {
      if (tmp->data != pattern[i]) {
        break;
      }
      if ((tmp->data == pattern[i]) && (pattern[i + 1] == '\0')) {
        count_to_send = count;
        check = true;
        for (unsigned int j = 0; j < pattern_len - 1; j++) {
          iter = iter->next;
          count++;
        }
      }
      tmp = tmp->next;
    }
    iter = iter->next;
  }
  if (check) {
    Splice(count_to_send, pattern, to_splice_in);
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
  } else {
    throw std::invalid_argument("pattern not found");
  }
}

void DNAstrand::Splice(unsigned int count,
                       const char* pattern,
                       DNAstrand& to_splice_in) {
  Node* iter = head_;
  Node* tmp = head_;
  if (count <= 1) {
    iter = to_splice_in.head_;
    head_ = iter;
  } else {
    for (unsigned int i = 0; i < count - 2 && iter->next != nullptr; i++) {
      tmp = tmp->next;
      iter = iter->next;
      if (i == count - 3) {
        tmp = tmp->next;
        iter->next = to_splice_in.head_;
      }
    }
  }
  iter = iter->next;
  for (unsigned int i = 0; pattern[i] != '\0' && tmp != nullptr; i++) {
    Node* tmp2 = tmp->next;
    delete tmp;
    tmp = tmp2;
  }
  while (iter->next != nullptr && iter != to_splice_in.tail_) {
    iter = iter->next;
  }
  iter->next = tmp;
  while (iter != nullptr && iter->next != nullptr) {
    iter = iter->next;
  }
  tail_ = iter;
}

void DNAstrand::PushBack(char data) {
  Node* tmp = new Node(data);
  if (head_ == nullptr) {
    head_ = tail_ = tmp;
  } else {
    tail_->next = tmp;
    tail_ = tail_->next;
  }
}