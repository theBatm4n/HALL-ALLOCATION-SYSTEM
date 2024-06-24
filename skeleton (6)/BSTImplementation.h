#ifndef __BST_IMPLEMENTATION_H__
#define __BST_IMPLEMENTATION_H__

#include "BST.h"
#include "BSTNode.h"
#include "LinkedList.h"

// TODO: Task 3.1
template <typename K>
const BST<K>* BST<K>::find(K key) const {
    if(root == nullptr)
        return nullptr;

    if(key > root->key)
        return root->right.find(key);
    else if(key < root->key)
        return root->left.find(key);
    else
        return this;

}

// TODO: Task 3.2
template <typename K>
bool BST<K>::contains(K key, const Student* student) const {
    const BST<K>* current = find(key);
    if(current != nullptr){
        LinkedList link = current->root->value;
        if(link.contains(student))
            return true;
    } 
    return false;
}

// TODO: Task 3.3
template <typename K>
int BST<K>::size() const {
    if(root){
        if(!root->value.isEmpty()){
          return root->value.getSize() + root->left.size() + root->right.size();
        }
    }
    return 0;
}

// TODO: Task 3.4
template <typename K>
void BST<K>::add(K key, Student* student){
    
    if(contains(key,student))  // already there
        return;
    
    if(root == nullptr){
        root = new BSTNode<K>(key, student);
    }
    else if(root->key < key){  // key bigger than current
        root->right.add(key, student);
    }
    else if(root->key > key){  // key smaller than current
        root->left.add(key,student);
    }
    else{
        root->add(student);
    }
}

// TODO: Task 3.5
template <typename K>
LinkedList BST<K>::getAllValues() const {
    if(this->root == nullptr || this->root->value.isEmpty())
      return LinkedList{};

    LinkedList rhs = this->root->right.getAllValues();
    rhs.add(root->value);
    LinkedList lhs = this->root->left.getAllValues();
    lhs.add(root->value);
    lhs.add(rhs);
    return lhs;

}

// TODO: Task 3.6
template <typename K>
const BST<K>* BST<K>::kthLargest(int k) const {
    if(k > size())
        return nullptr;

    if(k == 0)
        return nullptr;
    
    if(root->left.root || root->right.root){
        if(root->right.root){
            if(root->right.size() >= k)
                return root->right.kthLargest(k);  
        }
        k -= root->right.size();
        if(root->value.getSize() >= k)
            return this;
        
        k-= root->value.getSize();
        return root->left.kthLargest(k);

    }
    return this;
}

// TODO: Task 3.7
template <typename K>
void BST<K>::remove(K key){
    if(isEmpty())
        return;
    
    if(root->key > key)
        root->left.remove(key);
    else if(root->key < key)
        root->right.remove(key);
    else if(root->left.root && root->right.root){
        root->key = root->left.kthLargest(1)->getKey();
        root->value = root->left.kthLargest(1)->getValue();
        root->left.remove(root->key);
    }
    else{
        BSTNode<K>* current = root;
        root = (root->left.isEmpty())? root->right.root : root->left.root;
        current->left.root = current->right.root= nullptr;
        delete current;
    }
}

// TODO: Task 3.8
template <typename K>
void BST<K>::remove(K key, const Student* student) {
    if(isEmpty())   
        return;

    if(root->key > key)
        root->left.remove(key,student);
    else if(root->key < key)
        root->right.remove(key,student);
    else{
        root->value.remove(student);
        if(root->value.isEmpty())
            this->remove(key);
    }
}
#endif