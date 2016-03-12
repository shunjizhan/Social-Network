#include "Node.h"

Node::Node(string name, int index) {
    this->name = name;
    this->index = index;
    this->nextFriend = NULL;
  }

Node::Node(string name) {
    this->name = name;
    this->index = -1;
    this->nextFriend = NULL;
}
  
void Node::addFriend(Node* next) {
  Node* temp = this->getNextFriend();
  
  if(temp == NULL) {
    this->setNextFriend(next);
  }
  
  else {
    while(temp->getNextFriend() != NULL) {
      temp = temp->getNextFriend();
    }
    
    temp->setNextFriend(next);
  }
}
