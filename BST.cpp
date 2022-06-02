#include "BST.h"

using namespace std;

//Constructor
Binary_tree::Binary_tree() {
  root = empty;
  node* empty = new node();
  empty->value = 999999;
  empty->color = BLACK;
  empty->lchild = empty;
  empty->rchild = empty;
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

//Removes a node from the tree
void Binary_tree::remove(int removeValue) {
  node* result = root;
  node* prevResult = root;
  findNode(removeValue, result, prevResult);
  if(!result || result == empty) {
    cout << "Couldn't find " << removeValue << " in tree." << endl;
    return;
  }
  removeNode(result, true);
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

node* Binary_tree::findSucc(node* target) {
  node* succ;
  if(target->rchild != empty) {
    succ = target->rchild;
    while(succ->lchild != empty) { //loop to find leftmost of right subtree (next largest)
      succ = succ->lchild;
    }
    return succ;
  }
  else {
    succ = target->lchild;
    while(succ->rchild != empty) { //loop to find leftmost of right subtree (next smallest)
      succ = succ->rchild;
    }
    return succ;
  }
}

//Finds the sibling of a given node
node* Binary_tree::findSibling(node* target) {
  if(target == root) {
    return root;
  }
  if(target->parent->lchild->value == target->value) {
    return target->parent->rchild;
  }
  else {
    return target->parent->lchild;
  }
}

//Deletes a node from the tree with a given value
void Binary_tree::removeNode(node* & result, bool deleteMode) {
  cout << "Removing/checking cases on: " << result->value << endl;
  empty->color = BLACK;
  node* replace = result;
  if(deleteMode) { //When false, just check for cases.
    if(result->lchild != empty && result->rchild != empty) { //two children
      node* succ = findSucc(result);
      if(devMode) {
	inorder(root);
	cout << endl;
	cout << "Successor of: " << result->value << " is: " << succ->value << endl;
      }
      result->value = succ->value;
      removeNode(succ, true);
      return;
    }
    else { //one or no children
      if(result->lchild != empty) {
	replace = result->lchild;
      }
      else {
	replace = result->rchild;
      }
      replace->color = result->color;
      moveChildUp(result, replace);
    }
  }
  if(replace == root) { //case 1 - terminating
    return;
  }
  node* parent = replace->parent;
  node* sibling = findSibling(replace);
  if(devMode) {
    cout << "parent is: " << parent->value << endl;
    cout << "sibling is: " << sibling->value << endl;
    if(sibling == empty) {
      cout << "Sibling is empty" << endl;
    }
    cout << "Checking cases..." << endl;
  }
  cout << "I DIE" << endl;
  if(sibling->lchild->color == BLACK) {
    cout << " ";
  }
  cout << "BUT I LIVE" << endl;
  if(parent->color == BLACK && sibling->color == RED && sibling->lchild->color == BLACK
     && sibling->rchild->color == BLACK) { //case 2
    cout << "Case 2" << endl;
    if(root == parent) {
      root = sibling;
    }
    else if(islchild(parent, parent->parent)) {
      parent->parent->lchild = sibling;
    }
    else {
      parent->parent->rchild = sibling;
    }
    if(islchild(replace, parent)) { //right rotation
      sibling->parent = parent->parent;
      parent->rchild = sibling->lchild;
      sibling->lchild = parent;
      parent->parent = sibling;
    }
    else { //left rotation
      sibling->parent = parent->parent;
      parent->lchild = sibling->rchild;
      sibling->rchild = parent;
      parent->parent = sibling;
    }
    parent->color == RED;
    sibling->color == BLACK;
    if(devMode) {
      display();
    }
    removeNode(replace, false);
  }
  else if(parent->color == BLACK && sibling->color == BLACK && sibling->lchild->color == BLACK
	  && sibling->rchild->color == BLACK) { //case 3
    cout << "Case 3" << endl;
    sibling->color == RED;
    if(devMode) {
      display();
    }
    removeNode(parent, false);
  }
  else if(parent->color == RED && sibling->color == BLACK && sibling->lchild->color == BLACK
	  && sibling->rchild->color == BLACK) { //case 4 - terminating
    cout << "Case 4" << endl;
    parent->color = BLACK;
    sibling->color = RED;
    return;
  }
  else if(parent->color == BLACK && sibling->color == BLACK && sibling->lchild->color == RED) { //case 5
    cout << "Case 5" << endl;
    node* newSibling;
    if(islchild(replace, parent)) { //right rotation
      newSibling = sibling->lchild;
      newSibling->parent = parent;
      sibling->lchild = newSibling->rchild;
      newSibling->rchild = sibling;
      sibling->parent = newSibling;
      parent->rchild = newSibling;
    }
    else { //left rotation
      newSibling = sibling->rchild;
      newSibling->parent = parent;
      sibling->rchild = newSibling->lchild;
      newSibling->lchild = sibling;
      sibling->parent = newSibling;
      parent->lchild = newSibling;
    }
    sibling->color == RED;
    newSibling->color == BLACK;
    if(devMode) {
      display();
    }
    removeNode(replace, false);
  }
  else if(sibling->color == BLACK && sibling->rchild->color == RED) { //case 6 - terminating
    cout << "Case 6" << endl;
    if(root == parent) {
      root = sibling;
    }
    else if(islchild(parent, parent->parent)) {
      parent->parent->lchild = sibling;
    }
    else {
      parent->parent->rchild = sibling;
    }
    if(islchild(replace, replace->parent)) { //left rotation
      sibling->parent = parent->parent;
      parent->rchild = sibling->lchild;
      sibling->lchild = parent;
      parent->parent = sibling;
      sibling->color = parent->color;
      parent->color = BLACK;
      sibling->rchild->color = BLACK;
    }
    else { //right rotation
      sibling->parent = parent->parent;
      parent->lchild = sibling->rchild;
      sibling->rchild = parent;
      parent->parent = sibling;
      sibling->color = parent->color;
      parent->color = BLACK;
      sibling->lchild->color = BLACK;
    }
  }
}

//Moves a target node's parent to it's position, only use if one child.
void Binary_tree::moveChildUp(node* target, node* child) {
  if(devMode) {
    cout << target->parent->value << " -> " << target->value << " <- " << child->value << endl;
    cout << target->parent->value << " ->  <- " << child->value << endl;
  }
  if(target == root) {
    root = child;
    delete target;
    return;
  }
  child->parent = target->parent;
  if(islchild(target, target->parent)) {
    target->parent->lchild = child;
  }
  else {
    target->parent->rchild = child;
  }
  delete target;
}

//Rotates the tree around a given grandparent
void Binary_tree::rotateGrandparent(node* target) {
  node* grandparent = target->parent->parent;
  node* greatgrandparent = target->parent->parent->parent;
  node* parent = target->parent;
  node* uncle = findUncle(target);
  if(devMode) {
    cout << "╔══════════════════════════╗" << endl;
    cout << "   --GRANDPARENT ROTATE--    " << endl;
    cout << "Target: " << target->value << endl;
    cout << "Parent: " << parent->value << endl;
    cout << "Grandparent: " << grandparent->value << endl;
    cout << "Great-grandparent: " << greatgrandparent->value << endl;
    cout << "Uncle: " << uncle->value << endl;
    display();
  }
  grandparent->color = RED;
  parent->color = BLACK;
  if(root == grandparent) {
    root = parent;
    parent->parent = empty;
  }
  else {
    if(islchild(grandparent, greatgrandparent)) {
      greatgrandparent->lchild = parent;
    }
    else {
      greatgrandparent->rchild = parent;
    }
    parent->parent = grandparent->parent;
  }
  if(islchild(parent, grandparent) && islchild(target, parent)) {
    parent->rchild->parent = grandparent;
    grandparent->lchild = parent->rchild;
    parent->rchild = grandparent;
    grandparent->parent = parent;
  }
  else {
    parent->lchild->parent = grandparent;
    grandparent->rchild = parent->lchild;
    parent->lchild = grandparent;
    grandparent->parent = parent;
  }
  if(root->color == RED) {
    root->color = BLACK;
  }
  if(devMode) {
    cout << "  VVVVVVVVVVVVVVVVVVVV" << endl;
    display();
    cout << "╚══════════════════════════╝" << endl;
  }
}

//Rotates the tree around a given node
void Binary_tree::rotateTree(node* target) {
  node* parent = target->parent;
  node* grandparent = parent->parent;
  if(devMode) {
    cout << "╔══════════════════════════╗" << endl;
    cout << "       --ROTATE TREE--      " << endl;
    cout << "Target: " << target->value << endl;
    cout << "Parent: " << parent->value << endl;
    cout << "Grandparent: " << grandparent->value << endl;
    display();
  }
  if(parent == root) {
    root = target;
  }
  if(islchild(parent, grandparent) && !islchild(target, parent)) { //if Parent is left and node is right
    if(target->lchild != empty) {
      target->lchild->parent = parent;
    }
    parent->rchild = target->lchild;
    target->lchild = parent;
    parent->parent = target;
    target->parent = grandparent;
    grandparent->lchild = target;
    if(devMode) {
      cout << "VVVVVVVVVVVVVVVVVVVVV" << endl;
      display();
      cout << "╚══════════════════════════╝" << endl;
    }
    rotateGrandparent(target->lchild);
  }
  else { //if Parent is right and node is left
    if(target->rchild != empty) {
      target->rchild->parent = parent;
    }
    parent->lchild = target->rchild;
    target->rchild = parent;
    parent->parent = target;
    target->parent = grandparent;
    grandparent->rchild = target;
    if(devMode) {
      cout << "VVVVVVVVVVVVVVVVVVVVV" << endl;
      display();
      cout << "╚══════════════════════════╝" << endl;
    }
    rotateGrandparent(target->rchild);
  }
}

//Recursively checks for cases, case3 recurses
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

//Case3 for remove
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
  if(devMode) {
    cout << "New node: " << newNode->value << " inserted into tree:" << endl;
    display();
  }
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
    cout << root->value << " " << "\033[1;34m" << root->parent->value << "\033[0m" << " , ";
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
