#include<iostream>
#include<random>
#include<vector>
#include<chrono>

using namespace std;

using namespace std::chrono_literals;

#define MATRIX_SIZE 512

class matrix_multiplication{
    private:
    chrono::milliseconds duration;
    
    public: 
    matrix_multiplication();
    void create_rand_sqaurematrix(int m_size, double** vmatrix,bool fill);
    void mul_sqaureMatrices(int m_size,double** inA,double** inB, double** resC);
    void mul_sqaureMatrices_byTranspose(int m_size,double** inA,double** inB, double** resC);
    int get_execution_time();
    void delete_sqaurematrix(int m_size, double** vmatrix);
};

