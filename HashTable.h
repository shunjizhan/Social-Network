#include "Node.h"
#include "BTree.h"
using namespace std;

class HashTable {
 public:
  const static int TABLE_SIZE = 211;
  
  HashTable() {
    table = new Node*[211];
    for(int i=0; i<211; i++) {
      table[i] = NULL;
    }
  }

  void insert(string name) {
    int h = hash(name);
    Node* node = new Node(name);
    while(table[h] != NULL) {
      h++;
    }
    table[h] = node;
  }

  int search(string name) {
    int h = hash(name);
    while(table[h]->getName() != name) {
      h++;
      if(table[h] == NULL) {
	return -1;
      }
    }
    return h;
  }
  
  int hash(string name) {
    int hash = 0;
    for(int i=0; i<name.length(); i++) {
      hash = (hash*101 + name[i]) % TABLE_SIZE;
    }
    return hash;
  }

  void printAll() {
    
  }
   
 private:
  Node** table;
  
};
