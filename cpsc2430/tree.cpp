// Devon McKee
// tree.cpp
// Implementation of Tree as described in tree.h

#include "tree.h"
#include <stack>
#include <iostream>

using namespace std;

Tree::Tree()
{
  root = nullptr;
}

Tree::Tree(const Tree &cp)
{
  root = copyTree(cp.root);
}

Tree& Tree::operator=(const Tree &cp)
{
  if(this != &cp){
    root = copyTree(cp.root);
  }
  return *this;
}

Tree::~Tree()
{
  deleteTreeR(root);
}

bool Tree::insertKey(int key)
{
  return insertKey(root, key);
}

bool Tree::findKey(int key)
{
  return findKey(root, key);
}

int Tree::findMinKey()
{
  return findMinKey(root);
}

int Tree::findHeight()
{
  return findHeight(root);
}

void Tree::preOrder()
{
  cout << "Preorder Traversal: ";
  if(root != nullptr){
    preOrder(root);
  }else{
    cout << "Tree is null!";
  }
  cout << "\n";
}

void Tree::inOrder()
{
  if(root != nullptr){
    // doing iteratively
    stack<TNode*> s;
    TNode* current = root;
    cout << "Inorder Traversal: ";
    while(current != nullptr || !s.empty()){
      while(current != nullptr){
        s.push(current);
        current = current->left;
      }
      current = s.top();
      s.pop();
      cout << current->key << " ";
      current = current->right;
    }
    cout << "\n";
  }else{
    cout << "Inorder Traversal: Tree null!\n";
  }
}

Tree::TNode* Tree::copyTree(Tree::TNode* root)
{
  Tree::TNode* temp = nullptr;
  if(root != nullptr){
    temp = new Tree::TNode;
    temp->key = root->key;
    temp->left = copyTree(root->left);
    temp->right = copyTree(root->right);
  }
  return temp;
}

void Tree::deleteTreeR(Tree::TNode*& root)
{
  if(root->left == nullptr && root->right == nullptr){
    delete root;
    root = nullptr;
  }else{
    if(root->left != nullptr){
      deleteTreeR(root->left);
    }
    if(root->right != nullptr){
      deleteTreeR(root->right);
    }
    delete root;
    root = nullptr;
  }
}

bool Tree::insertKey(Tree::TNode*& root, int key)
{
  if(root == nullptr){
    root = new Tree::TNode;
    root->key = key;
    root->left = nullptr;
    root->right = nullptr;
    return true;
  }else{
    if(key < root->key){
      return insertKey(root->left, key);
    }else if(key > root->key){
      return insertKey(root->right, key);
    }else{
      return false;
    }
  }
}

bool Tree::findKey(Tree::TNode* root, int key)
{
  if(root == nullptr){
    return false;
  }else{
    if(root->key == key){
      return true;
    }else if(key < root->key){
      return findKey(root->left, key);
    }else{
      return findKey(root->right, key);
    }
  }
}

int Tree::findMinKey(Tree::TNode* root)
{
  if(root != nullptr){
    if(root->left != nullptr){
      return findMinKey(root->left);
    }else{
      return root->key;
    }
  }else{
    return -1;
  }
}

int Tree::findHeight(Tree::TNode* root)
{
  if(root == nullptr){
    return 0;
  }else{
    int left = 0;
    int right = 0;
    if(root->left != nullptr){
      left = findHeight(root->left);
    }
    if(root->right != nullptr){
      right = findHeight(root->right);
    }
    if(left > right){
      return left + 1;
    }else{
      return right + 1;
    }
  }
}

void Tree::preOrder(Tree::TNode* root)
{
  cout << root->key << " ";
  if(root->left != nullptr){
    preOrder(root->left);
  }
  if(root->right != nullptr){
    preOrder(root->right);
  }
}

