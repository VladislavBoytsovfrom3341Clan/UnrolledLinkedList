#include"UnrolledLinkedList.h"
#include<iostream>
#include<cmath>
#include<vector>

const int minimalCacheSize = 64;

template<typename T>
UnrolledLinkedList<T>::UnrolledLinkedList(int optimalNodeSize):mNodeSize{optimalNodeSize}
{
    mNodeNum=0;
    mHead = nullptr;
    mTail=nullptr;
}

template<typename T>
UnrolledLinkedList<T>::UnrolledLinkedList(std::vector<T> values, int optimalNodeSize):UnrolledLinkedList(optimalNodeSize)
{
    for(auto value: values)
    {
        //create a node if list hos no one
        if(mTail == nullptr)
        {
            mTail = new UnrolledLinkedListNode<T>(mNodeSize);
            mHead=mTail;
            mHead->insert(value, 0);
            mNodeNum=1;
            continue;
        }
        //if node has empty space add to an end of the node
        if(mTail->mLength<mNodeSize)
            mTail->pushBack(value);
        else
        //otherwise create a new node withous splitting an old one
        {
            UnrolledLinkedListNode<T>* newTail = new UnrolledLinkedListNode<T>(mNodeSize);
            newTail->mPrev=mTail;
            mTail->mNext=newTail;
            newTail->insert(value, 0);
            mTail=newTail;
            mNodeNum++;
        }
    }
}

template<typename T>
UnrolledLinkedList<T>::~UnrolledLinkedList()
{
    if(mTail==nullptr)
        return;
    while(mTail!=nullptr)
    {
        UnrolledLinkedListNode<T>* temp = mTail->mPrev;
        mTail->remove();
        mTail=temp;
    }
}

template<typename T>
int UnrolledLinkedList<T>::length()
{
    int length=0;
    UnrolledLinkedListNode<T>* cur=mHead;

    /**summing all nodes length
     * without array iterations**/
    while(cur!=nullptr)
    {
        length+=cur->mLength;
        cur=cur->mNext;
    }
    return length;
}

template<typename T>
int UnrolledLinkedList<T>::find(T value)
{
    //searching for <value> by all arrays iterating
    for(int i=0;i<this->length();i++)
        if((*this)[i]==value)
            return i;
    return -1;
}

template<typename T>
void UnrolledLinkedList<T>::pushBack(T value)
{
    this->pasteAtIndex(value, this->length());
}

template<typename T>
void UnrolledLinkedList<T>::split(UnrolledLinkedListNode<T>* node)
{
    UnrolledLinkedListNode<T>* newNode = new UnrolledLinkedListNode<T>(mNodeSize);
    int j=0;

    //moving half of the firts node to a new one
    for(int i=node->mLength/2; i<node->mLength; i++)
        newNode->mNodeArray[j++]=node->mNodeArray[i];

    //redefining nodes lenghts
    node->mLength/=2;
    newNode->mLength=j;

    //correcting pointers
    newNode->mNext = node->mNext;
    newNode->mPrev=node;
    node->mNext=newNode;

    mNodeNum++;
}

template<typename T>
void UnrolledLinkedList<T>::pasteAtIndex(T value, int index)
{
    if(index<0)
        throw std::invalid_argument("Invalid index");
    UnrolledLinkedListNode<T>* curPos=mHead;

    //create a node if list has no one
    if(mHead == nullptr)
    {
        mHead = new UnrolledLinkedListNode<T>(mNodeSize);
        mTail=mHead;
        mHead->insert(value, 0);
        mNodeNum=1;
        return;
    }

    //searching for a proper node by index
    while(curPos->mLength<index and curPos->mNext!=nullptr)
    {
        index-=curPos->mLength;
        curPos=curPos->mNext;
    }

    //too big index
    if(index>curPos->mLength)
        throw std::invalid_argument("Invalid index");

    //index is in list
    else
    {
        //split the node if necessary
        if(curPos->mLength>mNodeSize/2)
        {
            split(curPos);
            if(mTail->mNext!=nullptr)
                mTail=mTail->mNext;
        }

        //choose between old and new node
        if(curPos->mLength<index)
        {
            index-=curPos->mLength;
            curPos=curPos->mNext;
        }
        
        curPos->insert(value, index);
    }
}

template<typename T>
void UnrolledLinkedList<T>::print()
{
    UnrolledLinkedListNode<T>* cur=mHead;
    std::cout<<"Size: "<<mNodeSize<<std::endl;
    for(int i=0; cur!=nullptr; i++)
    {
        std::cout<<"Node "<<i<<": ("<<cur->mLength<<") [";
        for(int j=0;j<cur->mLength;j++)
            std::cout<<"_"<<cur->mNodeArray[j];
        std::cout<<" ]"<<std::endl;
        cur=cur->mNext;
    }
}

template<typename T>
T& UnrolledLinkedList<T>::operator[] (int index)
{
    if(index<0)
        throw std::length_error("Invalid index");
    UnrolledLinkedListNode<T>* cur = mHead;
    if(mHead==nullptr)
        throw std::length_error("Empty list indexation");
    while(index>=cur->mLength and cur->mNext!=nullptr)
    {
        index-=cur->mLength;
        cur=cur->mNext;
    }
    if(index>=cur->mLength)
        throw std::length_error("Invalid index");
    return cur->mNodeArray[index];
}

int calculate_optimal_node_size(const int& num_elements, const int& element_size)
{
    float totalMemory = element_size*num_elements;
    int cacheStringsAmount =ceil(totalMemory/static_cast<float>(minimalCacheSize))+1;
    return cacheStringsAmount;
}


template class UnrolledLinkedList<int>;