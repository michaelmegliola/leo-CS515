/* These are test for set inerface methods using Google Test */
#include "set.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

TEST(SetTest, constructorCreatesZeroSizeSet)
{ 
    Set testSet;
    EXPECT_EQ(0, testSet.size());
}
             
TEST(SetTest, eraseWhenEmptyRemainsZeroSize)
{ 
    Set testSet;
    testSet.erase("a");
    EXPECT_EQ(0, testSet.size());
}

TEST(SetTest, insertWhenEmptyHasCorrectSize)
{ 
    Set testSet;
    testSet.insert("a");
    EXPECT_EQ(1, testSet.size());
}

class SetABCTest : public ::testing::Test
{
  protected:
    virtual void SetUp()
    {
        insertABC(testSet);
    }

    void insertABC(Set &testSet)
    {
        testSet.insert("a");
        testSet.insert("b");
        testSet.insert("c");
    }

    void compareKeys(Set &testSet, string key[])
    {
        Set::Iterator it = testSet.begin();
        int i = 0;
        while (it != testSet.end())
        {
            EXPECT_EQ(key[i], *it) << " at index " << i;
            i++; it++;
        }
    }

    //virtual void TearDown() {}

    Set testSet;
};

TEST_F(SetABCTest, insertOfSameKeyRemainsSameSize)
{ 
    EXPECT_EQ(3, testSet.size());
    testSet.insert("c");
    EXPECT_EQ(3, testSet.size());
}

TEST_F(SetABCTest, clearReducesSizeToZero)
{ 
    testSet.clear();
    EXPECT_EQ(0, testSet.size());
}

TEST_F(SetABCTest, traversalWithIteratorListsCorrectItems)
{ 
    string key[] = {"a", "b", "c"};

    compareKeys(testSet, key);
}

TEST_F(SetABCTest, findOnMissingItemReturnsEnd)
{ 
    EXPECT_EQ(testSet.end(), testSet.find("e"));
}

TEST_F(SetABCTest, findOnExistingItemReturnsNonEnd)
{ 
    EXPECT_NE(testSet.end(), testSet.find("c"));
}

TEST_F(SetABCTest, eraseOfExistingItemDecrementsSizeAndCannotBeFound)
{ 
    testSet.erase("c");
    EXPECT_EQ(2, testSet.size());
    EXPECT_EQ(testSet.end(), testSet.find("c"));
}

TEST_F(SetABCTest, eraseAndInsertMultipleTimesGivesProperSizeAndOrder)
{ 
    string key[] = {"a", "b", "e", "l", "m"};
    testSet.erase("c");
    testSet.insert(key[4]);
    testSet.insert(key[3]);
    testSet.insert(key[2]);
    EXPECT_EQ(5, testSet.size());

    compareKeys(testSet, key);

    string key2[] = {"a", "b", "e", "f", "l", "m", "o", "r"};
    testSet.insert(key2[6]);
    testSet.insert(key2[0]);
    testSet.insert(key2[3]);
    testSet.insert(key2[7]);
    EXPECT_EQ(8, testSet.size());

    compareKeys(testSet, key2);

    string key3[] = {"a", "e", "f", "l", "m", "r"};
    testSet.erase("o");
    EXPECT_EQ(7, testSet.size());
    testSet.erase("o");
    EXPECT_EQ(7, testSet.size());
    testSet.erase("b");
    EXPECT_EQ(6, testSet.size());

    compareKeys(testSet, key3);
}

TEST_F(SetABCTest, insertionOperatorAfterMultipleInsertErasePrintsProperly)
{ 
    string key[] = {"a", "b", "e", "l", "m"};
    testSet.erase("c");
    testSet.insert(key[4]);
    testSet.insert(key[3]);
    testSet.insert(key[2]);

    string key2[] = {"a", "b", "e", "f", "l", "m", "o", "r"};
    testSet.insert(key2[6]);
    testSet.insert(key2[0]);
    testSet.insert(key2[3]);
    testSet.insert(key2[7]);

    testSet.erase("o");
    testSet.erase("o");
    testSet.erase("b");

    cout << "Should have a, e, f, l, m, r: " << testSet << endl;
}

class SetInsertATest : public SetABCTest
{
  protected:
    virtual void SetUp()
    {
        SetABCTest::SetUp();
        //Round out Set A
        testSet.insert("x");
        testSet.insert("y");
        testSet.insert("z");
        testSet.insert("q");
        testSet.insert("p");
    }
};

TEST_F(SetInsertATest, copyConstructorMakesCorrectSizeAndComparesAsEqual)
{
    Set s2 = testSet;
    EXPECT_EQ(8, s2.size());
    EXPECT_EQ(testSet, s2);
}

TEST_F(SetInsertATest, copyConstructorMakesSeparateCopy)
{
    Set s2 = testSet;
    testSet.clear();
    EXPECT_EQ(8, s2.size());
    EXPECT_EQ(0, testSet.size());
    EXPECT_EQ(testSet.end(), testSet.find("a"));
    EXPECT_EQ(testSet.end(), testSet.find("f"));
    cout << "Should have a, b, c, p, q, x, y, z: " << s2 << endl;
}

class SetS2ABCTest : public SetInsertATest
{
  protected:
    virtual void SetUp()
    {
        SetInsertATest::SetUp();
        insertABC(s2);
    }

    void insertSetB(Set &s2)
    {
        insertABC(s2);
        s2.insert("d");
        s2.insert("v");
        s2.insert("k");
        s2.insert("n");
        s2.insert("r");
    }

    Set s2;
};

TEST_F(SetS2ABCTest, assignmentOperatorMakesCorrectSizeAndComparesEqual)
{
    s2 = testSet;
    EXPECT_EQ(8, s2.size());
    EXPECT_EQ(testSet, s2);
}

TEST_F(SetS2ABCTest, assignmentOperatorMakesSeparateCopiesWithCorrectValues)
{
    s2 = testSet;
    s2.clear();
    insertSetB(s2);
    cout << "testSet :" << testSet << endl;
    cout << "s2 :" << s2 << endl;
}

/*---Tests with s1 = SetA and s2 = SetB---*/
class SetASetBTest : public SetS2ABCTest
{
  protected:
    virtual void SetUp()
    {
        SetInsertATest::SetUp(); //skip over SetS2ABCTest's setup
        insertSetB(s2);
    }
};

TEST_F(SetASetBTest, differenceOperator)
{
    Set diff;
    diff = testSet - s2;
    EXPECT_EQ(diff.end(), diff.find("a"));
    EXPECT_EQ(diff.end(), diff.find("b"));
    EXPECT_EQ(diff.end(), diff.find("c"));
    EXPECT_NE(diff.end(), diff.find("x"));
    EXPECT_NE(diff.end(), diff.find("y"));
    EXPECT_NE(diff.end(), diff.find("z"));
    EXPECT_NE(diff.end(), diff.find("p"));
    EXPECT_NE(diff.end(), diff.find("q"));
    EXPECT_EQ(diff.end(), diff.find("d"));
    EXPECT_EQ(diff.end(), diff.find("v"));
    EXPECT_EQ(diff.end(), diff.find("k"));
    EXPECT_EQ(diff.end(), diff.find("n"));
    EXPECT_EQ(diff.end(), diff.find("r"));
}

TEST_F(SetASetBTest, intersectOperator)
{
    Set inter;
    inter = testSet & s2;
    EXPECT_NE(inter.end(), inter.find("a"));
    EXPECT_NE(inter.end(), inter.find("b"));
    EXPECT_NE(inter.end(), inter.find("c"));
    EXPECT_EQ(inter.end(), inter.find("x"));
    EXPECT_EQ(inter.end(), inter.find("y"));
    EXPECT_EQ(inter.end(), inter.find("z"));
    EXPECT_EQ(inter.end(), inter.find("p"));
    EXPECT_EQ(inter.end(), inter.find("q"));
    EXPECT_EQ(inter.end(), inter.find("d"));
    EXPECT_EQ(inter.end(), inter.find("v"));
    EXPECT_EQ(inter.end(), inter.find("k"));
    EXPECT_EQ(inter.end(), inter.find("n"));
    EXPECT_EQ(inter.end(), inter.find("r"));
}

TEST_F(SetASetBTest, joinOperator)
{
    Set join;
    join = testSet | s2;
    EXPECT_NE(join.end(), join.find("a"));
    EXPECT_NE(join.end(), join.find("b"));
    EXPECT_NE(join.end(), join.find("c"));
    EXPECT_NE(join.end(), join.find("x"));
    EXPECT_NE(join.end(), join.find("y"));
    EXPECT_NE(join.end(), join.find("z"));
    EXPECT_NE(join.end(), join.find("p"));
    EXPECT_NE(join.end(), join.find("q"));
    EXPECT_NE(join.end(), join.find("d"));
    EXPECT_NE(join.end(), join.find("v"));
    EXPECT_NE(join.end(), join.find("k"));
    EXPECT_NE(join.end(), join.find("n"));
    EXPECT_NE(join.end(), join.find("r"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
