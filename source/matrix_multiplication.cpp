#include"matrix_multiplication.h"

matrix_multiplication::matrix_multiplication()
{
        this->duration=0ms;
}


int matrix_multiplication::get_execution_time()
{
    return this->duration.count();
}






