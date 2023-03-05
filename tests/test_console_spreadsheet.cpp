#include<gtest/gtest.h>
#include"console_spreadsheet.h"


using namespace ::testing;

/*
Input:                  Output:
5	6	A1+B1           5   6   11
7	8	A2+B2           7   8   15
		C1*C2                   165

*/
TEST(Console_Spreadsheet, GoodCase1) {
    //the path is relative to ProjectCT_tst.exe in build files
    Spreadsheet T1("..\\..\\tests\\spreadsheet_test1_input.txt");
    std::stringstream ss;
    std::stringstream ss_exp;
    T1.parseTextFile();
    T1.evaluate();
    T1.streamOutput(ss);
    ss_exp<<"5"<<"\t"<<"6"<<"\t"<<"11"<<"\t"<<endl;
    ss_exp<<"7"<<"\t"<<"8"<<"\t"<<"15"<<"\t"<<endl;
    ss_exp<<""<<"\t"<<""<<"\t"<<"165"<<"\t"<<endl;
    auto s1=ss.str();
    auto s2=ss_exp.str();
    EXPECT_EQ(s1,s2); 
}

/*
Input:                  Output:
5	6	                5   6   
	8	                    8   
		A1+B1+A2                  #NAN
*/
TEST(Console_Spreadsheet, BadCase1) {
    //the path is relative to ProjectCT_tst.exe in build files
    Spreadsheet T1("..\\..\\tests\\spreadsheet_test2_input.txt");
    std::stringstream ss;
    std::stringstream ss_exp;
    T1.parseTextFile();
    T1.evaluate();
    T1.streamOutput(ss);
    ss_exp<<"5"<<"\t"<<"6"<<"\t"<<"\t"<<endl;
    ss_exp<<""<<"\t"<<"8"<<"\t"<<"\t"<<endl;
    ss_exp<<""<<"\t"<<""<<"\t"<<"#NAN"<<"\t"<<endl;
    auto s1=ss.str();
    auto s2=ss_exp.str();
    EXPECT_EQ(s1,s2); 
}

/*
Input:                  Output:
1	45	=A1+B1+C3       1   45  #ERROR
1	4	                1   4
		=C1+A2                  #ERROR  
*/
TEST(Console_Spreadsheet, circular_refs) {
    //the path is relative to ProjectCT_tst.exe in build files
    Spreadsheet T1("..\\..\\tests\\spreadsheet_test3_input.txt");
    std::stringstream ss;
    std::stringstream ss_exp;
    T1.parseTextFile();
    T1.evaluate();
    T1.streamOutput(ss);
    ss_exp<<"1"<<"\t"<<"45"<<"\t"<<"#ERROR"<<"\t"<<endl;
    ss_exp<<"1"<<"\t"<<"4"<<"\t"<<"\t"<<endl;
    ss_exp<<""<<"\t"<<""<<"\t"<<"#ERROR"<<"\t"<<endl;
    auto s1=ss.str();
    auto s2=ss_exp.str();
    EXPECT_EQ(s1,s2); 
}