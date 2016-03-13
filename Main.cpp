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

int main()
{
  HashTable hashtable;
  BTree btree;

  	for(int i=0; i<95; i++) {
	  btree.insert(i);
	}
	
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
