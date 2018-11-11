/*
 * takes a previously encoded .comp file or files and outputs .plaintexts.
 * usage "./encoder myfile.comp secondfile.comp favoritefile.comp"
 */
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include "huffman.hh"
#include "bitio.hh"

int main(int argc, char** argv) {
  assert(argc >= 2);
  // cycle through every argument
  for (int i = 1; i < argc; i++) {
    std::string fname(argv[i]);
    std::ifstream input(fname);
    assert(input.is_open());
    fname = fname + ".plaintext";
    std::ofstream output(fname);
    assert(output.is_open());
    Huffman huffdec;
    BitIO bio(nullptr, &input);
    for (; !(input.eof());) {
      // read in bits from input using bitio.
      auto b = bio.input_bit();
      // feed bits to huffman decoder.
      int c = huffdec.decode(b);
      if (c == huffdec.HEOF) {
        break;
      }
      if (c >= 0) {
        // when huffman decoder returns a positive number,
        output << static_cast<char>(c);
      }
    }
  }
  return 0;
}
