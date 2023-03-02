#include<iostream>
#include<vector>
#include<chrono>
#include<array>

using namespace std;

class Binomial_Coefficient
{
    double res;

    public:
    int n;
    int k;
    chrono::milliseconds duration;
   
    Binomial_Coefficient(int num,int den);
    double calculate_binCoeff();
    double calculate_binCoeff_opt1();
};