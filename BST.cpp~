#include "BST.h"

using namespace std;

//Constructor
Binary_tree::Binary_tree() {
  root = NULL;
}

//Destructor
Binary_tree::~Binary_tree() {
  destroy(root);
}

//Deletes every node in the tree
void Binary_tree::destroy(node* & root) {
  if(root) {
    destroy(root->lchild);
    destroy(root->rchild);
    delete root;
    root = nullptr;
  }
}

//Adds a value to tree
void Binary_tree::insert(int newInt) {
  node* newNode = new node();
  newNode->value = newInt;
  newNode->lchild = nullptr;
  newNode->rchild = nullptr;
  insertNode(root, newNode);
}

//Searches for a value in tree
bool Binary_tree::search(int searchValue) {
  node* result = root;
  node* prevResult = root;
  findNode(searchValue, result, prevResult);
  if(result) {
    return true;
  }
  else {
    return false;
  }
}

//Finds the parent of a node with a given value
node* Binary_tree::findPreviousNode(int searchValue, node* result, node* prevResult) {
  if(result) {
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
    return nullptr;
  }
}

//Uses findPreviousNode to find a node with a given value
void Binary_tree::findNode(int & searchValue, node* & result, node* & prevResult) {
  prevResult = findPreviousNode(searchValue, result, prevResult);
  if(prevResult) {
    if(prevResult->lchild && prevResult->lchild->value == searchValue) {
      result = prevResult->lchild;
    }
    else if(prevResult->rchild && prevResult->rchild->value == searchValue) {
      result = prevResult->rchild;
    }
    else {
      result = root;
    }
  }
  else {
    result = nullptr;
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
  if(!result->lchild && !result->rchild) { //leaf
    if(lchild) {
      prevResult->lchild = nullptr;
      delete result;
    }
  }
  else if(result->lchild && result->rchild) { //two children
    node* replacementParent = result;
    node* replacement = replacementParent->rchild;
    while(replacement->lchild) { //loop to find leftmost of right subtree
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
	replacementParent->rchild = nullptr;
      }
      else {
	replacementParent->lchild = nullptr;
      }
    }
    int replacementValue = replacement->value;
    delete replacement;
    result->value = replacementValue;
  }
  else if(result->lchild || result->rchild) { //one child
    node* child;
    if(result->lchild) {
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

//Puts a new node into the tree at the right place
void Binary_tree::insertNode(node* & root, node* & newNode) {
  if(!root) {
    root = newNode;
  }
  else if(root->value > newNode->value) {
    insertNode(root->lchild, newNode);
  }
  else {
    insertNode(root->rchild, newNode);
  }
}

//Runs displayTree
void Binary_tree::display() {
  string prefix = "";
  displayTree(false, root, prefix);
  cout << endl;
  cout << "Inorder: ";
  inorder(root);
  cout << endl;
}

//Prints the tree in order
void Binary_tree::inorder(node* & root) {
  if(root) {
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
  if(root) {
    cout << prefix;

    cout << (isLeft ? "├──" : "└──" );

    cout << root->value << endl;
    displayTree(true, root->lchild, prefix + (isLeft ? "|   " : "    " ));
    displayTree(false, root->rchild, prefix + (isLeft ? "|   " : "    " ));
  }
}
