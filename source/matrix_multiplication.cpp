#include"matrix_multiplication.h"


#define MATRIX_SIZE 496



void create_rand_sqaurematrix(int m_size, vector<vector<double>>& vmatrix)
{
    std::random_device rd;
    std::mt19937_64 e64(rd());
    std::uniform_real_distribution<double> dist(0.5, 100.0);

    for (int r = 0; r < m_size; r++) {
        for (int c = 0; c < m_size; c++){
            vmatrix[r][c]=dist(e64);
        }
    }
}

void multiply_sqaureMatrices(vector<vector<double>>& inA,vector<vector<double>>& inB, vector<vector<double>>& resC)
{
    for(int i=0; i<inA.size(); i++)
    {
        for(int j=0; j<inB.size(); j++)
        {
            resC[i][j]=0;
            for( int k=0; k< inA.size(); k++)
            {
             resC[i][j] += inA[i][k]*inB[k][j];
            }
        }
    }
}