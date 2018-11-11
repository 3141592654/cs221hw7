/*
 * Implementation of huffman.hh.
 */

#include <vector>
#include <climits>
#include "huffman.hh"
#include "hforest.hh"
#include "htree.hh"

// constructor and destructor don't do much
Huffman::Huffman() {
  hf_ = new HForest();
}
Huffman::~Huffman() {
  delete hf_;
}

// create nodes for each symbol in the frequency table
// and turns them into a huffman tree
void Huffman::create_tree() {
  // get new tree
  delete hf_;
  hf_ = new HForest();
  // create node for each symbol
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    // the values normally have values between -256 and 256. uint64_t
    // has a lot more space than that. so multiply by 512. later on,
    // two merged trees will have a value 1 greater than their previous values.
    // since there are 257 trees, this will not change the ordering of values
    // unless the ordering would otherwise be a tie, in which case adding 1
    // guarantees that the node with fewer children is merged first. this makes
    // for a more balanced tree.
    uint64_t nval = freq_table_[i]*512;
    std::shared_ptr<const HTree> ht = std::shared_ptr<const HTree>
                                             (new HTree(i, nval));
    hf_->add_tree(ht);
  }
  // turn the nodes into a huffman tree
  for (int i = -1; hf_->size() > 1; i--) {
    HForest::tree_ptr_t p1 = hf_->pop_tree();
    // hforest re-heaps itself when it pops a tree, so pop again.
    HForest::tree_ptr_t p2 = hf_->pop_tree();
    uint64_t nval = p1->get_value()+p2->get_value()+1;
    HTree::tree_ptr_t p3 = std::shared_ptr<const HTree>
                          (new HTree(i, nval, p1, p2));
    hf_->add_tree(p3);
  }
  cur_tree_ = (*hf_)[0];
}

Huffman::bits_t Huffman::encode(int symbol) {
  // create nodes for each symbol and turn them into a huffman tree
  create_tree();
  // then return the path to the symbol
  HTree::path_t path = (*hf_)[0]->path_to(symbol);
  std::vector<bool> retval(0);
  retval = dir_t_bl(path);
  freq_table_[symbol]++;
  return retval;
}

int Huffman::decode(bool bit) {
  if (cur_tree_ == nullptr) {
    create_tree();
  }
  HTree::Direction d = HTree::Direction(bit);
  if (cur_tree_->get_child(d)->get_key() >= 0) {
    // then it decodes to a value
    int retval = cur_tree_->get_child(d)->get_key();
    freq_table_[retval]++;
    cur_tree_ = nullptr;
    return retval;
  } else {
    cur_tree_ = cur_tree_->get_child(d);
    return -1;
  }
}

std::vector<bool> dir_t_bl(HTree::path_t path) {
  std::vector<bool> retval(0);
  for (HTree::Direction a : path) {
    if (a == HTree::Direction::LEFT) {
      retval.push_back(false);
    } else {
      retval.push_back(true);
    }
  }
  return retval;
}
