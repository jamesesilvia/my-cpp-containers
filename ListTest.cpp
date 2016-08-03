#include <stdexcept>
#include "gmock/gmock.h"
#include "List.h"
#include <list>

using namespace testing;

class AnIntegerList : public Test 
{
public:
    int testInt = 10;
    List<int> intList;

    AnIntegerList() = default;
}; 

TEST_F(AnIntegerList, CanPushFrontOnEmptyList)
{
    ASSERT_THAT(intList.size(), Eq(0));
    intList.push_front(testInt);
    ASSERT_THAT(intList.size(), Eq(1));
}

TEST_F(AnIntegerList, CanGetFrontOnSingleItemList)
{
    intList.push_front(testInt);
    auto& frontInt = intList.front();
    ASSERT_THAT(frontInt, Eq(testInt)); 
}

TEST_F(AnIntegerList, ThrowsStdLengthErrorOnEmptyFront)
{
    ASSERT_THAT(intList.size(), Eq(0));
    try
    {
        intList.front();
        ASSERT_TRUE(false);
    }
    catch(std::exception &e)
    {
        ASSERT_TRUE(true);
    }
}

TEST_F(AnIntegerList, HandlesFrontStress)
{
    std::list<int> testList {0, 1, 2, 3, 4};
    for (auto testInt : testList)
    {
        intList.push_front(testInt);
        auto theInt = intList.front();
        ASSERT_THAT(testInt, Eq(theInt));
    }
}

TEST_F(AnIntegerList, CanPushItemsToBack)
{
    std::list<int> testList {0, 1, 2, 3, 4};
    ASSERT_THAT(intList.size(), Eq(0));
    for (auto testInt : testList)
    {
        intList.push_back(testInt);
        auto theInt = intList.back();
        ASSERT_THAT(testInt, Eq(theInt));
    }
    ASSERT_THAT(intList.size(), Eq(5));
}

TEST_F(AnIntegerList, PopFrontWithSizeOfOne)
{
    ASSERT_THAT(intList.size(), Eq(0));
    intList.push_front(10);
    intList.pop_front();
    ASSERT_THAT(intList.size(), Eq(0));
}

TEST_F(AnIntegerList, PopFrontDoesntThrowOnEmpty)
{
    try
    {
        intList.pop_front();
        ASSERT_TRUE(true);
    }
    catch(std::exception &e)
    {
        ASSERT_TRUE(false);
    }
}

TEST_F(AnIntegerList, PopsFrontWithValueCheck)
{
    intList.push_front(1);
    intList.push_front(2);
    ASSERT_THAT(intList.front(), Eq(2));
    intList.pop_front();
    ASSERT_THAT(intList.front(), Eq(1));
}

TEST_F(AnIntegerList, PopBackWithSizeOfOne)
{
    ASSERT_THAT(intList.size(), Eq(0));
    intList.push_front(10);
    intList.pop_back();
    ASSERT_THAT(intList.size(), Eq(0));
}

TEST_F(AnIntegerList, PopBackDoesntThrowOnEmpty)
{
    try
    {
        intList.pop_back();
        ASSERT_TRUE(true);
    }
    catch(std::exception &e)
    {
        ASSERT_TRUE(false);
    }
}

TEST_F(AnIntegerList, PopsBackWithValueCheck)
{
    intList.push_back(1);
    intList.push_back(2);
    ASSERT_THAT(intList.back(), Eq(2));
    intList.pop_back();
    ASSERT_THAT(intList.back(), Eq(1));
}

TEST_F(AnIntegerList, AcceptsInitializationLists)
{
    List<int> testList {0, 1, 2, 3, 4, 5};
    ASSERT_THAT(testList.front(), Eq(0));
    ASSERT_THAT(testList.back(), Eq(5));
}

TEST_F(AnIntegerList, ExplicitContructor)
{
    List<int> intList(testInt);
    ASSERT_THAT(testInt, Eq(intList.front()));
}

TEST_F(AnIntegerList, CanBeIterated)
{
    auto testInt = 0;
    List<int> testList {0, 1, 2, 3, 4, 5};

    for (auto i : testList)
        ASSERT_THAT(testInt++, Eq(i));
}
