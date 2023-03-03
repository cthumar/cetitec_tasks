#include<gtest/gtest.h>
#include"matrix_multiplication.h"

TEST(Matrix_Multiplication, Dot4x4Test) {
  vector<array<double,4>> a{{5,2,6,1},{0,6,2,0},{3,8,1,4},{1,8,5,6}};
  vector<array<double,4>> b{{7,5,8,0},{1,8,2,6},{9,4,3,8},{5,3,7,9}};
  vector<array<double,4>> c{{96,68,69,69},{24,56,18,52},{58,95,71,92},{90,107,81,142}};
  vector<array<double,4>> c_actual(4);

  matrix_multiplication m;


  m.mul_sqaureMatrices( a,b,c_actual);
 
  // Expect equality.
  for (int i=0; i < c.size(); i++)
  {
    for(int j=0; j< c.size(); j++)
    {
      EXPECT_DOUBLE_EQ(c_actual[i][j],c[i][j]);
    }
  }

  //EXPECT_TRUE(true);

}


TEST(Matrix_Multiplication, singleDotValueTest) {

  vector<array<double,512>> A(512);
  vector<array<double,512>> B(512);
  vector<array<double,512>> Res(512);
  double singleRes=0;

  matrix_multiplication m;
  m.create_rand_sqaurematrix(A,true);
  m.create_rand_sqaurematrix(B,true);
  m.create_rand_sqaurematrix(Res,false);

  m.mul_sqaureMatrices(A,B,Res);
  //Calculate single scalar value of multiplication result of index [3][3]
  for (int i=0; i<A.size(); i++)
  {
    singleRes+=A[3][i]*B[i][3];
  }
  // Expect equality.
  EXPECT_DOUBLE_EQ(singleRes,Res[3][3]);

}

TEST(Matrix_Mul_Transpose, Dot4x4Test) {
  vector<array<double,4>> a{{5,2,6,1},{0,6,2,0},{3,8,1,4},{1,8,5,6}};
  vector<array<double,4>> b{{7,5,8,0},{1,8,2,6},{9,4,3,8},{5,3,7,9}};
  vector<array<double,4>> c{{96,68,69,69},{24,56,18,52},{58,95,71,92},{90,107,81,142}};
  vector<array<double,4>> c_actual(4);

  matrix_multiplication m;


  m.mul_sqaureMatrices_byTranspose( a,b,c_actual);
 
  // Expect equality.
  for (int i=0; i < c.size(); i++)
  {
    for(int j=0; j< c.size(); j++)
    {
      EXPECT_DOUBLE_EQ(c_actual[i][j],c[i][j]);
    }
  }

}


TEST(Matrix_Mul_Transpose, singleDotValueTest) {

  vector<array<double,512>> A(512);
  vector<array<double,512>> B(512);
  vector<array<double,512>> Res(512);
  double singleRes=0;

  matrix_multiplication m;
  m.create_rand_sqaurematrix(A,true);
  m.create_rand_sqaurematrix(B,true);
  m.create_rand_sqaurematrix(Res,false);

  m.mul_sqaureMatrices_byTranspose(A,B,Res);
  //Calculate single scalar value of multiplication result of index [3][3]
  for (int i=0; i<A.size(); i++)
  {
    singleRes+=A[3][i]*B[i][3];
  }
  // Expect equality.
  EXPECT_DOUBLE_EQ(singleRes,Res[3][3]);

}



TEST(Matrix_Mul_MultiThread, singleDotValueTest) {

  vector<array<double,512>> A(512);
  vector<array<double,512>> B(512);
  vector<array<double,512>> Res(512);
  double singleRes=0;

  matrix_multiplication m;
  m.create_rand_sqaurematrix(A,true);
  m.create_rand_sqaurematrix(B,true);
  m.create_rand_sqaurematrix(Res,false);

  m.mul_sqaureMatrices_multithread(4,A,B,Res);
  //Calculate single scalar value of multiplication result of index [3][3]
  for (int i=0; i<A.size(); i++)
  {
    singleRes+=A[3][i]*B[i][3];
  }
  // Expect equality.
  EXPECT_DOUBLE_EQ(singleRes,Res[3][3]);

}
