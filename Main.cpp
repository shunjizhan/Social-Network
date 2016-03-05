#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
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
	ifstream f;
	f.open("Generated1.txt", ios::in);
	if(!f) cerr << "File not found" << endl;
	else
	{
		string line;
		while(std::getline(f, line))
		{
			vector<string> words = split(line, ',');
			// ... TO DO ...
		}
	}
	return 0;
}
