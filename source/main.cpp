#include"matrix_multiplication.h"
#include"binomial_coefficient.h"

using namespace std;

//#define MATRIX_SIZE 4096
//void multiply_sqaureMatrices(double inA[][MATRIX_SIZE],double inB[][MATRIX_SIZE], double resC[][MATRIX_SIZE]);
//void create_rand_sqaurematrix(int m_size, double ppmatrix[][MATRIX_SIZE]);
//void multiply_sqaureMatrices_transpose(double inA[][MATRIX_SIZE],double inB[][MATRIX_SIZE], double resC[][MATRIX_SIZE]);

//double a[MATRIX_SIZE][MATRIX_SIZE];
//double b[MATRIX_SIZE][MATRIX_SIZE];
//double c[MATRIX_SIZE][MATRIX_SIZE];



int main(void)
{
    vector<array<double,MATRIX_SIZE>> matA(MATRIX_SIZE);
    vector<array<double,MATRIX_SIZE>> matB(MATRIX_SIZE);
    vector<array<double,MATRIX_SIZE>> matC(MATRIX_SIZE);
    
    
    matrix_multiplication mm;
    mm.create_rand_sqaurematrix(matA,true);
    mm.create_rand_sqaurematrix(matB,true);
    mm.create_rand_sqaurematrix(matC,false);
/*
    mm.mul_sqaureMatrices(matA,matB,matC);
    cout << "The execution time withouth optimization is: " << mm.get_execution_time() << "milliseconds" << endl;
    mm.mul_sqaureMatrices_byTranspose(matA,matB,matC);
    cout << "The execution time with transpose optimization is: " << mm.get_execution_time() << "milliseconds" << endl;
*/  
    Binomial_Coefficient bn(7,3);
    cout << "Result:" << bn.calculate_binCoeff() <<endl;
    cout << "Result:" << bn.calculate_binCoeff_opt1() <<endl;
    /*
    mm.mul_sqaureMatrices_byTranspose(MATRIX_SIZE,a,b,c);
    cout << "The execution time with transpose is: " << mm.get_execution_time() << "milliseconds";

    create_rand_sqaurematrix(MATRIX_SIZE,a);
    create_rand_sqaurematrix(MATRIX_SIZE,b);
    //multiply_sqaureMatrices(a,b,c);
    multiply_sqaureMatrices_transpose(a,b,c2);
    
    mm.delete_sqaurematrix(MATRIX_SIZE,a);
    mm.delete_sqaurematrix(MATRIX_SIZE,b);
    mm.delete_sqaurematrix(MATRIX_SIZE,c);
    */
}
/*
void create_rand_sqaurematrix(int m_size, double ppmatrix[][MATRIX_SIZE])
{
    std::random_device rd;
    std::mt19937_64 e64(rd());
    std::uniform_real_distribution<double> dist(0.5, 100.0);

    for (int r = 0; r < m_size; r++) {
        for (int c = 0; c < m_size; c++){
            ppmatrix[r][c]=dist(e64);
        }
    }
}

void multiply_sqaureMatrices(vector<array<double>>& inA,vector<array<double>>& inB, vector<array<double>>& resC)
{
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<MATRIX_SIZE; i++)
    {
        for(int j=0; j<MATRIX_SIZE; j++)
        {
            resC[i][j]=0;
            for( int k=0; k< MATRIX_SIZE; k++)
            {
             resC[i][j] += inA[i][k]*inB[k][j];
            }
        }
    }
     auto stop = chrono::high_resolution_clock::now();
     auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
     cout << "Time taken by function: "<< duration.count() << " milliseconds" << endl;
}

void multiply_sqaureMatrices_transpose(double inA[][MATRIX_SIZE],double inB[][MATRIX_SIZE], double resC[][MATRIX_SIZE])
{
    auto start = chrono::high_resolution_clock::now();

    for(int i=0; i<MATRIX_SIZE; i++)
    {
        for(int j=0; j<MATRIX_SIZE; j++)
        {
            bT[i][j]=inB[j][i];
        }
    }

    for(int i=0; i<MATRIX_SIZE; i++)
    {
        for(int j=0; j<MATRIX_SIZE; j++)
        {
            resC[i][j]=0;
            for( int k=0; k< MATRIX_SIZE; k++)
            {
             resC[i][j] += inA[i][k]*bT[j][k];
            }
        }
    }
     auto stop = chrono::high_resolution_clock::now();
     auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
     cout << "Time taken by function 2: "<< duration.count() << " milliseconds" << endl;
}
*/