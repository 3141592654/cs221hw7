/*
 * A simple class to perform stream I/O on individual bits.
 * Before reading any bits, ensure your input stream still has valid inputs.
 */
#pragma once

#include <iostream>

class BitIO {
 public:
  // Construct with one of either an input stream or output (the other null)
  BitIO(std::ostream* os, std::istream* is);

  // Flushes out any remaining output bits and trailing zeros, if any:
  ~BitIO();

  BitIO(const BitIO&) = default;
  BitIO(BitIO&&) = default;
  BitIO& operator=(const BitIO&) = default;
  BitIO& operator=(BitIO&&) = default;

  // Output a single bit (buffered)
  void output_bit(bool bit);

  // Read a single bit (or trailing zero)
  bool input_bit();

 private:
  std::ostream* os_;
  std::istream* is_;
  int num_bits_input_;
  char buf_ = 0;
  // lookup table for bitwise and.
  const unsigned char lookup_[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
                                                                       0x80};
};
