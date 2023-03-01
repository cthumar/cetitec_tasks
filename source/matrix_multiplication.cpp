#include"matrix_multiplication.h"

matrix_multiplication::matrix_multiplication()
{
        this->duration=0ms;
}

void matrix_multiplication::create_rand_sqaurematrix(int m_size, double** vmatrix, bool fill)
{
    std::random_device rd;
    std::mt19937_64 e64(rd());
    std::uniform_real_distribution<double> dist(0.5, 100.0);

    vmatrix=new double*[m_size]; 

    for (int r = 0; r < m_size; r++) {
        vmatrix[r]=new double[m_size];
        for (int c = 0; c < m_size; c++){
            if(fill) vmatrix[r][c]=dist(e64);
            else vmatrix[r][c]=0;
        }
    }
}

void matrix_multiplication::delete_sqaurematrix(int m_size, double** vmatrix)
{
    for (int r = 0; r < m_size; r++)
        delete vmatrix[r];
    delete vmatrix;
}

int matrix_multiplication::get_execution_time()
{
    return this->duration.count();
}

void matrix_multiplication::mul_sqaureMatrices(int m_size,double** inA,double** inB, double** resC)
{
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<m_size; i++)
    {
        for(int j=0; j<m_size; j++)
        {
            resC[i][j]=0;
            for( int k=0; k< m_size; k++)
            {
             resC[i][j] += inA[i][k]*inB[k][j];
            }
        }
    }
     auto stop = chrono::high_resolution_clock::now();
     this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}

void matrix_multiplication::mul_sqaureMatrices_byTranspose(int m_size,double** inA,double** inB, double** resC)
{
    auto start = chrono::high_resolution_clock::now();
    double** b_transpose; 
    this->create_rand_sqaurematrix(m_size,b_transpose,false);
    for(int i=0; i<m_size; i++)
    {

        for(int j=0; j<m_size; j++)
        {
            b_transpose[i][j]=inB[j][i];
        }
    }

    for(int i=0; i<m_size; i++)
    {
        for(int j=0; j<m_size; j++)
        {
            resC[i][j]=0;
            for( int k=0; k< m_size; k++)
            {
             resC[i][j] += inA[i][k]*b_transpose[j][k];
            }
        }
    }
    this->delete_sqaurematrix(m_size,b_transpose);
    auto stop = chrono::high_resolution_clock::now();
    this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}



