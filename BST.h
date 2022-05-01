#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>

using namespace std;

struct node {
  bool color;
  int value;
  node* lchild;
  node* rchild;
  node* parent;
};

class Binary_tree {
 public:
  Binary_tree();
  ~Binary_tree();
  void insert(int);
  void remove(int);
  bool search(int);
  void display();
 private:
  const int BLACK = 0;
  const int RED = 1;
  node* root;
  node* empty;
  void rotateGrandparent(node*);
  void rotateTree(node*);
  void recursiveInsert(node*);
  node* findUncle(node*);
  void insertCheck(node*);
  void insertNode(node*&, node*&, node*&);
  void displayTree(bool, node*, const string&);
  node* findPreviousNode(int, node*, node*);
  void findNode(int&, node*&, node*&);
  bool islchild(node*, node*);
  void inorder(node*&);
  void destroy(node*&);
};


#endif
