/*
  Stefan Smith
  4/21/2022
  Binary Search Tree

  Commands:
  - remove - Remove a value from the tree.
  - add - Add a value to the tree.
  - display - Display the tree to console.
  - search - Determine if a value is in the tree.
  - quit - End the program.

  Code Used:
  - printBT by Adrian Schneider - https://stackoverflow.com/users/2631225/adrian-schneider
 */

#include <iostream>
#include "BST.h"
#include "time.h"
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

void stringToTree(Binary_tree* bst, char* input);
void stringFromFile(char* input, char* inputFileName, bool &success);
int spaces(char* input);

int main() {
  Binary_tree* bst = new Binary_tree();
  bool validCmd = false;
  char input[10];
  while(!validCmd) {
    cout << "Fill tree manually, randomly, or by file? (m/r/f): ";
    cin >> input;
    cin.clear();
    cin.ignore();
    if(!strcmp(input, "quit")) {
      return 0;
    }
    if(!strcmp(input, "m")) {
      char manual[350] = {0};
      char* manualInput = manual;
      cout << "Enter numbers separated by spaces, hit enter to finish." << endl;
      cin.getline(manualInput, 350);
      stringToTree(bst, manualInput);
      validCmd = true;
    }
    else if(!strcmp(input, "r")) {
      srand(time(NULL));
      for(int i = 0; i < 10; i++) {
	bst->insert((rand() % 999) + 1);
      }
      validCmd = true;
    }
    else if(!strcmp(input, "f")) {
      char fileInput[350];
      char fileName[30];
      cout << "File name: ";
      cin.getline(fileName, 30);
      stringFromFile(fileInput, fileName, validCmd);
      if(validCmd) {
	stringToTree(bst, fileInput);
      }
    }
    else {
      cout << "Command not recognized." << endl;
    }
  }
  bool running = true;
  int intInput = 0;
  bst->display();
  while(running) {
    cout << "Command: ";
    cin.getline(input, 10);
    if(!strcmp(input, "remove")) {
      cout << "Remove: ";
      cin >> intInput;
      bst->remove(intInput);
      cin.ignore();
      cin.clear();
    }
    else if(!strcmp(input, "add")) {
      cout << "Add: ";
      cin >> intInput;
      bst->insert(intInput);
      cin.ignore();
      cin.clear();
    }
    else if(!strcmp(input, "search")) {
      cout << "Search for: ";
      cin >> intInput;
      if(bst->search(intInput)) {
	cout << intInput << " is in tree." << endl;
      }
      else {
	cout << intInput << " is not in tree." << endl;
      }
      cin.ignore();
      cin.clear();
    }
    else if(!strcmp(input, "display")) {
      bst->display();
    }
    else if(!strcmp(input, "quit")) {
      running = false;
    }
  }
  delete bst;
  return 0;
}

//Fills a char array from the first line of a file
void stringFromFile(char* input, char* inputFileName, bool &success) {
  fstream file;
  string output;
  int length = 0;
  file.open(inputFileName, ios::in);
  if(file.is_open()) {
    getline(file, output);
    file.close();
    strcpy(input, output.c_str());
    success = true;
  }
  else {
    cout << "Couldn't open file." << endl;
  }
}

//Counts the spaces in a string
int spaces(char* input) {
  int output = 0;
  int it = 0;
  while(input[it] != '\0') {
    if(input[it] == ' ') {
      output++;
    }
    it++;
  }
  return output;
}

//Extracts ints from a string, adds them to the tree
void stringToTree(Binary_tree* bst, char* input) {
  int intFromInput = 0;
  int intspaces = spaces(input);
  for(int i = 1; i < intspaces + 2; i++) {
    sscanf(input, "%d", &intFromInput);
    bst->insert(intFromInput);
    if(intFromInput < 10) {
      input += 2;
    }
    else if(intFromInput < 100) {
      input += 3;
    }
    else if(intFromInput < 1000) {
      input += 4;
    }
    else {
      input += 5;
    }
  }
}
