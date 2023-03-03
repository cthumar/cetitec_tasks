#include<gtest/gtest.h>
#include"binomial_coefficient.h"

TEST(Binomail_Coefficient, SmallInputsTest) {
    Binomial_Coefficient bn(7,3);
    EXPECT_DOUBLE_EQ(bn.calculate_binCoeff(),35);
}

TEST(Binomail_Coefficient, WrongInputs_0) {
    Binomial_Coefficient bn(0,0);
    EXPECT_DOUBLE_EQ(bn.calculate_binCoeff(),0);
}

TEST(Binomail_Coefficient, WrongInputs_NbiggerK) {
    Binomial_Coefficient bn(5,7);
    EXPECT_DOUBLE_EQ(bn.calculate_binCoeff(),0);
}

TEST(Binomail_Coefficient, BigInputsTest) {
    Binomial_Coefficient bn(29,7);
    EXPECT_DOUBLE_EQ(bn.calculate_binCoeff(),1560780);
}