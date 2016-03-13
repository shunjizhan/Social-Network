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

vector<string> getUser(int index) {
  vector<string> allInfo;
  string line;
  ifstream myfile;
  myfile.open("Generated3.txt", ios::in);
  for (int lineno = 0; getline (myfile,line) && lineno < index+1; lineno++) {
    if (lineno == index) {
      allInfo = split(line, ',');
    }     
  }
  return allInfo;
}

void printUser(HashTable h, int index) {
  vector<string> info = getUser(index);
  h.printUser(info);
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
			//cout << btree.bigger(name, "ZZZZZZZZZZZ");
		}
	        
	}

	hashtable.printAll();

	//printUser(hashtable, 65);	
	
	return 0;
}
