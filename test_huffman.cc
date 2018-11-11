/*
 * test_huffman: test the Huffman class
 */

#include <iostream>
#include <cassert>
#include <climits>
#include "huffman.hh"

//////////////////////////////////////////////////////////////////////////////
// Ensure the encoder actually modifies the coding' length as expected
void test_encode() {
  Huffman huff;

  auto bits = huff.encode('a');
  assert(bits.size() >= CHAR_BIT);  // this has been changed from >.
  bits = huff.encode('b');
  assert(bits.size() >= CHAR_BIT);  // this has been changed from >.

  bits = huff.encode('a');
  assert(bits.size() < CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() < CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() == huff.encode('a').size());

  bits = huff.encode('b');
  bits = huff.encode('b');
  bits = huff.encode('b');
  assert(bits.size() < huff.encode('a').size());
}

//////////////////////////////////////////////////////////////////////////////
// A utility function that takes a collection of bits and a Huffman tree, and
// figures out which symbol these bits encode.
int decode_symbol(Huffman& huff, const Huffman::bits_t& bits) {
  int symbol = -1;

  for (auto b : bits) {
    symbol = huff.decode(b);
  }
  assert(symbol >= 0);
  return symbol;
}

//////////////////////////////////////////////////////////////////////////////
// Ensure decoding returns the same symbol that was encoded, in different
// scenarios.
void test_decode() {
  Huffman encoder, decoder;

  auto bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode('b');
  assert(decode_symbol(decoder, bits) == 'b');
  bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode(Huffman::HEOF);
  assert(decode_symbol(decoder, bits) == Huffman::HEOF);
}

//////////////////////////////////////////////////////////////////////////////
// Test some sentences and ensure rarer characters are not encoded in fewer
// bits than shorter ones.
void test_misc() {
  Huffman encoder, decoder;
  for (auto c : "the quick brown fox jumps over the lazy frog") {
    encoder.encode(c);
  }
  assert(!(encoder.encode('q').size() < encoder.encode('q').size()));
  Huffman encoder2;
  std::string alphabet("abcdefghijklmnopqrstuvwxyz");
  for (int i = 0; i < 26; i++) {
    char c = alphabet[i];
    encoder2.encode(c);
    for (int j = i+1; j < 26; j++) {
      char d = alphabet[j];
      int a = encoder2.encode(c).size();
      int b = encoder2.encode(d).size();
      assert(!(a > b));
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
int main() {
  test_encode();
  test_decode();
  test_misc();
  return 0;
}

