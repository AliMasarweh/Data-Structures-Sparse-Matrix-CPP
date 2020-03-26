//
// Created by ali-masa on 3/26/20.
//

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace std;

TEST(MatrixBasicTesting, MatrixBasicCreationAndDestructionAndStreaming)
{
    Matrix<int>* m =  new Matrix<int>(2,2);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);

    stringstream ss;
    ss << *m;
    string repr = "[[1, 0], [0, 1]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixBasicTesting, MatrixBasicScalarOperations)
{
    Matrix<int>* m =  new Matrix<int>(2,2);
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

    stringstream ss2;
    ss2 << *m;
    repr = "[[4, 2], [2, 4]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixBasicTesting, MatrixBasicMatrixOperations)
{
    Matrix<int>* m =  new Matrix<int>(2,2);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);

    Matrix<int>* m2 =  new Matrix<int>(2,2);
    m->SetItemAt(0, 0 ,0);
    m->SetItemAt(0, 1, 1);
    m->SetItemAt(1, 0, 1);
    m->SetItemAt(1, 1, 0);

    *m += *m2;

    stringstream ss;
    ss << *m;
    string repr = "[[2, 2], [2, 2]]";
    ASSERT_EQ(ss.str(), repr);

    *m -= *m2;
    *m *= *m2;
    ASSERT_TRUE(*m == *m2);
}

TEST(MatrixBasicTesting, MatrixBasicMatrixOperations)
{
    Matrix<int>* m =  new Matrix<int>(2, 3);
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
    stringstream ss2;
    ss2 << *m;
    repr= "[[1, 0], [0, 1], [1, 0]]";
    ASSERT_EQ(ss.str(), repr);
}

TEST(MatrixAdvancedTesting, MatrixAdvancedCaluclation)
{
    Matrix<int>* m =  new Matrix<int>(4,4);
    m->SetItemAt(0, 0 ,1);
    m->SetItemAt(0, 1, 0);
    m->SetItemAt(1, 0, 0);
    m->SetItemAt(1, 1, 1);
}
