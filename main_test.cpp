//
// Created by ali-masa on 3/26/20.
//

#include <gtest/gtest.h>
#include "niave_matrix.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace std;

TEST(MatrixBasicTesting, MatrixBasicCreationAndDestructionAndStreaming)
{
    IMatrix<int>::type* m =  new NaiveMatrix<int>(2,2);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);

    stringstream ss;
    ss << *m;
    string repr = "[[1, 0], [0, 1]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixBasicTesting, MatrixBasicScalarAddition)
{
    IMatrix<int>::type *m = new NaiveMatrix<int>(2, 2);
    m->SetItemAt(0, 0, 1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);

    stringstream ss;
    ss << *m;
    string repr = "[[1, 0], [0, 1]]";
    ASSERT_EQ(ss.str(), repr);

    *m += 1;

    ss.str(string());

    ss << *m;
    repr = "[[2, 1], [1, 2]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixBasicTesting, MatrixBasicScalarOperations)
{
    IMatrix<int>::type* m =  new NaiveMatrix<int>(2,2);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);

    *m += 1;

    stringstream ss;
    ss << *m;
    string repr = "[[2, 1], [1, 2]]";
    ASSERT_EQ(ss.str(), repr);

    *m *= 2;

    ss.str(string());
    ss << *m;
    repr = "[[4, 2], [2, 4]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixBasicTesting, MatrixBasicMatrixAddition) {
    IMatrix<int>::type *m = new NaiveMatrix<int>(2, 2);
    m->SetItemAt(0, 0, 1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);

    IMatrix<int>::type *m2 = new NaiveMatrix<int>(2, 2);
    m2->SetItemAt(0, 0, 0);
    m2->SetItemAt(0, 1, 1);
    m2->SetItemAt(1, 0, 1);
    m2->SetItemAt(1, 1, 0);

    *m += *m2;

    stringstream ss;
    ss << *m;
    string repr = "[[1, 1], [1, 1]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixBasicTesting, MatrixBasicMatrixOperations)
{
    IMatrix<int>::type* m =  new NaiveMatrix<int>(2,2);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);

    IMatrix<int>::type* m2 =  new NaiveMatrix<int>(2,2);
    m2->SetItemAt(0, 0 ,0);
    m2->SetItemAt(0, 1, 1);
    m2->SetItemAt(1, 0, 1);
    m2->SetItemAt(1, 1, 0);

    *m += *m2;

    stringstream ss;
    ss << *m;
    string repr = "[[1, 1], [1, 1]]";
    ASSERT_EQ(ss.str(), repr);

    *m += NaiveMatrix<int>((*m2)*-1);
    *m *= *m2;
    ASSERT_TRUE(*m == *m2);
}

TEST(MatrixBasicTesting, MatrixTranspose)
{
    IMatrix<int>::type* m =  new NaiveMatrix<int>(2, 3);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(0, 2, 1);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);
    m->SetItemAt(1, 2, 0);

    stringstream ss;
    ss << *m;
    string repr = "[[1, 0, 1], [0, 1, 0]]";
    ASSERT_EQ(ss.str(), repr);

    m = &m->Transpose();
    ss.str(string());
    ss << *m;
    repr= "[[1, 0], [1, 0], [1, 0]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixAdvancedTesting, MatrixAdvancedCaluclation)
{
    IMatrix<int>::type* m =  new NaiveMatrix<int>(4,4);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);
}
