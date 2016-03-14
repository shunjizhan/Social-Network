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
  myfile.open("Generated1.txt", ios::in);
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

void addLine(string s){
	  ofstream myfile;
	  myfile.open ("Generated1.txt", ios::app);
	  myfile << s << "\n";
	  myfile.close();
	}

void printAll(HashTable h, int index){
  for(int i=0; i<index ; i++){
    printUser(h, i);
  }
}


int getUserLine(string name){
  //user must already exist in the network
  int i=1;
  while(getUser(i)[0] != name){
    i++;
  }
  return i;
}


void printFriends(string name, HashTable h) {
  int tableIndex = h.search(name);
  Node* n = h.getNode(tableIndex);
  while(n->getNextFriend() != NULL) {
    n = n->getNextFriend();
    string name = n->getName();
    int line = getUserLine(name); // line in the file
    vector<string> info = getUser(line);
    string age = info[1];
    string occ = info[2];
    cout << name << "," << age << "," << occ << endl;
    
    //cout << name << line;
    //cout << endl;
  }

  cout << endl;

}


int main()
{
  HashTable hashtable;
  BTree btree;
  vector<string> user;
  int index=0;
  
	ifstream f;
	f.open("Generated1.txt", ios::in);
	if(!f) cerr << "File not found" << endl;      

	else
	{
	  cout << "~~~~~~~~~ file opened successfully ~~~~~~~" << endl << endl;
	  
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

	cout << "~~~~~~~~~ hash table initialized complete ~~~~~~~~~" << endl << endl;
	cout << "~~~~~~~~~~~ BTree initialized complete ~~~~~~~~~~~~" << endl << endl;
	
	try
	  {

	    cout << "~~~~~~~~~~~~~ program ready for input ~~~~~~~~~~~~~" << endl << endl;
	    
	    while(true)
	      {
		string str;
		cin >> str;
		if(cin.eof())
		  {
		    break;
		  }
		if(str.compare("exit") == 0)
		  {
		    break;
		  }
		else if(str.compare("insert") == 0)
		  {
		    string line;
		    std::getline(cin, line);
		    string l = "";
		    for(int i=1; i<line.size(); i++){
		      l += line[i];
		    }
		    addLine(l);
		    vector<string> inf = split(l,',');
		    string newName = inf[0];
		    hashtable.insert(newName,index,inf);
		    btree.insert(new Node(newName,index));
		    index++;
		  }
		else if(str.compare("printAll")== 0)
		  {
		    printAll(hashtable, index+1);
		    cout << endl;
		  }
		else if(str.compare("range")== 0)
		  {
		    string name1, name2;
		    cin >> name1 >> name2;
		    range(name1, name2, hashtable, btree);
		  }
		else if(str.compare("printTree")== 0)
		  {
		    btree.printTree(1);
		    cout << "\n";
		  }
		else if(str.compare("printNodes")== 0)
		  {
		    btree.printTree(0);
		    cout << "\n";
		  }
		else if(str.compare("printFriends")==0)
		  {
		    string name;
		    cin >> name;
		    printFriends(name, hashtable);
		    cout << endl;
		  }
		else if(str.compare("addFriend")==0)
		  {
		    string friend1, friend2;
		    cin >> friend1 >> friend2;
		    hashtable.addFriend(friend1, friend2);
		    cout << "~~ now " << friend1 << " and " << friend2 << " are good friends! ~~" << endl;
		  }
		else if(str.compare("printHashTable")==0)
		  {
		    hashtable.printAll();
		  }
	      }
	  }
	catch(exception& ex)
	  {
	    cerr << ex.what() << endl;
	  }

	  
	return 0;
}
