/*
 * HForest: a class to represent a forest of trees.
 */

#pragma once

#include <memory>
#include <list>
#include <vector>
#include "htree.hh"

class HForest {
 public:
  using tree_ptr_t = std::shared_ptr<const HTree>;
  enum class Direction { LEFT, RIGHT };
  using path_t = std::list<Direction>;
  // initialize a forest from a given tree_ptr_t vector, using an empty one if
  // no argument is given.
  explicit HForest(std::vector<tree_ptr_t> = std::vector<HTree::tree_ptr_t>(0));
  ~HForest();
  int size() const;
  void add_tree(tree_ptr_t);
  tree_ptr_t pop_tree();
  // the customer definitely wants a get-able forest_. since the trees don't
  // necessarily link to each other, the customer wants all trees to be
  // get-able. but setting the forest should be done by the previously defined
  // methods.
  tree_ptr_t operator[](int i) {return forest_[i];}
 private:
  std::vector<tree_ptr_t> forest_;
};

bool compare_trees(HForest::tree_ptr_t, HForest::tree_ptr_t);

