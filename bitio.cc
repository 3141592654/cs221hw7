/*
 * Implementation of bitio.hh.
 */
#include <assert.h>
#include <iostream>
#include "bitio.hh"

BitIO::BitIO(std::ostream* os, std::istream* is) {
  if (os == nullptr) {
    os_ = nullptr;
    assert(is != nullptr);
    is_ = is;
  } else {
    is_ = nullptr;
    assert(is == nullptr);
    os_ = os;
  }
  num_bits_input_ = 0;
}

BitIO::~BitIO() {
  if (os_ != nullptr) {
    // flush all bits in the buffer plus some trailing zeros.
    if (num_bits_input_ != 0) {
      *os_ << buf_;
    }
    os_->flush();
  }
}

void BitIO::output_bit(bool bit) {
  assert(os_ != nullptr);
  // modify a single bit of buf_, which is a char that is initialised to 0
  buf_ += bit << num_bits_input_;
  num_bits_input_++;
  if (num_bits_input_ >= 8) {
    *os_ << buf_;
    os_->flush();
    num_bits_input_ = 0;
    buf_ = 0;
  }
}

bool BitIO::input_bit() {
  assert(is_ != nullptr);
  if (num_bits_input_ == 0) {
    is_->read(&buf_, 1);
    num_bits_input_ = 8;
  }
  num_bits_input_--;
  return buf_ & lookup_[7-num_bits_input_];
}
