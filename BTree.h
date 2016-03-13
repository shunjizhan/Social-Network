#include <stddef.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class BTreeNode {
 public:
  BTreeNode(bool isLeaf, BTreeNode* parent) {
    this->keys = new Node*[5];
    this->children = new BTreeNode*[6];
    for(int i=0; i<5; i++) {
      keys[i]= new Node("zzzzzzzzzzzzz");
    }
    this->parent = parent;
    for(int i=0; i<6; i++) {
      children[i] = NULL;
    }
    this->currentKeyNumber = 0;
    this->isLeaf = isLeaf;
    left = NULL;
    right = NULL;
  }
  
  Node** keys;  
  BTreeNode** children;
  BTreeNode* parent;
  BTreeNode* left;
  BTreeNode* right;
  int currentKeyNumber;
  bool isLeaf;
  
};

class BTree {
 public:
  BTree() {
    root = NULL;
  }

  void insert(Node* k) {
    cout << "-------------------------inserting " << k->getName() << "----------------------------" << endl;
    if(root == NULL) {
      root = new BTreeNode(true,NULL);
      root->keys[0] = k;
      root->currentKeyNumber = 1;
    }

    else {
      BTreeNode* leafToInsert = find(k->getName());
      // cout << "found leaf" << endl;
      insert(k,leafToInsert);
    }

    cout << "print tree........" << endl;
    printTree();
    cout << "-------------------------insert[" << k->getName() << "]complete!---------------------------" << endl; 
    cout << endl<< endl;
  }

  void insert(Node* k, BTreeNode* leaf) {
    int i=2;

    while((i >= 0) && bigger(leaf->keys[i]->getName(), k->getName())) {
      cout << "i=" << i;
      leaf->keys[i+1] = leaf->keys[i];
      i--;
      //printKeyList(leaf);
    }
    
    leaf->keys[i+1] = k;
    leaf->currentKeyNumber++;

    if(leaf->currentKeyNumber == 4) {
      split(leaf);
    }
	
  }

  void split(BTreeNode* node) {
    cout << "!!!!!!!!!!!!!! split !!!!!!!!!!!!!!!!!!!" << endl;
    BTreeNode* parent = node->parent;
    cout << "parent's keyList=";
    printKeyList(parent);
    cout << endl;
    
    if(parent == NULL) {  // this is the root
      BTreeNode* newRoot = new BTreeNode(false,NULL);
      BTreeNode* left = new BTreeNode(true,newRoot);
      BTreeNode* right = new BTreeNode(true,newRoot);

      newRoot->keys[0] = node->keys[2];
      left->keys[0] = node->keys[0];
      left->keys[1] = node->keys[1];
      right->keys[0] = node->keys[2];
      right->keys[1] = node->keys[3];
      newRoot->children[0] = left;
      newRoot->children[1] = right;
      newRoot->currentKeyNumber = 1;
      left->currentKeyNumber = 2;
      right->currentKeyNumber = 2;
      root = newRoot;
    }

    else {    // this is not root
      BTreeNode* left = new BTreeNode(true,parent);
      BTreeNode* right = new BTreeNode(true,parent);
      left->keys[0] = node->keys[0];
      left->keys[1] = node->keys[1];
      right->keys[0] = node->keys[2];
      right->keys[1] = node->keys[3];
      left->currentKeyNumber = 2;
      right->currentKeyNumber = 2;
      // right->keys[0] 顶上去
      int i=parent->currentKeyNumber-1;
      while((i >= 0) && bigger(parent->keys[i]->getName(), right->keys[0]->getName())) {
        parent->keys[i+1] = parent->keys[i];
        parent->children[i+2] = parent->children[i+1];
	i--;
      }
      
      parent->keys[i+1] = right->keys[0];
      parent->children[i+1] = left;
      parent->children[i+2] = right;      
      parent->currentKeyNumber++;
      
      if(parent->currentKeyNumber == 5) {
	splitNonLeaf(parent);
      }
    }

    delete node;
  }

  void splitNonLeaf(BTreeNode* node) {
    cout << "splitNonLeaf!!!!!!!!!!!!!!!!!!!" << endl;
    BTreeNode* parent = node->parent;
    BTreeNode* left = new BTreeNode(false,parent);
    BTreeNode* right = new BTreeNode(false,parent);

    // copy all the keys
    left->keys[0]  = node->keys[0];
    left->keys[1]  = node->keys[1];
    std::string goesUp  = node->keys[2]->getName();
    right->keys[0] = node->keys[3];
    right->keys[1] = node->keys[4];
    left->currentKeyNumber = 2;
    right->currentKeyNumber = 2;
    
    // copy all the children
    left->children[0] = node->children[0];
    left->children[1] = node->children[1];
    left->children[2] = node->children[2];
    right->children[0] = node->children[3];
    right->children[1] = node->children[4];
    right->children[2] = node->children[5];

    left->children[0]->parent = left;
    left->children[1]->parent = left;
    left->children[2]->parent = left;
    right->children[0]->parent = right;
    right->children[1]->parent = right;
    right->children[2]->parent = right;
    
    if(parent != NULL) { // this is not the root 
      // find place in the parent to put int goesUp
      int i = parent->currentKeyNumber-1;
      while((i >= 0) && bigger(parent->keys[i]->getName(), goesUp)) {
	parent->keys[i+1] = parent->keys[i];
	parent->children[i+2] = parent->children[i+1];
	i--;
      }
      
      parent->keys[i+1]->setName(goesUp);
      parent->children[i+1] = left;
      parent->children[i+2] = right;
      
      parent->currentKeyNumber++;
      if(parent->currentKeyNumber == 5) {
	splitNonLeaf(parent);
      }
    }       

    else {    // this is the root
      BTreeNode* newRoot = new BTreeNode(false,NULL);
      left->parent = newRoot;
      right->parent = newRoot;

      newRoot->keys[0] = new Node(goesUp);
      newRoot->children[0] = left;
      newRoot->children[1] = right;
      newRoot->currentKeyNumber = 1;
      
      root = newRoot;
    }

    delete node;
    
  }
  

  BTreeNode* find(string k) { // find the leaf to insert k
    return find(k,root);
  }
  
  BTreeNode* find(string k, BTreeNode* node) {
    cout << "k=" << k << ",";
    if(node->isLeaf == true) {
      cout << "isLeaf=" << node->isLeaf << endl;
      return node;
    }


    else {
      int i=0;
      while( bigger(k, node->keys[i]->getName()) && i<4) {
	i++;
      }
      // now i is the index of child pointer
      return find(k,node->children[i]);
    }   
  }

  void printTree() {
    printTree(root);
  }

  void printTree(BTreeNode* node) {
    if(node != NULL) {   
      cout << "isLeaf=" << node->isLeaf << ", " << "keyList=";

      printKeyList(node);
      
      cout << ", " << "currentKeyNumber=" << node->currentKeyNumber << ", ";
      
      cout << "parent's keyList=";
      printKeyList(node->parent);
      cout << endl;
      
      
      for(int i=0; i<6; i++) {
	printTree(node->children[i]);
      }
      
    }
  }
    
  void printKeyList(BTreeNode* node) {
    if(node != NULL) {
      cout << "[";
      for(int i=0; i<5; i++) {
	if(node->keys[i]->getName() != "zzzzzzzzzzzzz") {
	  cout << node->keys[i]->getName();
	}
	else {
	  cout << "X";
	}
	if(i != 4) { cout << ",";}
      }
      cout << "]";
    }
  }

  bool bigger(string s1, string s2) {
    int i = 0;
    
    while((s1[i] == s2[i]) && (i < s1.length()-1) && (i < s2.length()-1)) {
      i++;
    }
    
    if(s1[i] > s2[i])  { return true;}
    else { return false;}

  }

  /*
  vector<int> getAllIndex(string name1, string name2) {
    string small;
    string large;
    
    if(bigger(name1,name2)) {
      small = name2;
      large = name1;
    }
    else {
      small = name1;
      large = name2;
    }

    return range(small,large,root);    
  }

  vector<int> getAllIndex(string small, string large, BTreeNode* node) {
    

  }
  */
  
 private:
  BTreeNode* root;
  
};
