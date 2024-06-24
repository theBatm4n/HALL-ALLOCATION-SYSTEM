#include <iostream>
#include "LinkedList.h"
#include "Student.h"

// TODO: Task 2.2
LinkedList::LinkedList(const LinkedList& ll) : size{ll.size} {
    if(ll.head == nullptr){
      head = tail = nullptr;
      return;
    }

    head = new LLNode(ll.head->data);
    LLNode* current_ll = ll.head;
    LLNode* current = head;
    while(current_ll->next){
        current->next = new LLNode(current_ll->next->data);
        current->next->prev = current;
        current = current->next;
        current_ll = current_ll->next;
    }
    tail = current;
    
}

// TODO: Task 2.1
bool LinkedList::contains(const Student* data) const {
    LLNode* current = head;
    while(current){
      if(current->data == data)
          return true;
      current = current->next;
    }
    return false;
}

// TODO: Task 2.3
LinkedList& LinkedList::operator=(const LinkedList& ll){
  this->clear();
  this->add(ll);
  return *this;
}
