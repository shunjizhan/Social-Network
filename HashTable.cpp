#include <string>
#include "HashTable.h"
using namespace std;


HashTable::HashTable() {
  table = new Node*[TABLE_SIZE];
  for(int i=0; i<TABLE_SIZE; i++) {
    table[i] = NULL;
  }
}


void HashTable::insert(string name, int index, vector<string> words) {
  // create a new node with all the informations
  // friends start from words[3]
  Node* node = new Node(name, index);
  for(int i=3; i<words.size(); i++) {
    node->addFriend(new Node(words[i]));
  }     

  // add it to the table
  int h = hash(name);
  while(table[h] != NULL) {
    h = (h+1) % TABLE_SIZE;
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
  int count = 0;
  for(int i=0; i<TABLE_SIZE; i++) {
    if(table[i] != NULL) {
      count++;
      cout << "name=" << table[i]->getName()
	   << " index=" << table[i]->getIndex()
	   << " friend:";
      Node* thisFriend = table[i]->getNextFriend();
      while( thisFriend != NULL) {
	cout << thisFriend->getName() << ",";
	thisFriend = thisFriend->getNextFriend();
      }
      cout << endl;
      
    } // end if
  }
  cout << "number of people=" << count << endl;
}

int HashTable::getUserIndex(string name) {
  // find his index in the file, from hash table 
  return search(name);
}

void HashTable::printUser(vector<string> info) {
  for(int i=0; i<info.size(); i++) {
    cout << info[i];
    
    if(i != info.size()-1) {
      cout << ",";
    }
    
  }
  cout << endl;
}
