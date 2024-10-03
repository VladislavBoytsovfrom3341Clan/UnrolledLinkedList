#include<iostream>
#include<vector>
#include"UnrolledLinkedList.h"

std::vector<int> getParts(std::string inp)
{
    std::vector<int> partsOfString;
    std::string temp;
    for(auto sym = inp.begin(); sym!= inp.end(); sym++)
    {
        if(*sym!=' ')
            temp+=*sym;
        else
        {
            partsOfString.push_back(std::stoi(temp));
            temp.clear();
        }
    }
    partsOfString.push_back(std::stoi(temp));
    return partsOfString;
}

template class UnrolledLinkedList<int>;

int main()
{
    std::string inp;
    getline(std::cin, inp);
    std::vector<int> arr=getParts(inp);
    //int optimalCapacity = calculate_optimal_node_size(arr.size(), sizeof(int));
    //UnrolledLinkedList<int> m(arr, 5);
    
    UnrolledLinkedList<int> m(5);
    for(auto v: arr)
        m.pushBack(v);
    //m.pushBack(99);
    m.print();
    for(int i=0;i<25; i++)
        m.pasteAtIndex(999, m.length()/3);
    m.print();
    for(int i=0; i<20; i++)
        m.removeAtIndex(m.length()/4);
    //m.removeAtIndex(ind);
    m.print();
    //std::cout<<m.find(ind);
}