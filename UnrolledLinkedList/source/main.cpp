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
    int optimalCapacity = calculate_optimal_node_size(arr.size(), sizeof(int));
    UnrolledLinkedList<int> m(arr, optimalCapacity);
    m.print();
    for(auto v: arr)
        m.pushBack(v);
    //m.pushBack(99);
    m.print();
    //m.pasteAtIndex(999, 11);
    //int ind;
    //std::cin>>ind;
    //m.removeAtIndex(ind);
    m.resize(5);
    m.print();
    //std::cout<<m.find(ind);
}