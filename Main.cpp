#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>
#include "HashTable.h"
#include "BTree.h"
using namespace std;

vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);       // turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}

	return internal;
}

vector<string> getUser(int index) {   // index is the file index 
  vector<string> allInfo;
  string line;
  ifstream myfile;
  myfile.open("Generated3.txt", ios::in);
  for (int lineno = 0; getline (myfile,line) && lineno < index+1; lineno++) {
    if (lineno == index-1) {
      allInfo = split(line, ',');
    }     
  }
  return allInfo;
}


void printUser(HashTable h, int index) {   // index is the index in the file
  vector<string> info = getUser(index);
  h.printUser(info);
}

void range(string name1, string name2, HashTable h, BTree btree) {
  vector<int> indexes = btree.getAllIndex(name1, name2);	
  for(int i=0; i<indexes.size(); i++) {
    printUser(h, indexes[i]);
  }
}

int main()
{
  HashTable hashtable;
  BTree btree;
  vector<string> user;
	
	ifstream f;
	f.open("Generated3.txt", ios::in);
	if(!f) cerr << "File not found" << endl;

	// initialize the hash table
	else
	{
	  int index=0;
		string line;
		while(std::getline(f, line))
		{
		  vector<string> words = split(line, ',');
			string name = words[0];
			int thisIndex = index;
			index++;
			hashtable.insert(name,index,words);
			btree.insert(new Node(name,index));
		}
	        
	}

	hashtable.printAll();

	range("Zjduerj","Adriaa", hashtable, btree);




	
	/*
	btree.printKeyList(btree.findLeaf("A"));
	btree.printKeyList(btree.findLeaf("B"));
	btree.printKeyList(btree.findLeaf("D"));
	btree.printKeyList(btree.findLeaf("R"));
	btree.printKeyList(btree.findLeaf("G"));
	btree.printKeyList(btree.findLeaf("H"));
	btree.printKeyList(btree.findLeaf("Q"));
	btree.printKeyList(btree.findLeaf("U"));
	btree.printKeyList(btree.findLeaf("F"));
	btree.printKeyList(btree.findLeaf("E"));
	btree.printKeyList(btree.findLeaf("N"));
	btree.printKeyList(btree.findLeaf("z"));
	btree.printKeyList(btree.findLeaf("o"));
	btree.printKeyList(btree.findLeaf("w"));
	btree.printKeyList(btree.findLeaf("p"));
	btree.printKeyList(btree.findLeaf("q"));
	btree.printKeyList(btree.findLeaf("a"));
	*/

	/*
	for(int i=0; i<65; i++) {
	  printUser(hashtable,i);	
	}
	*/
	  
	return 0;
}
