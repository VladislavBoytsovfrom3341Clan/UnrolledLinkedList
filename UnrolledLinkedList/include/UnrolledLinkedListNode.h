#pragma once

template<typename T>
class UnrolledLinkedListNode
{
public:
    /** Members of the class are made public
     * for accessebility from
     * the linked list */

    //array with type <T> elements
    T* mNodeArray;

    //current number of elements in Node
    int mLength;

    //maximal size of Node's array
    int mCapacity;

    //Linked list pointers
    UnrolledLinkedListNode<T>* mNext;
    UnrolledLinkedListNode<T>* mPrev;

    UnrolledLinkedListNode(int capacity);

    //deletes the node from linked list
    void remove();

    //deletes <index> elem, moving nexto ones forward
    void cut(const int index);

    //inserts the <value> on <index> positions 
    void insert(const T& value, const int index);

    //addes the <value> to the end of the node
    void pushBack(const T& value);

    T& operator[] (const int index);

    ~UnrolledLinkedListNode();
};

