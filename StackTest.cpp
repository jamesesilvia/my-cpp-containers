#include "gmock/gmock.h"
#include "Stack.h"

using namespace testing;

class AnIntegerStack : public Test 
{
public:
    int testInt;
    Stack<int> intStack;

    AnIntegerStack() = default;
};

TEST_F(AnIntegerStack, GetsSetUp)
{
    ASSERT_TRUE(true);
}

TEST_F(AnIntegerStack, CanHaveAnIntegerPushed)
{
    ASSERT_TRUE(intStack.Empty());
    intStack.push(testInt);
    ASSERT_THAT(intStack.Count(), Eq(1));
}

TEST_F(AnIntegerStack, CanGetTheTop)
{
    ASSERT_TRUE(intStack.Empty());
    intStack.push(testInt);
    auto topInt = intStack.Top();
    ASSERT_THAT(topInt, Eq(testInt));
}

TEST_F(AnIntegerStack, CanPop)
{
    ASSERT_TRUE(intStack.Empty());
    intStack.push(testInt);
    intStack.Pop();
    ASSERT_TRUE(intStack.Empty());
}

TEST_F(AnIntegerStack, ThrowsOnEmptyTopCall)
{
    ASSERT_TRUE(intStack.Empty());
    try
    {
        intStack.Top();
        ASSERT_TRUE(false);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }
}

TEST_F(AnIntegerStack, ThrowsOnEmptyPopCall)
{
    ASSERT_TRUE(intStack.Empty());
    try
    {
        intStack.Pop();
        ASSERT_TRUE(false);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }
}