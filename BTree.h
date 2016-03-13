#include <stddef.h>
#include <iostream>
using namespace std;

class BTreeNode {
 public:
  BTreeNode(bool isLeaf, BTreeNode* parent) {
    this->keys = new int[5];
    this->children = new BTreeNode*[6];
    for(int i=0; i<5; i++) {
      keys[i] = 99;
    }
    this->parent = parent;
    for(int i=0; i<6; i++) {
      children[i] = NULL;
    }
    this->currentKeyNumber = 0;
    this->isLeaf = isLeaf;
  }
  
  int* keys;  
  BTreeNode** children;
  BTreeNode* parent;
  int currentKeyNumber;
  bool isLeaf;
  
};

class BTree {
 public:
  BTree() {
    root = NULL;
  }

  void insert(int k) {
    cout << "inserting " << k << endl;
    if(root == NULL) {
      root = new BTreeNode(true,NULL);
      root->keys[0] = k;
      root->currentKeyNumber = 1;
    }

    else {
      cout << "finding leaf to insert" << k << endl;
      BTreeNode* leafToInsert = find(k);
      
      cout << "inserting..." << endl;
      insert(k,leafToInsert);
      cout << "insert[" << k << "]complete!" << endl;
    }

    cout << "print tree........" << endl;
    printTree();
    cout << endl;
  }

  void insert(int k, BTreeNode* leaf) {
    int i=2;

    while(leaf->keys[i] > k) {
      leaf->keys[i+1] = leaf->keys[i];
      i--;
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
      while(parent->keys[i] > right->keys[0]) {
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
    int goesUp     = node->keys[2];
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
      while(parent->keys[i] > goesUp) {
	parent->keys[i+1] = parent->keys[i];
	parent->children[i+2] = parent->children[i+1];
	i--;
      }
      
      parent->keys[i+1] = goesUp;
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

      newRoot->keys[0] = goesUp;
      newRoot->children[0] = left;
      newRoot->children[1] = right;
      newRoot->currentKeyNumber = 1;
      
      root = newRoot;
    }

    delete node;
    
  }
  

  BTreeNode* find(int k) { // find the leaf to insert k 
    return find(k,root);
  }
  
  BTreeNode* find(int k, BTreeNode* node) {
    cout << "k=" << k << ",";
    if(node->isLeaf == true) {
      cout << "isLeaf=" << node->isLeaf << endl;
      return node;
    }

    else {
      int i=0;
      while(node->keys[i] < k && i<4) {
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
    //cout << "printing tree..." << endl;
    if(node != NULL) {   
      cout << "isLeaf="    
	   << node->isLeaf
	   << ", " << "keyList=";
      
      printKeyList(node);

      cout << ", " << "currentKeyNumber=" << node->currentKeyNumber << ", ";
      
      cout << "parent's keyList=";
      printKeyList(node->parent);
      cout << endl;
      
      
      for(int i=0; i<6; i++) {
	//cout << "children[" << i << "] -";
	printTree(node->children[i]);
      }
      
    }
  }
    
  void printKeyList(BTreeNode* node) {
    if(node != NULL) {
      cout << "[";
      for(int i=0; i<5; i++) {
	if(node->keys[i] != 99) {
	  cout << node->keys[i];
	}
	else {
	  cout << "X";
	}
	if(i != 4) { cout << ",";}
      }
      cout << "]";
    }
  }
  

  BTreeNode* root;
  
};
