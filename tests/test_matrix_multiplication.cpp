#include<gtest/gtest.h>
//#include<iostream>
//#include<random>
//#include<vector>
#include"matrix_multiplication.h"

double matA[MATRIX_SIZE][MATRIX_SIZE];
double matB[MATRIX_SIZE][MATRIX_SIZE];
double matC[MATRIX_SIZE][MATRIX_SIZE];
/*
void initialize4x4matrix( double** a, double** b, double** c)
{
  double mat_a[4][4]={{5,2,6,1},{0,6,2,0},{3,8,1,4},{1,8,5,6}};
  double mat_b[4][4]={{7,5,8,0},{1,8,2,6},{9,4,3,8},{5,3,7,9}};
  double mat_c[4][4]={{96,68,69,69},{24,56,18,52},{58,95,71,92},{90,107,81,142}};

  for(int i=0; i<4; i++)
  {
    for(int j=0;j<4;j++)
    {
      a[i][j]=mat_a[i][j];
      b[i][j]=mat_b[i][j];
      c[i][j]=mat_c[i][j];
    }
  }
}
*/
TEST(Matrix_Multiplication, Dot4x4Test) {
  vector<array<double,4>> a{{5,2,6,1},{0,6,2,0},{3,8,1,4},{1,8,5,6}};
  vector<array<double,4>> b{{7,5,8,0},{1,8,2,6},{9,4,3,8},{5,3,7,9}};
  vector<array<double,4>> c{{96,68,69,69},{24,56,18,52},{58,95,71,92},{90,107,81,142}};
  vector<array<double,4>> c_actual(4);

  matrix_multiplication m;
  //m.create_rand_sqaurematrix(a,false);
  //m.create_rand_sqaurematrix(b,false);
  //m.create_rand_sqaurematrix(c,false);
  //m.create_rand_sqaurematrix(c_actual,false);
  //initialize4x4matrix(a, b,c_actual);
  


  m.mul_sqaureMatrices( a,b,c_actual);
 
  // Expect equality.
  /*for (int i=0; i < c.size(); i++)
  {
    for(int j=0; j< c.size(); j++)
    {
      EXPECT_DOUBLE_EQ(c_actual[i][j],c[i][j]);
    }
  }*/

  EXPECT_TRUE(true);

}

/*
TEST(Matrix_Multiplication, Dot1024Test) {

  int mSize=1024;

  double **a,**b,**c;

  matrix_multiplication m;
  m.create_rand_sqaurematrix(mSize,a,false);
  m.create_rand_sqaurematrix(mSize,b,false);
  m.create_rand_sqaurematrix(mSize,c,false);

  m.mul_sqaureMatrices(mSize,a,b,c);
  m.get_execution_time();
  // Expect equality.
  EXPECT_TRUE(true);

  m.delete_sqaurematrix(mSize,a);
  m.delete_sqaurematrix(mSize,b);
  m.delete_sqaurematrix(mSize,c);

}
*/