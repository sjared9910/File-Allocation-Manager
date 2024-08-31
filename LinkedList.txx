#include "LinkedList.hpp"

template<typename T >
LinkedList< T >::LinkedList()
{
    //sets head to null and count to 0
    head = nullptr;
    count = 0;
}

template<typename T >
LinkedList< T >::LinkedList(const LinkedList< T >& rhs)
{
    //sets count
    count = rhs.count;
    //head of the list
    Node<T>* aphd = rhs.head;

    //if original list is empty
    if (aphd == nullptr)
    {
        head = nullptr;
    }
    else
    {
        //copies first node
        head = new Node<T>(aphd->getItem(), aphd->getNext());
        //copies remaining nodes
        aphd = aphd->getNext();
        Node<T>* p = head;
        while (aphd != nullptr)
        {
            //gets next item from original list
            Node<T>* n = new Node<T>(aphd->getItem(), aphd->getNext());
            //advances pointer to next item
            p->setNext(n);
            p = p->getNext();
            aphd = aphd->getNext();
        }
        //end of list
        p = nullptr;
    }
    //Deep copy test
    Node<T>* p = head;
    while (p != nullptr)
    {
        p = p->getNext();
    }

    p = rhs.head;
    while (p != nullptr)
    {
        p = p->getNext();
    }
}

template<typename T >
LinkedList< T >::~LinkedList()
{
    //calls clear function to deconstruct list
    clear();
}

template<typename T >
LinkedList <T>& LinkedList< T >::operator= (LinkedList< T > rhs)
{
    //copies list
    swap(*this, rhs);
    //returns copied list
    return *this;
}

template<typename T >
bool LinkedList< T >::isEmpty() const
{
    //if the list count is 0, the list is empty
    if (count == 0)
    {
        //true is returned
        return true;
    }
    //else false is returned
    return false;
}

template<typename T >
int LinkedList< T >::getLength() const
{
    //gets length count
    return count;
}

template<typename T >
bool LinkedList< T >::insert(int newPosition, const T& newEntry)
{
    //check to make sure position is valid
    if (newPosition >= 1 && newPosition <= count + 1)
    {
        //creates new node containing the new entry
        Node<T>* newNode = new Node<T>(newEntry);

        //attaches new node
        if (newPosition == 1)
        {
            //creates node at the beginning of the list
            newNode->setNext(head);
            head = newNode;
        }
        else
        {
            //gets previous node
            Node<T>* last = getNodeAt(newPosition - 1);
            //inserts new node after the previous node
            newNode->setNext(last->getNext());
            last->setNext(newNode);
        }
        //increases list count
        count++;

        return true;
    }
    return false;
}

template<typename T >
bool LinkedList< T >::remove(int position)
{
    //check to make sure position is valid
    if (position >= 1 && position <= count)
    {
        Node<T>* p = nullptr;

        if (position == 1)
        {
            //removes the first node in list
            //saves pointer to the node
            p = head;
            head = head->getNext();
        }
        else
        {
            //finds node that before the node to be removed
            Node<T>* previous = getNodeAt(position - 1);
            //pointer to node to remove
            p = previous->getNext();
            //connects previous node to forward node
            previous->setNext(p->getNext());
        }
        //returns node to system
        p->setNext(nullptr);
        delete p;
        p = nullptr;
        //decreases list count
        count--;
        //returns true is successful
        return true;
    }
    return false;
}

template<typename T >
void LinkedList< T >::clear()
{
    Node<T>* tempNode = head;
    //goes through each variable and deletes it
    while (head != nullptr)
    {
        head = head->getNext();
        //sets node to next in list
        tempNode->setNext(nullptr);
        //node is deleted
        delete tempNode;
        tempNode = head;
    }
    //count is set to 0
    count = 0;
}

template<typename T >
T LinkedList< T >::getEntry(int position) const
{
    //check to make sure position is valid
    if (position >= 1 && position <= count)
    {
        //gets node at position
        Node<T>* p = getNodeAt(position);
        //returns item at position
        return p->getItem();
    }
    //if the position isnt valid a logic error is thrown
    throw std::logic_error("Entry reference greater than list length.");
}

template<typename T >
T LinkedList< T >::setEntry(int position, const T& newValue)
{
    //check to make sure position is valid
    if (position >= 1 && position <= count)
    {
        //gets node at position
        Node<T>* p = getNodeAt(position);
        //gets old value and sets it to variable oldValue
        T oldValue = p->getItem();
        //value is changed to input value
        p->setItem(newValue);
        return oldValue;
    }
    //if the position isnt valid a logic error is thrown
    throw std::logic_error("Entry reference greater than list length.");
}

template<typename T >
void LinkedList< T >::swap(LinkedList< T >& lhs, LinkedList< T >& rhs)
{
    //swaps lhs and rhs
    std::swap(lhs.count, rhs.count);
    std::swap(lhs.head, rhs.head);
}

template<typename T >
Node<T>* LinkedList< T >::getNodeAt(int position) const
{
    //node at beginning of chain
    Node<T>* test = head;
    //counts from beginning of chain
    for (int i = 1; i < position; i++)
    {
        //finds the node at position
        test = test->getNext();
    }
    return test;
}