#include <string>
#include "HashTable.h"
using namespace std;

HashTable::HashTable() {
  table = new Node*[211];
  for(int i=0; i<211; i++) {
    table[i] = NULL;
  }
}

void HashTable::insert(string name, int index) {
  int h = hash(name);
  Node* node = new Node(name, index);
  while(table[h] != NULL) {
    h++;
  }
  table[h] = node;
}

int HashTable::search(string name) {
  int h = hash(name);
  while(table[h]->getName() != name) {
    h++;
      if(table[h] == NULL) {
	return -1;
      }
  }
  return h;
}

int HashTable::hash(string name) {
  int hash = 0;
  for(int i=0; i<name.length(); i++) {
    hash = (hash*101 + name[i]) % TABLE_SIZE;
  }
  return hash;
}

void HashTable::addFriend(string friend1, string friend2) {
  int firstIndex = search(friend1);
  int secondIndex = search(friend2);
  Node* first = table[firstIndex];
  Node* second = table[secondIndex];
  first->addFriend(second);
  second->addFriend(first);
}

void HashTable::printAll() {
  
}
