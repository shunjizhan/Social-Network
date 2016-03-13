#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
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

int main()
{
  HashTable hashtable;
  BTree btree;

  btree.insert(12);
  
  btree.insert(10);
  
  btree.insert(15);
  
  btree.insert(5);  
  
  btree.insert(1);
  
  btree.insert(17);
  
  btree.insert(3);
  
  btree.insert(13);
  
  btree.insert(8);
  
  btree.insert(2);
  
  btree.insert(7);
  
  btree.insert(4);
  
  btree.insert(6);

	
	ifstream f;
	f.open("Generated1.txt", ios::in);
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

		}
	}

	//hashtable.printAll();
	
	return 0;
}
