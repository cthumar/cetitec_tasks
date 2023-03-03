#include "binomial_coefficient.h"

Binomial_Coefficient::Binomial_Coefficient(int num, int den)
{
    this->n=num;
    this->k=den;
}

double Binomial_Coefficient::calculate_binCoeff()
{   //no optimization
    auto start = chrono::high_resolution_clock::now();
    if(k>n || n<=0 || k<=0) return 0;
    
    double res_num=1;
    double res_den=1;
    for(int i=0; i<n ;i++){
        res_num*= (n-i);
    }
    for(int i=0; i<k ;i++){
        res_den*= (k-i);
    }
    for(int i=1; i < (n-k+1); i++){
        res_den*=i;
    }

    this->res=(double)res_num/res_den;
    auto stop = chrono::high_resolution_clock::now();
    this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    return this->res;
}

double Binomial_Coefficient::calculate_binCoeff_opt1()
{   
    if(k>n || n<0 || k<0) return 0;
    //Optimization by eliminating common numerators and denominators
    //and using C(n,k)=C(n,n-k)
    auto start = chrono::high_resolution_clock::now();
    this->res=1;
    if(k > (n-k)) k=n-k;

    for(int i=0; i < k; ++i)
    {
        this->res *= (n-i);
        this->res /= (i+1);
    }
    auto stop = chrono::high_resolution_clock::now();
    this->duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    return this->res;
}