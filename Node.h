#include <stddef.h>
#include <string>
using namespace std;

class Node {
 public:
  Node(string name, int index);
  void addFriend(Node* next);  // add a friend to his list of friends

  // getters and setters
  string getName() { return this->name; }
  int getIndex() { return this->index; }
  Node* getNextFriend() { return this->nextFriend; }

  void setName(string name){ this->name = name;}
  void setIndex(int index){ this->index = index;}
  void setNextFriend(Node* next) { this->nextFriend = next;}

 private:
  string name;
  int index;
  Node* nextFriend;
      
};
