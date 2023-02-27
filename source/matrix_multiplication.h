#include<iostream>
#include<random>
#include<vector>
#include<chrono>

using namespace std;

void create_rand_sqaurematrix(int m_size, vector<vector<double>>& vmatrix);
void multiply_sqaureMatrices(vector<vector<double>>& inA,vector<vector<double>>& inB, vector<vector<double>>& resC);