#include "uniteller.h"
#include "test_runner.h"
#include "profile.h"

#include <iostream>

#include <future>

using namespace std;

void TestOverflow()
{
    Identificator temp;
    temp.Set("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z8");
    ASSERT_EQUAL("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9", temp.Increment());
    ASSERT_EQUAL("A1", temp.Increment());
    ASSERT_EQUAL("A2", temp.Increment());
}

void TestForbiddenSymbols()
{
    Identificator temp;
    temp.Set("A1-C8");
    ASSERT_EQUAL("A1-C9", temp.Increment());
    ASSERT_EQUAL("A1-E1", temp.Increment());
    ASSERT_EQUAL("A1-E2", temp.Increment());
}

void TestNextPair()
{
    Identificator temp;
    temp.Set("Z8");
    ASSERT_EQUAL("Z9", temp.Increment());
    ASSERT_EQUAL("A1-A1", temp.Increment());
    ASSERT_EQUAL("A1-A2", temp.Increment());
}

void IncrementCount(Identificator &x, const int count)
{
    for (int i = 0; i < count; i++)
    {
        string temp = x.Increment();
    }
}

void TestMulti()
{
    Identificator temp;

    temp.Set("A1");

    int count_part = 200000;
    int count = 200000 * 5;
    string result;

    for (int i = 0; i < count; i++)
    {
        result = temp.Increment();
    }

    result = temp.Increment();

    temp.Set("A1");

    auto future_1 = async(IncrementCount, ref(temp), count_part);
    auto future_2 = async(IncrementCount, ref(temp), count_part);
    auto future_3 = async(IncrementCount, ref(temp), count_part);
    auto future_4 = async(IncrementCount, ref(temp), count_part);
    auto future_5 = async(IncrementCount, ref(temp), count_part);

    future_1.get();
    future_2.get();
    future_3.get();
    future_4.get();
    future_5.get();

    ASSERT_EQUAL(result, temp.Increment());
}

int main()
{
    TestRunner runner;

    RUN_TEST(runner, TestOverflow);
    RUN_TEST(runner, TestForbiddenSymbols);
    RUN_TEST(runner, TestNextPair);

    {
        LOG_DURATION("Multi");
        RUN_TEST(runner, TestMulti);
    }

    return 0;
}