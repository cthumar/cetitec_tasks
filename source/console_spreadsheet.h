#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<regex>

using namespace std;

class Cells{
    std::vector<std::vector<std::string>> table;

    public:
    size_t row_size;
    size_t col_size;
    Cells(size_t rowSize,size_t colSize);
    std::string operator()(char col, int row);
    std::string& operator()(int row, int col);
};

class Spreadsheet{

    ifstream inStream;

    public:
    Cells cell_table;
    Spreadsheet(std::string filename);
    ~Spreadsheet();
    void parseTextFile();
    void evaluate();
    void streamOutput(ostream& cout);


    void string_calculator(int col, int row, string str,string currentCellName);
    int getCellValue(string str, string& rslt);
    int getRowValue(string str);
    int getColValue(string str);
};