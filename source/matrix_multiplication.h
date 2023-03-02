#include<iostream>
#include<random>
#include<vector>
#include<chrono>
#include<array>

using namespace std;

using namespace std::chrono_literals;

#define MATRIX_SIZE 512
#define M(pointer,size,i,j) *((double*)pointer + (i*size) + j) 

class matrix_multiplication{
    private:
    chrono::milliseconds duration;
    
    public: 
    matrix_multiplication();
    template<size_t SIZE> void create_rand_sqaurematrix(vector<array<double,SIZE>>& matrix,bool fill);
    template<size_t SIZE> void mul_sqaureMatrices(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC);
    template<size_t SIZE> void mul_sqaureMatrices_byTranspose(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC);
    int get_execution_time();

};

template<size_t SIZE> void matrix_multiplication::create_rand_sqaurematrix(vector<array<double,SIZE>>& matrix,bool fill)
{
    std::random_device rd;
    std::mt19937_64 e64(rd());
    std::uniform_real_distribution<double> dist(0.5, 100.0);

    for (int r = 0; r < matrix.size(); r++) {   
        for (int c = 0; c < matrix.size(); c++){
            if(fill) matrix[r][c]=dist(e64);
            else matrix[r][c]=0;
        }
    }
}

template<size_t SIZE> void matrix_multiplication::mul_sqaureMatrices(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC)
{
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i < resC.size(); i++)
    {
        for(int j=0; j<resC.size(); j++)
        {
            resC[i][j]=0;
            for( int k=0; k< resC.size(); k++)
            {
             resC[i][j] += inA[i][k]*inB[k][j];
            }
        }
    }
     auto stop = chrono::high_resolution_clock::now();
     this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}

template<size_t SIZE> void matrix_multiplication::mul_sqaureMatrices_byTranspose(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC)
{
    auto start = chrono::high_resolution_clock::now();
    vector<array<double,SIZE>> b_transpose(SIZE);
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            b_transpose[i][j]=inB[j][i];
        }
    }

    for(int i=0; i<resC.size(); i++)
    {
        for(int j=0; j<resC.size(); j++)
        {
            resC[i][j]=0;
            for( int k=0; k< resC.size(); k++)
            {
             resC[i][j] += inA[i][k]*b_transpose[j][k];
            }
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}