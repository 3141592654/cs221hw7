CXX=g++
CXXFLAGS=-g -Wall -Wextra -pedantic -std=c++17
OPTFLAGS=-O3
LDFLAGS=$(OPTFLAGS) $(CXXFLAGS)
SOURCEFILES = htree.cc hforest.cc huffman.cc
HEADERFILES = htree.hh hforest.hh huffman.hh
OBJECTFILES = htree.o  hforest.o  huffman.o

all: test_huffman test_bitio encoder decoder

test_huffman: test_huffman.cc $(SOURCEFILES) $(HEADERFILES) $(OBJECTFILES)
	$(CXX) $(LDFLAGS) -o test_huffman $(OBJECTFILES) test_huffman.cc

htree.o: htree.cc htree.hh
	$(CXX) $(LDFLAGS) -c -o htree.o htree.cc

hforest.o: hforest.cc hforest.hh
	$(CXX) $(LDFLAGS) -c -o hforest.o hforest.cc

huffman.o: huffman.cc huffman.hh
	$(CXX) $(LDFLAGS) -c -o huffman.o huffman.cc

test_bitio: test_bitio.cc bitio.o
	$(CXX) $(LDFLAGS) -o test_bitio bitio.o test_bitio.cc

bitio.o: bitio.cc bitio.hh
	$(CXX) $(LDFLAGS) -c -o bitio.o bitio.cc

encoder: encoder.cc huffman.o bitio.o
	$(CXX) $(LDFLAGS) -o encoder $(OBJECTFILES) bitio.o encoder.cc

decoder: decoder.cc huffman.o bitio.o
	$(CXX) $(LDFLAGS) -o decoder $(OBJECTFILES) bitio.o decoder.cc

clean:
	rm -rf *.o *.comp *.plaintext test_huffman test_bitio encoder decoder
