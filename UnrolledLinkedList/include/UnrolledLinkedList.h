#pragma once
#include"UnrolledLinkedListNode.h"
#include<vector>
extern const int minimalCacheSize;

template<typename T>
class UnrolledLinkedList
{
private:
    UnrolledLinkedListNode<T>* mHead;
    UnrolledLinkedListNode<T>* mTail;
    int mNodeSize;
    int mNodeNum;
    int size;

public:
    UnrolledLinkedList(int optimalNodeSize);

    UnrolledLinkedList(std::vector<T> vals, int optimalNodeSize);

    //returns total number of elements in list
    int length();

    //returns index of the <value> if in list, otherwise -1
    int find(T value);

    //splits <node> on two parts, adding a new node
    void split(UnrolledLinkedListNode<T>* node);

    void pushBack(T value);
    void popBack();
    //pastes a <value> on the <index> in the list
    void pasteAtIndex(T value, int index);

    void resize(int newNodeSize);

    //removes node pointed by <node>
    void removeNode(UnrolledLinkedListNode<T>* node);

    //removes element at <index>, replacing the following
    void removeAtIndex(int index);

    //prints the list by nodes
    void print();

    T& operator[] (int index);

    ~UnrolledLinkedList();
};

int calculate_optimal_node_size(const int& num_elements, const int& element_size);
