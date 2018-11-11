# cs221hw7
  Worked alone.
  To build project, run make.
  Submitted more files than listed. htree, for instance, from previous
  assignment submission. Necessary for make to build properly.
  Nothing particularly fancy about code design. Asserted that exactly one of
  bitio's arguments was nullptr. When encoder was done, I added end-of-file
  as one last input and then flushed the remaining bits. The decoder breaks
  when it reads end of file, so those final bits at the end won't do anything.
  Printed a bit at a time by setting a char to 0 and adding 2^n to it if the bit
  was true. Might have been faster to encode more bits at a time. For the return
  value of bitio's input_bit, I used a lookup table for bitwise and. For the
  values in the Huffman tree, I multiplied the frequencies by 512. Since there
  are a lot of bits left over in the uint64_t tree values, and then we can add 1
  whenever we merge trees so that in the case of a tie in between trees with the
  same value, the tree with fewer children gets merged first.
Name                    Size (bytes)  Compressed size   Diff Successful?
AdaptiveHuffmanCoding   7,606         4,611             Yes
BBC                     10,539        6,627             Yes
Reed                    2,764         1,850             Yes
Thermodynamics          20,418        12,384            Yes
USA                     10,220        6,468             Yes
