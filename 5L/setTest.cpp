/* These are test for map inerface methods using Google Test */
#include "set.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

TEST(SetTest, constructorCreatesZeroSizeSet)
{ 
    Set testSet;
    EXPECT_EQ(0, testSet.size());
}
             
TEST(SetTest, insertWhileEmptyHasCorrectSize)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    EXPECT_EQ(3, testSet.size());
}

TEST(SetTest, insertOfSameKeyRemainsSameSize)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    EXPECT_EQ(3, testSet.size());
    testSet.insert(3);
    EXPECT_EQ(3, testSet.size());
}

TEST(SetTest, clearReducesSizeToZero)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    testSet.clear();
    EXPECT_EQ(0, testSet.size());
}

TEST(SetTest, findOnMissingItemReturnsFalse)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    EXPECT_FALSE(testSet.find(4));
}

TEST(SetTest, findOnExistingItemReturnsTrue)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    EXPECT_TRUE(testSet.find(3));
}

TEST(SetTest, eraseOfExistingItemDecrementsSizeAndCannotBeFound)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    testSet.erase(3);
    EXPECT_EQ(2, testSet.size());
    EXPECT_FALSE(testSet.find(3));
}

TEST(SetTest, eraseAndInsertMultipleTimesGivesProperSize)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    testSet.erase(3);
    testSet.insert(2);
    testSet.insert(4);
    testSet.insert(6);
    EXPECT_EQ(4, testSet.size());
    testSet.erase(6);
    EXPECT_EQ(3, testSet.size());
    testSet.erase(6);
    EXPECT_EQ(3, testSet.size());
    testSet.erase(1);
    EXPECT_EQ(2, testSet.size());
}

TEST(SetTest, insertionOperatorAfterMultipleInsertErasePrintsProperly)
{ 
    Set testSet;
    testSet.insert(1);
    testSet.insert(2);
    testSet.insert(3);
    testSet.erase(3);
    testSet.insert(2);
    testSet.insert(4);
    testSet.insert(6);
    testSet.erase(6);
    testSet.erase(6);
    testSet.erase(1);
    cout << "Should have 2 and 4 remaining: " << testSet << endl;
}

TEST(SetTest, copyConstructorMakesCorrectSizeAndPrintsProperly)
{
    Set testSet;
    testSet.insert(2);
    testSet.insert(4);

    Set s2 = testSet;
    EXPECT_EQ(2, s2.size());
    cout << "Should have 2 and 4: " << s2 << endl;
}

TEST(SetTest, copyConstructorMakesSeparateCopy)
{
    Set testSet;
    testSet.insert(2);
    testSet.insert(4);

    Set s2 = testSet;
    testSet.clear();
    EXPECT_EQ(2, s2.size());
    EXPECT_EQ(0, testSet.size());
    EXPECT_FALSE(testSet.find(2));
    EXPECT_FALSE(testSet.find(4));
    EXPECT_TRUE(s2.find(2));
    EXPECT_TRUE(s2.find(4));
}

TEST(SetTest, insertAfterCopyMadeMakesCorrectSizeChanges)
{
    Set testSet;
    testSet.insert(2);
    testSet.insert(4);

    Set s2 = testSet;
    testSet.clear();
    testSet.insert(1);
    testSet.insert(9);
    testSet.insert(3);
    testSet.insert(10);
    testSet.insert(21);
    testSet.insert(3);
    testSet.insert(4);
    testSet.insert(21);
    testSet.insert(33);
    testSet.insert(21);
    testSet.insert(14);
    testSet.insert(9);
    testSet.insert(1);
    EXPECT_EQ(8, testSet.size());
    cout << "Should be 1 3 4 9 10 14 21 33: " << testSet << endl;
    EXPECT_EQ(2, s2.size());
}

TEST(SetTest, assignmentOperatorMakesCorrectSize)
{
    Set testSet;
    testSet.insert(2);
    testSet.insert(4);

    Set s2 = testSet;
    testSet.clear();
    testSet.insert(1);
    testSet.insert(9);
    testSet.insert(3);
    testSet.insert(10);
    testSet.insert(21);
    testSet.insert(3);
    testSet.insert(4);
    testSet.insert(21);
    testSet.insert(33);
    testSet.insert(21);
    testSet.insert(14);
    testSet.insert(9);
    testSet.insert(1);

    s2 = testSet;
    EXPECT_EQ(8, s2.size());
}

TEST(SetTest, assignmentOperatorMakesCorrectValues)
{
    int i;
    Set testSet;
    testSet.insert(2);
    testSet.insert(4);

    Set s2 = testSet;
    testSet.clear();
    testSet.insert(1);
    testSet.insert(9);
    testSet.insert(3);
    testSet.insert(10);
    testSet.insert(21);
    testSet.insert(3);
    testSet.insert(4);
    testSet.insert(21);
    testSet.insert(33);
    testSet.insert(21);
    testSet.insert(14);
    testSet.insert(9);
    testSet.insert(1);

    s2 = testSet;
    EXPECT_EQ(testSet.find(0), s2.find(0));
    EXPECT_EQ(testSet.find(1), s2.find(1));
    EXPECT_EQ(testSet.find(2), s2.find(2));
    EXPECT_EQ(testSet.find(3), s2.find(3));
    EXPECT_EQ(testSet.find(4), s2.find(4));
    EXPECT_EQ(testSet.find(9), s2.find(9));
    EXPECT_EQ(testSet.find(10), s2.find(10));
    EXPECT_EQ(testSet.find(14), s2.find(14));
    EXPECT_EQ(testSet.find(21), s2.find(21));
    EXPECT_EQ(testSet.find(33), s2.find(33));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
