#include"UnrolledLinkedList.h"
#include<iostream>
#include<cmath>
#include<vector>

const int minimalCacheSize = 64;

template<typename T>
UnrolledLinkedList<T>::UnrolledLinkedList(int optimalNodeSize):mNodeSize{optimalNodeSize}
{
    mNodeNum=0;
    size=0;
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
            size++;
            mNodeNum=1;
            continue;
        }

        //if node has empty space add to an end of the node
        if(mTail->mLength<mNodeSize)
        {
            mTail->pushBack(value);
            size++;
        }
        else
        //otherwise create a new node withous splitting an old one
        {
            UnrolledLinkedListNode<T>* newTail = new UnrolledLinkedListNode<T>(mNodeSize);
            newTail->mPrev=mTail;
            mTail->mNext=newTail;
            newTail->insert(value, 0);
            size++;
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
    size=0;
}

template<typename T>
int UnrolledLinkedList<T>::length()
{
    return size;
}

template<typename T>
int UnrolledLinkedList<T>::find(T value)
{
    //searching for <value> by all arrays iterating
    for(int i=0;i<size;i++)
        if((*this)[i]==value)
            return i;
    return -1;
}

template<typename T>
void UnrolledLinkedList<T>::pushBack(T value)
{
    this->pasteAtIndex(value, this->size);
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
    if(node->mNext!=nullptr)
        node->mNext->mPrev=newNode;
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
        size++;
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
        if(curPos->mLength>=mNodeSize)
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
        size++;
    }
}

template<typename T>
void UnrolledLinkedList<T>::removeNode(UnrolledLinkedListNode<T>* node)
{
    if(node==nullptr)
        return;

    //repointing surrounding nodes
    if(node->mPrev!=nullptr)
        node->mPrev->mNext=node->mNext;
    if(node->mNext!=nullptr)
        node->mNext->mPrev=node->mPrev;

    //repointing Head and Tail
    if(node==mHead)
        mHead=node->mNext;
    if(node==mTail)
        mTail=node->mPrev;
        
    node->remove();
}

template<typename T>
void UnrolledLinkedList<T>::removeAtIndex(int index)
{
    if(mHead==nullptr)
        return;
    if(index<0)
        throw std::invalid_argument("Invalid index");
    UnrolledLinkedListNode<T>* curPos=mHead;

    //searching for a proper node by index
    while(curPos->mLength<=index and curPos->mNext!=nullptr)
    {
        index-=curPos->mLength;
        curPos=curPos->mNext;
    }
    //too big index
    if(index>curPos->mLength)
        throw std::invalid_argument("Invalid index");
    else
    {
        curPos->cut(index);
        //if node was made empty, remove one
        if(curPos->mLength==0)
            removeNode(curPos);

        /** if node has not enough elements
        * replace elements with ones from next Node
        * if it exists **/
        if(curPos->mLength<mNodeSize/2 +1 and curPos->mNext!=nullptr)
        {
            //replacing element from the next node
            if(curPos->mNext->mLength>0)
            {
                curPos->pushBack(curPos->mNext->mNodeArray[0]);
                curPos->mNext->cut(0);
            }

            //removing next node if it is empty
            if(curPos->mNext->mLength==0)
                removeNode(curPos->mNext);

            /** Merging two nodes 
             * is there are a few elements */
            else if(curPos->mNext->mLength+curPos->mLength<=mNodeSize)
            {
                while(curPos->mNext->mLength>0)
                {
                    curPos->pushBack(curPos->mNext->mNodeArray[0]);
                    curPos->mNext->cut(0);
                }
                removeNode(curPos->mNext);
            }
        }
        size--;
    }
}

template<typename T>
void UnrolledLinkedList<T>::resize(int newNodeSize)
{
    if(newNodeSize==mNodeSize)
        return;
    if(newNodeSize<=0)
        throw std::length_error("Invalid new node size");
    UnrolledLinkedListNode<T>* newHead = new UnrolledLinkedListNode<T>(newNodeSize);
    UnrolledLinkedListNode<T>* cur = newHead;
    int curIndex=0, newNodeNum=0;
    for(int i=0; i<this->length(); i++)
    {
        if(curIndex>=newNodeSize)
        {
            UnrolledLinkedListNode<T>* newNode = new UnrolledLinkedListNode<T>(newNodeSize);
            cur->mNext=newNode;
            newNode->mPrev=cur;
            cur=cur->mNext;
            curIndex=0;
            newNodeNum++;
        }
        cur->insert(this->operator[](i), curIndex++);
    }
    while(mHead!=nullptr)
    {
        mHead->remove();
        mHead=mHead->mNext;
    }
    mHead=newHead;
    mTail=cur;
    mNodeSize=newNodeSize;
    mNodeNum=newNodeNum;
}

template<typename T>
void UnrolledLinkedList<T>::popBack()
{
    this->removeNode(mTail);
}

template<typename T>
void UnrolledLinkedList<T>::print()
{
    UnrolledLinkedListNode<T>* cur=mHead;
    std::cout<<"Size: "<<mNodeSize<<" , length: "<<size<<std::endl;

    //iterating on nodes
    for(int i=0; cur!=nullptr; i++)
    {
        std::cout<<"Node "<<i<<": ("<<cur->mLength<<") [";

        //printing nodes array
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
    
    //getting proper node by index
    while(index>=cur->mLength and cur->mNext!=nullptr)
    {
        index-=cur->mLength;
        cur=cur->mNext;
    }

    //too big index
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

/** This realisation requires
 * to instance the types for class */

template class UnrolledLinkedList<int>;