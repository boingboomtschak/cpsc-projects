// Devon McKee
// 2019-05-01
// Lab #3 (lab3.cpp)
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct TNode {
  int key;
  TNode* left;
  TNode* right;
};

const int RAND_INT_MIN = 0;
const int RAND_INT_MAX = 20;
const int NUM_NODES = 10;

bool insertTree(TNode*& root, int key);
// inserts TNode with specified key value in spot in tree determined by BST
// will not insert duplicates

void printInorder(TNode* root);
// prints values in tree with inorder traversal

void printPreorder(TNode* root);
// prints values in tree with preorder traversal

void printPostorder(TNode* root);
// prints values in tree with postorder traversal

void deleteAll(TNode*& root);
// deletes all values in tree, recursively, sets root pointer to nullptr



int main()
{
  TNode* root = nullptr;
  int randInt;
  bool dupe;
  srand(time(0));
  cout << "\033c";
  cout << "Welcome to lab 3!\n";
  cout << "By Devon McKee\n\n";
  cout << "Creating tree with " << NUM_NODES << " nodes..\n";
  for(int i=0; i<NUM_NODES; i++){
    randInt = (rand() % (RAND_INT_MAX - RAND_INT_MIN + 1)) + RAND_INT_MIN;
    dupe = insertTree(root, randInt);
    if(!dupe){
      cout << "Insertion failed! Duplicate number..\n";
    }
  }
  cout << "Tree created.\n";
  cout << "Inorder Traversal: ";
  printInorder(root);
  cout << "\n";
  cout << "Preorder Traversal: ";
  printPreorder(root);
  cout << "\n";
  cout << "Postorder Traversal: ";
  printPostorder(root);
  cout << "\n";
  cout << "\n";
  cout << "Cleaning up tree memory..\n";
  deleteAll(root);
  cout << "Thanks for using my program!\n";
  cout << "Have a nice day!\n";
  cout << "\n\n";
  return 0;
}

bool insertTree(TNode*& root, int key)
{
  if(root == nullptr){
    root = new TNode;
    root->key = key;
    root->left = nullptr;
    root->right = nullptr;
    return true;
  }else{
    if(key < root->key){
      return insertTree(root->left, key);
    }else if(key > root->key){
      return insertTree(root->right, key);
    }else{
      return false;
    }
  }
}

void printInorder(TNode* root)
{
  if(root->left != nullptr){
    printInorder(root->left);
  }
  cout << root->key << " ";
  if(root->right != nullptr){
    printInorder(root->right);
  }
}

void printPreorder(TNode* root)
{
  cout << root->key << " ";
  if(root->left != nullptr){
    printPreorder(root->left);
  }
  if(root->right != nullptr){
    printPreorder(root->right);
  }
}

void printPostorder(TNode* root)
{
  if(root->left != nullptr){
    printPostorder(root->left);
  }
  if(root->right != nullptr){
    printPostorder(root->right);
  }
  cout << root->key << " ";
}

void deleteAll(TNode*& root)
{
  if(root->left == nullptr && root->right == nullptr){
    delete root;
    root = nullptr;
  }else{
    if(root->left != nullptr){
      deleteAll(root->left);
    }
    if(root->right != nullptr){
      deleteAll(root->right);
    }
    delete root;
    root = nullptr;
  }
}

