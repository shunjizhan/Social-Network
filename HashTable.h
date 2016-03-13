#include <vector>
#include "Node.h"
using namespace std;

class HashTable {
 public:
  const static int TABLE_SIZE = 211;
  
  HashTable();
  void insert(string name, int index, vector<string> friends);
  int search(string name);  // find index in the hash table
  int hash(string name);
  void addFriend(string friend1, string friend2);
  void printAll();
  int getUserIndex(string name);
  void printUser(vector<string> info);
   
 private:
  Node** table;
  
};



