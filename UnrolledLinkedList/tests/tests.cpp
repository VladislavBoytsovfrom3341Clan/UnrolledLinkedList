#include<iostream>
#include"UnrolledLinkedList.h"
#include<vector>
#include<list>
#include <gtest/gtest.h>
#include<chrono>
#include<thread>


struct ULL_Initialisated : public testing::Test 
{
    UnrolledLinkedList<int>* myList;
    std::vector<int> reference = {1, 2, 3, 4, 5, 6, 7, 8, 10};

    void SetUp()
    {
        myList = new UnrolledLinkedList<int>(reference, calculate_optimal_node_size(reference.size(), sizeof(int)));
    }
    void TearDown() 
    { 
        delete myList; 
    }
};

TEST_F(ULL_Initialisated, vector_based) {
    ASSERT_TRUE(myList->length() == reference.size());
    for(int i=0;i<reference.size();i++)
        ASSERT_TRUE((*myList)[i]==reference.at(i));
}

TEST(ULL_Initialisation, push_back_based) {
    std::vector<int> reference = {1, 2, 3, 4, 5};
    UnrolledLinkedList<int> myList(calculate_optimal_node_size(reference.size(), sizeof(int)));
    for(auto i: reference)
        myList.pushBack(i);
    ASSERT_TRUE(myList.length() == reference.size());
    for(int i=0;i<reference.size();i++)
        ASSERT_TRUE(myList[i]==reference.at(i));
}

TEST_F(ULL_Initialisated, insert)
{
    reference.insert(reference.begin(), 888);
    myList->pasteAtIndex(888, 0);
    reference.insert(reference.begin()+2, 999);
    myList->pasteAtIndex(999, 2);
    reference.insert(reference.end(), 777);
    myList->pasteAtIndex(777, myList->length());
    ASSERT_TRUE(myList->length() == reference.size());
    for(int i=0;i<reference.size();i++)
        ASSERT_TRUE((*myList)[i]==reference.at(i));
}

TEST_F(ULL_Initialisated, erase)
{
    reference.erase(reference.begin());
    myList->removeAtIndex(0);
    reference.erase(reference.begin()+2);
    myList->removeAtIndex(2);
    reference.erase(reference.end()-1);
    myList->removeAtIndex(myList->length()-1);
    ASSERT_TRUE(myList->length() == reference.size());
    for(int i=0;i<reference.size();i++)
        ASSERT_TRUE((*myList)[i]==reference.at(i));
}

TEST_F(ULL_Initialisated, find)
{
    ASSERT_TRUE(myList->find(1)==0);
    ASSERT_TRUE(myList->find(5)==4);
    ASSERT_TRUE(myList->find(2)==1);
    ASSERT_TRUE(myList->find(99)==-1);
}

TEST_F(ULL_Initialisated, resize)
{
    myList->resize(9);
    ASSERT_TRUE(myList->length() == reference.size());
    for(int i=0;i<reference.size();i++)
        ASSERT_TRUE((*myList)[i]==reference.at(i));
}

void check(std::vector<int> arr_1, std::vector<int> arr_2)
{
    std::cout<<"\nCheck() running...\n\n";
    UnrolledLinkedList<int> myList(calculate_optimal_node_size(arr_1.size(), sizeof(int)));
    myList.print();
    for(auto i: arr_1)
    {
        myList.pushBack(i);
        myList.print();
    }
    for(auto i: arr_2)
        if(myList.find(i)!=-1)
        {
            myList.removeAtIndex(myList.find(i));
            myList.print();
        }
    std::cout<<"Check() ended successfully!\n\n";
}

namespace time_tests
{
    enum pos{START, CENTER, END};
    void combinedPositionAndSizedTest(int num, pos position)
    {
        UnrolledLinkedList<int> ULL(256);
        std::vector<int> vec;
        std::list<int> lst;

        if(position==0)
            std::cout<<"At START position";
        else if(position == 1)
            std::cout<<"At CENTER position";
        else
            std::cout<<"At END position";
        std::cout<<" with "<<num<<" elements in row:\n\n";
        auto start = std::chrono::high_resolution_clock::now();
        if(position == 0)
            for(int i=0;i<num;i++)
            {
                ULL.pasteAtIndex(0, 0);
            }
        else if (position == 1)
            for(int i=0;i<num;i++)
            {
                ULL.pasteAtIndex(0, ULL.length()/2);
            }
        else
            for(int i=0;i<num;i++)
            {
                ULL.pushBack(0);
            }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"ULL insert: "<<static_cast<double>(time.count())/1000.0<<"\n";

        if(position == 0)
            ULL.pasteAtIndex(999, ULL.length()/10);
        else if (position == 1)
                ULL.pasteAtIndex(999, ULL.length()/2);
        else
                ULL.pasteAtIndex(999, ULL.length()-(ULL.length()/10));

        start = std::chrono::high_resolution_clock::now();
        ULL.find(999);
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"ULL find: "<<static_cast<double>(time.count())/1000.0<<"\n";

        start = std::chrono::high_resolution_clock::now();
        if(position == 0)
            for(int i=0;i<num;i++)
            {
                ULL.removeAtIndex(0);
            }
        else if (position == 1)
            for(int i=0;i<num;i++)
            {
                ULL.removeAtIndex(ULL.length()/2);
            }
        else
            for(int i=0;i<num;i++)
            {
                ULL.removeAtIndex(ULL.length()-1);
            }
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"ULL remove: "<<static_cast<double>(time.count())/1000.0<<"\n\n";

        start = std::chrono::high_resolution_clock::now();
        if(position == 0)
            for(int i=0;i<num;i++)
            {
                vec.insert(vec.begin(), 0);
            }
        else if (position == 1)
            for(int i=0;i<num;i++)
            {
                vec.insert(vec.begin()+vec.size()/2, 0);
            }
        else
            for(int i=0;i<num;i++)
            {
                vec.insert(vec.end(), 0);
            }
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"Vector insert: "<<static_cast<double>(time.count())/1000.0<<"\n";

        if(position == 0)
            vec.insert(vec.begin()+vec.size()/10, 999);
        else if (position == 1)
            vec.insert(vec.begin()+vec.size()/2, 999);
        else
            vec.insert(vec.end()-vec.size()/10, 999);
        start = std::chrono::high_resolution_clock::now();
        std::find(vec.begin(), vec.end(), 999) != vec.end();
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"Vector find: "<<static_cast<double>(time.count())/1000.0<<"\n";

        start = std::chrono::high_resolution_clock::now();
        if(position == 0)
            for(int i=0;i<num;i++)
            {
                vec.erase(vec.begin());
            }
        else if (position == 1)
            for(int i=0;i<num;i++)
            {
                vec.erase(vec.begin()+vec.size()/2);
            }
        else
            for(int i=0;i<num;i++)
            {
                vec.erase(vec.end()-1);
            }
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"Vector remove: "<<static_cast<double>(time.count())/1000.0<<"\n\n";

        start = std::chrono::high_resolution_clock::now();
        if(position == 0)
            for(int i=0;i<num;i++)
            {
                lst.insert(lst.begin(), 0);
            }
        else if (position == 1)
            for(int i=0;i<num;i++)
            {
                lst.insert(std::next(lst.begin(), lst.size()/2), 0);
            }
        else
            for(int i=0;i<num;i++)
            {
                lst.insert(lst.end(), 0);
            }
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"List insert: "<<static_cast<double>(time.count())/1000.0<<"\n";

        if(position == 0)
            lst.insert(std::next(lst.begin(), lst.size()/10), 999);
        else if (position == 1)
            lst.insert(std::next(lst.begin(), lst.size()/2), 999);
        else
            lst.insert(std::next(lst.begin(), lst.size()-lst.size()/10), 999);

        start = std::chrono::high_resolution_clock::now();
        std::find(lst.begin(), lst.end(), 999) != lst.end();
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"List find: "<<static_cast<double>(time.count())/1000.0<<"\n";

        start = std::chrono::high_resolution_clock::now();
        if(position == 0)
            for(int i=0;i<num;i++)
            {
                lst.erase(lst.begin());
            }
        else if (position == 1)
            for(int i=0;i<num;i++)
            {
                lst.erase(std::next(lst.begin(), lst.size()/2));
            }
        else
            for(int i=0;i<num;i++)
            {
                lst.erase(std::prev(lst.end()));
            }
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout<<"List remove: "<<static_cast<double>(time.count())/1000.0<<"\n\n";
    }

    void runAllTests()
    {
        std::cout<<"Running All Time tests\n";
        std::vector<int> sizeTestsCollection{10, 1000, 100000};
        for(auto time: sizeTestsCollection)
        {
            combinedPositionAndSizedTest(time, START);
            combinedPositionAndSizedTest(time, CENTER);
            combinedPositionAndSizedTest(time, END);
        }
    }
}

int main(int argc, char** argv)
{
    const std::vector arr_1 = {1, 2, 3, 4, 5, 8, 99, -695, 12, 1};
    const std::vector arr_2 = {1, 99, 3, 555, -695, 1};
    check(arr_1, arr_2);

    ::testing::InitGoogleTest(&argc, argv);
    int tests_res = RUN_ALL_TESTS();
    
    time_tests::runAllTests();
    
    return tests_res;
}