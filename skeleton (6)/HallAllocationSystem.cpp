#include "HallAllocationSystem.h"
#include "BST.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Student.h"

// TODO: Task 5.1
HallAllocationSystem::HallAllocationSystem(int totalHallAvailable): totalHallAvailable(totalHallAvailable), studentPendingList() {
    studentTable = new HashTable(193);
    studentQueue = new BST<int>();
}

// TODO: Task 5.2
HallAllocationSystem::~HallAllocationSystem() {
    if(studentQueue){
        delete studentQueue;
    }
    if(studentTable){
        delete studentTable;
    }
}

// TODO: Task 5.3
void HallAllocationSystem::allocateHall() {
    
    if(!studentPendingList.isEmpty())   // 5.3 1
        return;                       
    
    LinkedList temp;
    if(studentQueue){
        while(totalHallAvailable > 0 || studentQueue->isEmpty()){
            const BST<int>* current = studentQueue->kthLargest(1);
            temp.add(current->getValue());
            totalHallAvailable -= current->getValue().getSize();
            for(LLNode* mid = temp.getHead(); mid != nullptr; mid = mid->getNext()){
                mid->getData()->setStatus(PENDING_ACTION);
            }
            studentQueue->remove(current->getKey());
        }
        if(totalHallAvailable < 0)
            totalHallAvailable = 0;
        studentPendingList.add(temp);
    }
}

// TODO: Task 5.4
void HallAllocationSystem::addStudent(Student* student) {
    if(student->getStatus() == QUEUEING){
        studentTable->add(student);
        studentQueue->add(student->getTotalHallPoints(), student);
    }
}

// TODO: Task 5.5
void HallAllocationSystem::removeStudent(const Student* student) {
    if(student){
        studentTable->remove(student);
        studentQueue->remove(student->getTotalHallPoints(), student);
        studentPendingList.remove(student);
    }
}

// TODO: Task 5.6
bool HallAllocationSystem::predict(const Student* student) const {
    if(!studentQueue->contains(student->getTotalHallPoints(),student))
        return false;
    
    int student_points = student->getTotalHallPoints();
    const BST<int>* current = studentQueue->kthLargest(totalHallAvailable);
    if(current){
        if(student_points >= current->getKey()){
            return true;
        }
    }
    return false;

}

// TODO: Task 5.7
void HallAllocationSystem::acceptOffer(Student* student) {
    if(student){
        if(studentPendingList.contains(student)){
            studentPendingList.remove(student);
            student->setStatus(ACCEPTED);
        }
    }
}

// TODO: Task 5.8
void HallAllocationSystem::rejectOffer(Student* student) {
    if(student){
        if(studentPendingList.contains(student)){
            studentPendingList.remove(student);
            student->setStatus(REJECTED);
            totalHallAvailable++;
        }
    }
}

// TODO: Task 5.9
void HallAllocationSystem::acceptAllOffers() {
    if(studentPendingList.getHead()){
        LLNode* curr = studentPendingList.getHead();
        while(curr->getNext() != nullptr){
            curr = curr->getNext();
            acceptOffer(curr->getPrev()->getData());
        }
        acceptOffer(curr->getData());
    }
}

// TODO: Task 5.10
void HallAllocationSystem::rejectAllOffers() {
   if(studentPendingList.getHead()){
        LLNode* curr = studentPendingList.getHead();
        while(curr->getNext() != nullptr){
            curr = curr->getNext();
            rejectOffer(curr->getPrev()->getData());
        }
        rejectOffer(curr->getData());
    }

}