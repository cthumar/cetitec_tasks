#include<gtest/gtest.h>
#include<iostream>
#include<random>
#include<vector>
#include"matrix_multiplication.h"


TEST(Matrix_Multiplication, Dot4x4Test) {

  std::vector<std::vector<double>> a{{5,2,6,1},{0,6,2,0},{3,8,1,4},{1,8,5,6}};
  std::vector<std::vector<double>> b{{7,5,8,0},{1,8,2,6},{9,4,3,8},{5,3,7,9}};
  std::vector<std::vector<double>> c{{96,68,69,69},{24,56,18,52},{58,95,71,92},{90,107,81,142}};
  std::vector<std::vector<double>> c_actual{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

  multiply_sqaureMatrices(a,b,c_actual);
 
  // Expect equality.
  for (int i=0; i < c.size(); i++)
  {
    for(int j=0; j< c.size(); j++)
    {
      EXPECT_DOUBLE_EQ(c_actual[i][j],c[i][j]);
    }
  }

  //ASSERT_DOUBLE_EQ(c_actual[2][2],c[2][2]);
}
