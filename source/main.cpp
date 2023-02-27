#include"matrix_multiplication.h"


#define MATRIX_SIZE 496


int main(void)
{
    vector<vector<double>> matA(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));
    vector<vector<double>> matB(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));
    vector<vector<double>> matC(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));
    
    
    create_rand_sqaurematrix(MATRIX_SIZE,matA);
    create_rand_sqaurematrix(MATRIX_SIZE,matB);

    auto start = chrono::high_resolution_clock::now();

    multiply_sqaureMatrices(matA,matB,matC);

    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
 
    cout << "Time taken by function: "
         << duration.count() << " milliseconds" << endl;
}

