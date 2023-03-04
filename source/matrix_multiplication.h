#include<iostream>
#include<random>
#include<vector>
#include<chrono>
#include<array>
#include<future>

using namespace std;

using namespace std::chrono_literals;

#define MATRIX_SIZE 4096
#define BLOCK_SIZE 128

#define M(pointer,size,i,j) *((double*)pointer + (i*size) + j) 

class matrix_multiplication{
    private:
    chrono::milliseconds duration;
    
    public: 
    matrix_multiplication();
    template<size_t SIZE> void create_rand_sqaurematrix(vector<array<double,SIZE>>& matrix,bool fill);
    template<size_t SIZE> void mul_sqaureMatrices(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC);
    template<size_t SIZE> void mul_sqaureMatrices_byTranspose(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC);
    template<size_t SIZE> void mul_sqaureMatrices_Blockwise(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC);
    template<size_t SIZE> void mul_sqaureMatrices_multithread(size_t threadCount,vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC);
    
    int get_execution_time();
    template<size_t SIZE>void util_transposeMatrix(vector<array<double,SIZE>>& B,vector<array<double,SIZE>>& B_Transpose);
    template<size_t SIZE>void util_dotProductRows(int firstIndex, int lastIndex, vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC);
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
    this->util_transposeMatrix(inB,b_transpose);
    this->util_dotProductRows(0,resC.size(),inA,b_transpose,resC);
    
    auto stop = chrono::high_resolution_clock::now();
    this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}

template<size_t SIZE> void matrix_multiplication::mul_sqaureMatrices_Blockwise(vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC)
{
    auto start = chrono::high_resolution_clock::now();
    vector<array<double,SIZE>> b_transpose(SIZE);
    this->util_transposeMatrix(inB,b_transpose);
    for(int i=0; i < resC.size(); i=i+BLOCK_SIZE)
    {
        for(int j=0; j<resC.size(); j=j+BLOCK_SIZE)
        {
            this->util_dotProductRows(i, i+BLOCK_SIZE,inA,b_transpose,resC);
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}

template<size_t SIZE> void matrix_multiplication::mul_sqaureMatrices_multithread(size_t threadCount,vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC)
{
    auto start = chrono::high_resolution_clock::now();
    vector<array<double,SIZE>> b_transpose(SIZE);
    this->util_transposeMatrix(inB,b_transpose);

    auto f_thread_dotproduct=[&inA, &b_transpose, &resC](size_t start, size_t last) {
            for (size_t row = start; row < last; row++){
                for (size_t col = 0; col < SIZE; col++){
                    resC[row][col]=0;
                    for (size_t col_t = 0; col_t < SIZE; col_t++){
                        resC[row][col] += inA[row][col_t] * b_transpose[col][col_t];
                    }
                }
            }
        };

    vector<size_t> row_seq;
    size_t groupSize=SIZE / threadCount;
    for(size_t thread_n=0; thread_n < SIZE; thread_n += groupSize){
        row_seq.push_back(thread_n);
    }

    vector<std::future<void>> results; 
    results.reserve(groupSize + 1);
    for (size_t i = 0; i < row_seq.size() - 1; i++){
        results.emplace_back(std::async(launch::async, f_thread_dotproduct, row_seq[i], row_seq[i + 1]));
    }
    for (auto& x : results){
        x.get();
    }

    auto stop = chrono::high_resolution_clock::now();
    this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}




/**************************utility helper functions******************************************/
template<size_t SIZE>void matrix_multiplication::util_transposeMatrix(vector<array<double,SIZE>>& B,vector<array<double,SIZE>>& B_Transpose)
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            B_Transpose[i][j]=B[j][i];
        }
    }
}

template<size_t SIZE> void matrix_multiplication::util_dotProductRows(int firstIndex, int lastIndex, vector<array<double,SIZE>>& inA,vector<array<double,SIZE>>& inB, vector<array<double,SIZE>>& resC)
{
    for(int k=firstIndex; k <lastIndex; k++)
            {
                for(int l=firstIndex; l < lastIndex; l++)
                {
                    resC[k][l]=0;
                    for( int x=0; x< resC.size(); x++)
                    {
                        resC[k][l] += inA[k][x]*inB[l][x];
                    }
                }
        
            }
}