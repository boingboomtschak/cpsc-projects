// Devon McKee
// tree.h
// Header file for Tree (BST)
// 2019-05-05

// #includes here

#ifndef TREE_H
#define TREE_H

class Tree
{
 public:
  struct TNode {
    int key;
    TNode* left;
    TNode* right;
  };
  Tree(); // constructor
  Tree(const Tree &cp); // copy constructor
  Tree& operator=(const Tree &cp); // overloaded assignment operator
  ~Tree(); // destructor
  bool insertKey(int key);
  bool findKey(int key);
  int findMinKey();
  int findHeight();
  void preOrder();
  void inOrder(); // iteratively
 private:
  TNode* root;
  TNode* copyTree(TNode* root);
  void deleteTreeR(TNode*& root);
  bool insertKey(TNode*& root, int key);
  bool findKey(TNode* root, int key);
  int findMinKey(TNode* root);
  // PRE: root must not be nullptr, otherwise, int returned is -1
  int findHeight(TNode* root);
  void preOrder(TNode* root);
};

#endif // tree_h
