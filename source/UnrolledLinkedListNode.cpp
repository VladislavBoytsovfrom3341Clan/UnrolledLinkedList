#include"UnrolledLinkedListNode.h"
#include<iostream>

template<typename T>
UnrolledLinkedListNode<T>::UnrolledLinkedListNode(int capacity): mCapacity{capacity}
{
    mNext=nullptr;
    mPrev = nullptr;
    mLength=0;
    mNodeArray = new T[capacity];
}

template<typename T>
UnrolledLinkedListNode<T>::~UnrolledLinkedListNode()
{
    this->remove();
}

template<typename T>
void UnrolledLinkedListNode<T>::pushBack(const T& value)
{
    this->insert(value, this->mLength);
}

template<typename T>
void UnrolledLinkedListNode<T>::insert(const T& value, const int index)
{
    if(index>=mCapacity)
        throw std::invalid_argument("Invalid index");
    this->mLength++;

    //moving all elements after index to 1 position to right
    for(int i=mLength; i>index;i--)
        mNodeArray[i]=mNodeArray[i-1];
    mNodeArray[index]=value;
}

template<typename T>
T& UnrolledLinkedListNode<T>::operator[] (const int index)
{
    if(index<0 or index>=mLength)
        throw std::length_error("Invalid index");
    return mNodeArray[index];
}

template<typename T>
void UnrolledLinkedListNode<T>::cut(const int index)
{
    if(index<0 or index>=mLength)
        throw std::length_error("Invalid index");
    for(int i=index;i<mLength-1;i++)
        mNodeArray[i]=mNodeArray[i+1];
    mLength--;
}

template<typename T>
void UnrolledLinkedListNode<T>::remove()
{
    delete[] mNodeArray;
    mLength=0;
    mNext=nullptr;
}

template class UnrolledLinkedListNode<int>;