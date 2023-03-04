#include"matrix_multiplication.h"
#include"binomial_coefficient.h"
#include "console_spreadsheet.h"

using namespace std;


int main(void)
{
    //Cells C(10,10);
    //C(0,0)="first";
    //cout <<"The cell value is "<< C('A',1) << endl;
    ifstream fin;
    fin.open("test1.txt", ifstream::out);

    if(fin.is_open()) cout << "is open"<<endl; 

     char c = fin.get();

    while (fin.good()) {
        std::cout << c;
        c = fin.get();
    }

   fin.close();


    Spreadsheet S1(".\\source\\test1.txt");
    S1.parseTextFile();
    S1.evaluate();
    S1.streamOutput();
    /*
    vector<array<double,MATRIX_SIZE>> matA(MATRIX_SIZE);
    vector<array<double,MATRIX_SIZE>> matB(MATRIX_SIZE);
    vector<array<double,MATRIX_SIZE>> matC(MATRIX_SIZE);
    
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

    
    Binomial_Coefficient bn(7,3);
    cout << "Result:" << bn.calculate_binCoeff() <<endl;
    cout << "Result:" << bn.calculate_binCoeff_opt1() <<endl;
*/
}
