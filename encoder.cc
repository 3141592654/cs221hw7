/*
 * takes in an ASCII file or files and outputs the Huffman encoding of that
 * file or files. output will have .comp extension.
 * usage "./decoder afile.txt myfile weirdfile.what"
 */
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include "huffman.hh"
#include "bitio.hh"

int main(int argc, char** argv) {
  assert(argc >= 2);
  for (int i = 1; i < argc; i++) {
    std::string fname(argv[i]);
    std::ifstream s_input(fname);
    assert(s_input.is_open());
    fname = fname + ".comp";
    std::ofstream s_output(fname);
    assert(s_output.is_open());
    Huffman huff_enc;
    BitIO bio(&s_output, nullptr);
    char c;
    // read chars from s_input into huffman encoder.
    for (s_input.get(c); !(s_input.eof()); s_input.get(c)) {
      // get bits from huffman encoder.
      auto bits = huff_enc.encode(c);
      for (auto b : bits) {
        // write these bits to s_output using bitio.
        bio.output_bit(b);
      }
    }
    // program is done, so add end of file character
    auto bits = huff_enc.encode(huff_enc.HEOF);
    for (auto b : bits) {
      bio.output_bit(b);
    }
  }
  return 0;
}
