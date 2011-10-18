#include <gtest/gtest.h>
#include "matrix.h"
TEST(MultiplyTest, NormalTest)
{
    Matrix A = initMatrix(3);
    Matrix B = initMatrix(3);
    Matrix C = initMatrix(3);
    Matrix R = initMatrix(3);
    int dataA[] = {0, 0, 0,  \
        0, 0, 0,\
            0, 1, 0};
    int dataB[] = {0, 0, 1,  \
        1, 0, 0,\
            1, 1, 0};
    int dataC[] = {0, 0, 0,  \
        0, 0, 0,\
            1, 0, 0};

    loadMatrix(dataA, A, 3);
    loadMatrix(dataB, B, 3);
    loadMatrix(dataC, C, 3);
    MultiplyMatrix(A, B, R, 3); 
    int k = 0;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            EXPECT_EQ(R[i][j], dataC[k++]);
        }
    }

}


TEST(MultiplyTest, NormalTest5)
{
    Matrix A = initMatrix(5);
    Matrix B = initMatrix(5);
    Matrix C = initMatrix(5);
    Matrix R = initMatrix(5);
    int dataA[] = {
        1, 2, 3,  4, 5,\
        1, 2, 3,  4, 5,\
        1, 2, 3,  4, 5,\
        1, 2, 3,  4, 5,\
        1, 2, 3,  4, 5};
    int dataB[] = {
        1,1,1,1,1,\
        2,2,2,2,2,\
        3,3,3,3,3,\
        4,4,4,4,4,\
        5,5,5,5,5};
        int dataC[] = {55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55};

    loadMatrix(dataA, A, 5);
    loadMatrix(dataB, B, 5);
    loadMatrix(dataC, C, 5);
    MultiplyMatrix(A, B, R, 5); 
    int k = 0;
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            EXPECT_EQ(R[i][j], dataC[k++]);
        }
    }

}


