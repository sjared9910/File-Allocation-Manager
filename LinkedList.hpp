#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <utility> //for swap
#include <iostream>

#include "AbstractList.hpp"
#include "Node.hpp"

template<typename T>
class LinkedList : public AbstractList<T>
{
public:
   LinkedList();
   LinkedList(const LinkedList& rhs);  
   virtual ~LinkedList();
   LinkedList& operator=( LinkedList rhs );
   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const T& newEntry);
   bool remove(int position);
   void clear();
   T getEntry(int position) const ;
   T setEntry(int position, const T& newValue);
   void swap(LinkedList& lhs, LinkedList& rhs);
        
private:
    // Pointer to first node in the chain
    Node<T>* head;
    //number of items
    int count;     
    //Gets node at position
    Node<T>* getNodeAt(int position) const;
};

#include "LinkedList.txx"

#endif 
