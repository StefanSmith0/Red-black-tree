#include "BST.h"

using namespace std;

//Constructor
Binary_tree::Binary_tree() {
  root = empty;
 node* empty = new node();
 empty->color = BLACK;
}

//Destructor
Binary_tree::~Binary_tree() {
  destroy(root);
}

//Deletes every node in the tree
void Binary_tree::destroy(node* & root) {
  if(root != empty) {
    destroy(root->lchild);
    destroy(root->rchild);
    delete root;
    root = empty;
  }
}

//Adds a value to tree
void Binary_tree::insert(int newInt) {
  node* newNode = new node();
  newNode->value = newInt;
  newNode->lchild = empty;
  newNode->rchild = empty;
  newNode->parent = empty;
  newNode->color = RED;
  insertNode(root, root, newNode);
}

//Searches for a value in tree
bool Binary_tree::search(int searchValue) {
  node* result = root;
  node* prevResult = root;
  findNode(searchValue, result, prevResult);
  if(result != empty) {
    return true;
  }
  else {
    return false;
  }
}

//Finds the parent of a node with a given value
node* Binary_tree::findPreviousNode(int searchValue, node* result, node* prevResult) {
  if(result != empty) {
    if(result->value == searchValue) {
      return prevResult;
    }
    else if(result->value > searchValue) {
      return findPreviousNode(searchValue, result->lchild, result);
    }
    else {
      return findPreviousNode(searchValue, result->rchild, result);
    }
  }
  else {
    return empty;
  }
}

//Uses findPreviousNode to find a node with a given value
void Binary_tree::findNode(int & searchValue, node* & result, node* & prevResult) {
  prevResult = findPreviousNode(searchValue, result, prevResult);
  if(prevResult != empty) {
    if(prevResult->lchild != empty && prevResult->lchild->value == searchValue) {
      result = prevResult->lchild;
    }
    else if(prevResult->rchild != empty && prevResult->rchild->value == searchValue) {
      result = prevResult->rchild;
    }
    else {
      result = root;
    }
  }
  else {
    result = empty;
  }
}

//Checks if a node is an lchild of another node
bool Binary_tree::islchild(node* child, node* parent) {
  if(parent->lchild->value == child->value) {
    return true;
  }
  return false;
}

//Deletes a node from the tree with a given value
void Binary_tree::remove(int deleteValue) {
  node* result = root;
  node* prevResult = root;
  findNode(deleteValue, result, prevResult);
  if(!result) {
    cout << "Couldn't find " << deleteValue << " in tree." << endl;
    return;
  }
  bool lchild = islchild(result, prevResult);
  if(result->lchild == empty && result->rchild == empty) { //leaf
    if(lchild) {
      prevResult->lchild = empty;
      delete result;
    }
  }
  else if(result->lchild != empty && result->rchild != empty) { //two children
    node* replacementParent = result;
    node* replacement = replacementParent->rchild;
    while(replacement->lchild != empty) { //loop to find leftmost of right subtree
      replacementParent = replacement;
      replacement = replacementParent->lchild;
    }
    if(replacement->rchild) { //if replacement has rchild, adopt it
      if(replacementParent == result) {
	replacementParent->rchild = replacement->rchild;
      }
      else {
	replacementParent->lchild = replacement->rchild;
      }
    }
    else {
      if(replacementParent == result) {
	replacementParent->rchild = empty;
      }
      else {
	replacementParent->lchild = empty;
      }
    }
    int replacementValue = replacement->value;
    delete replacement;
    result->value = replacementValue;
  }
  else if(result->lchild != empty || result->rchild != empty) { //one child
    node* child;
    if(result->lchild != empty) {
      child = result->lchild;
    }
    else {
      child = result->rchild;
    }
    if(lchild) {
      prevResult->lchild = child;
    }
    else {
      prevResult->rchild = child;
    }
    delete result;
  }
}

//Rotates the tree around a given grandparent
void Binary_tree::rotateGrandparent(node* target) {
  node* grandparent = target->parent->parent;
  node* greatgrandparent = grandparent->parent;
  node* parent = target->parent;
  node* uncle = findUncle(target);
  grandparent->color = RED;
  parent->color = BLACK;
  if(root == grandparent) {
    root = parent;
    parent->parent = empty;
  }
  else {
    if(islchild(grandparent, grandparent->parent)) {
      grandparent->parent->lchild = parent;
    }
    else {
      grandparent->parent->rchild = parent;
    }
    parent->parent = grandparent->parent;
  }
  if(islchild(parent, grandparent) && islchild(target, parent)) {
    grandparent->lchild = parent->rchild;
    parent->rchild = grandparent;
    grandparent->parent = parent;
  }
  else {
    grandparent->rchild = parent->lchild;
    parent->lchild = grandparent;
    grandparent->parent = parent;
  }
  if(root->color == RED) {
    root->color = BLACK;
  }
}

//Rotates the tree around a given node
void Binary_tree::rotateTree(node* target) {
  node* parent = target->parent;
  node* grandparent = parent->parent;
  if(parent == root) {
    root = target;
  }
  if(islchild(parent, grandparent) && !islchild(target, parent)) { //if Parent is left and node is right
    parent->rchild = target->lchild;
    target->lchild = parent;
    parent->parent = target;
    target->parent = grandparent;
    grandparent->lchild = target;
    rotateGrandparent(parent);
  }
  else if(!islchild(parent, grandparent) && islchild(target, parent)) { //if Parent is right and node is left
    parent->lchild = target->rchild;
    target->rchild = parent;
    parent->parent = target;
    target->parent = grandparent;
    grandparent->rchild = target;
    rotateGrandparent(parent);
  }  
}

//Recursively swaps nodes
void Binary_tree::recursiveInsert(node* newNode) {
  node* parent = newNode->parent;
  if(parent == empty || parent->color == BLACK) {
    return;
  }
  node* grandparent = parent->parent;
  if(grandparent == empty) {
    parent->color = BLACK;
    return;
  }
  node* uncle = findUncle(newNode);
  if(uncle == empty || uncle->color == BLACK) {
    if(islchild(newNode, newNode->parent) && islchild(newNode->parent, newNode->parent->parent)) {
      rotateGrandparent(newNode);
    }
    else if(!islchild(newNode, newNode->parent) && !islchild(newNode->parent, newNode->parent->parent)) { //Case 5
      rotateGrandparent(newNode);
    }
    else {
      rotateTree(newNode);
    }
  }
  else { //Case 3
    grandparent->lchild->color = BLACK;
    grandparent->rchild->color = BLACK;
    grandparent->color = RED;
    if(root->color == RED) {
      root->color = BLACK;
    }
    recursiveInsert(grandparent);
  }
}

void Binary_tree::case3(node* target, node* uncle) {
  if(target->parent == empty) {
    return;
  }
  target->parent->color = BLACK;
  uncle->color = BLACK;
  target->parent->parent->color = RED;
  case3(target->parent->parent, findUncle(target->parent->parent));
}

//Finds the uncle of a given node
node* Binary_tree::findUncle(node* target) {
  node* uncle = nullptr;
  node* grandparent = target->parent->parent;
  if(grandparent->lchild->value == target->parent->value) {
    uncle = grandparent->rchild;
  }
  else {
    uncle = grandparent->lchild;
  }
  return uncle;
}

//Resorts the tree after inserting a node
void Binary_tree::insertCheck(node* newNode) {
  if(newNode == root) {
    newNode->parent = empty;
  }
  else {
    recursiveInsert(newNode);
  }
}

//Puts a new node into the tree at the right place
void Binary_tree::insertNode(node* & root, node* & rootParent, node* & newNode) {
  if(root == empty) {
    root = newNode;
    newNode->parent = rootParent;
    insertCheck(root);
  }
  else if(root->value > newNode->value) {
    insertNode(root->lchild, root, newNode);
  }
  else {
    insertNode(root->rchild, root, newNode);
  }
}

//Runs displayTree
void Binary_tree::display() {
  string prefix = "";
  displayTree(false, root, prefix);
  cout << endl;
}

//Prints the tree in order
void Binary_tree::inorder(node* & root) {
  if(root != empty) {
    inorder(root->lchild);
    cout << root->value << ", ";
    inorder(root->rchild);
  }
}

//Prints the tree as a horizontal tree - printBT by Adrian Schneider (modified)
void Binary_tree::displayTree(bool isLeft, node* root, const string &prefix) {
  if(prefix.length() > 100) {
    return;
  }
  if(root != empty) {
    cout << prefix;

    cout << (isLeft ? "├──" : "└──" );
    if(root->color == RED) {
      cout << "\033[1;31m" << root->value << "\033[0m" << endl;
    }
    else {
      cout << root->value << endl;
    }
    displayTree(true, root->lchild, prefix + (isLeft ? "|   " : "    " ));
    displayTree(false, root->rchild, prefix + (isLeft ? "|   " : "    " ));
  }
}
