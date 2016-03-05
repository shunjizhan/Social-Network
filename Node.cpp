#include "Node.h"

Node:: Node(string name, int index) {
    this->name = name;
    this->index = index;
    this->nextFriend = NULL;
  }
  
void Node::addFriend(Node* next) {
    Node* temp = this->nextFriend;
    if(temp == NULL) {
      this->setNextFriend(next);
    }
    else {
      while(temp->getNextFriend() != NULL) {
	temp = temp->getNextFriend();
      }
      temp->getNextFriend()->setNextFriend(next);
    }
  }
