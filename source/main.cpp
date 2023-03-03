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

void create_rand_sqaurematrix(int m_size, vector<vector<double>>& vmatrix);
void multiply_sqaureMatrices_T(vector<vector<double>>& inA,vector<vector<double>>& inB, vector<vector<double>>& resC);
void multiply_sqaureMatrices_B(vector<vector<double>>& inA,vector<vector<double>>& inB, vector<vector<double>>& resC);

int main(void)
{
    vector<array<double,MATRIX_SIZE>> matA(MATRIX_SIZE);
    vector<array<double,MATRIX_SIZE>> matB(MATRIX_SIZE);
    vector<array<double,MATRIX_SIZE>> matC(MATRIX_SIZE);

    vector<vector<double>> A(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));
    vector<vector<double>> B(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));
    vector<vector<double>> C(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));
    create_rand_sqaurematrix(MATRIX_SIZE,A);
    create_rand_sqaurematrix(MATRIX_SIZE,B);
    
    
    matrix_multiplication mm;
    mm.create_rand_sqaurematrix(matA,true);
    mm.create_rand_sqaurematrix(matB,true);
    mm.create_rand_sqaurematrix(matC,false);

    //mm.mul_sqaureMatrices(matA,matB,matC);
    //cout << "The execution time withouth optimization is: " << mm.get_execution_time() << "milliseconds" << endl;
    mm.mul_sqaureMatrices_byTranspose(matA,matB,matC);
    cout << "The execution time with transpose optimization is: " << mm.get_execution_time() << "milliseconds" << endl;
    mm.mul_sqaureMatrices_Blockwise(matA,matB,matC);
    cout << "The execution time with block optimization is: " << mm.get_execution_time() << "milliseconds" << endl;
    mm.mul_sqaureMatrices_multithread(4,matA,matB,matC);
    cout << "The execution time with multithread optimization is: " << mm.get_execution_time() << "milliseconds" << endl;


    multiply_sqaureMatrices_T(A,B,C);
    multiply_sqaureMatrices_B(A,B,C);
    /*
    Binomial_Coefficient bn(7,3);
    cout << "Result:" << bn.calculate_binCoeff() <<endl;
    cout << "Result:" << bn.calculate_binCoeff_opt1() <<endl;
    
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

void multiply_sqaureMatrices_T(vector<vector<double>>& inA,vector<vector<double>>& inB, vector<vector<double>>& resC)
{
    auto start = chrono::high_resolution_clock::now();
    vector<vector<double>> b_transpose(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));

    for(int i=0; i < MATRIX_SIZE; i++){
        for(int j=0; j<MATRIX_SIZE; j++){
            b_transpose[i][j]=inB[j][i];
        }
    }

    for(int i=0; i<MATRIX_SIZE; i++)
    {
        for(int j=0; j<MATRIX_SIZE; j++)
        {
            resC[i][j]=0;
            for( int k=0; k< MATRIX_SIZE; k++)
            {
             resC[i][j] += inA[i][k]*b_transpose[j][k];
            }
        }
    }
     auto stop = chrono::high_resolution_clock::now();
     auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
     cout << "Time taken by function: "<< duration.count() << " milliseconds" << endl;
}

void multiply_sqaureMatrices_B(vector<vector<double>>& inA,vector<vector<double>>& inB, vector<vector<double>>& resC)
{
    auto start = chrono::high_resolution_clock::now();
    vector<vector<double>> b_transpose(MATRIX_SIZE,vector<double>(MATRIX_SIZE,0));
    for(int i=0; i < MATRIX_SIZE; i++){
        for(int j=0; j<MATRIX_SIZE; j++){
            b_transpose[i][j]=inB[j][i];
        }
    }
    for(int i=0; i < resC.size(); i=i+BLOCK_SIZE)
    {
        for(int j=0; j<resC.size(); j=j+BLOCK_SIZE)
        {
            for(int k=i; k <i+BLOCK_SIZE; k++)
            {
                for(int l=j; l < j+BLOCK_SIZE; l++)
                {
                    resC[k][l]=0;
                    for( int x=0; x< resC.size(); x++)
                    {
                        resC[k][l] += inA[k][x]*b_transpose[l][x];
                    }
                }
        
            }
        }
    }
     auto stop = chrono::high_resolution_clock::now();
     auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
     cout << "Time taken by function: "<< duration.count() << " milliseconds" << endl;
}