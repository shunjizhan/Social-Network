using namespace std;

class Node {
 public:
  Node() {
    this->name = "";
    this->index = -1;
    this->friend = NULL;
  }

  Node(string name) {
    this->name = name;
    this->index = -1;
    this->friend = NULL;
  }

  void addFriend(string firend1, string friend2) {
    
  }

  string getName() { return this->name; }
  int getIndex() { return this->index; }
  Node* getFriend() { return this->friend; }

  void setName(string name){ this->name = name;}
  void setIndex(int index){ this->index = index;}

 private:

  class FriendNode {
    FriendNode(string name, FriendNode* next) {
      this->name = name;
      this->next = next;
    }
    string name;
    FriendNode* next;
  };
  
  string name;
  int index;
  FriendNode* friend;
      
};
