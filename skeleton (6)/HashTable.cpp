#include <climits>
#include "HashTable.h"
#include "Student.h"

using namespace std;

// TODO: Task 4.1
HashTable::HashTable(int size) : size{size}{
    table = new LinkedList[size];
    for(int i = 0; i < size; i++){
      table[i].clear();
    }
}

// TODO: Task 4.2
HashTable::~HashTable() {
  if(table){
    delete [] table;
  }

}

// TODO: Task 4.3
int HashTable::hash(int sid) {
    return (sid * sid) % INT_MAX;
}

// TODO: Task 4.4
void HashTable::add(Student* student) {
    if(student){
        int current = hash(student->getSid()) % size;
        table[current].add(student);
    }
}

// TODO: Task 4.5
Student* HashTable::get(int sid) const {
    int current = hash(sid) % size;
    for(LLNode* cur = table[current].getHead(); cur != nullptr; cur = cur->getNext())
        if(cur->getData()->getSid() == sid){
            return cur->getData();
        }
    return nullptr;
}

// TODO: Task 4.6
void HashTable::remove(const Student* student) {
    if(student){
        int index = hash(student->getSid()) % size;
        table[index].remove(student);
    }
}

// GIVEN: DO NOT EDIT
void HashTable::printTable() const {
    for (int i = 0; i < size; i++) {
        cout << "table[" << i << "] = " << table[i] << endl;
    }
}