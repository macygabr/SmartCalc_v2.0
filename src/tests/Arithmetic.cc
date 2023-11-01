#include <gtest/gtest.h>

#include "../Model/Model.h"

TEST(Calculation_src_test, test_1) {
  s21::Model nur;
  nur.PolishNotation("12+34-4*2^3^0.5+3^2");
  ASSERT_NEAR(nur.Arithmetic(), 41.7120116581, ACCURACY);
  //   nur.PrintString();
}

TEST(Calculation_src_test, test_2) {
  s21::Model nur;
  nur.PolishNotation("sin2+cos(2*3)/ln10+2^2");
  ASSERT_NEAR(nur.Arithmetic(), 5.32629408401, ACCURACY);
  // nur.PrintString();
}

TEST(Calculation_src_test, test_3) {
  s21::Model nur;
  nur.PolishNotation("(sin5)^2+(cos5)^2");
  ASSERT_NEAR(nur.Arithmetic(), 1, ACCURACY);
  // nur.PrintString();
}

TEST(Calculation_src_test, test_4) {
  s21::Model nur;
  nur.PolishNotation("-sqrt(5647*(9-(-78)))+46^3/250-log(1000)");
  EXPECT_NEAR(nur.Arithmetic(), -314.57610957027, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_5) {
  s21::Model nur;
  nur.PolishNotation("10000000+98/100000-cos(90)*(sqrt(625))");
  EXPECT_NEAR(10000011.2028204, nur.Arithmetic(), ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_6) {
  s21::Model nur;
  nur.PolishNotation("log(-178)");
  EXPECT_TRUE(std::isnan(nur.Arithmetic()));
}

TEST(calculation_src_test, test_7) {
  s21::Model nur;
  nur.PolishNotation("2mod0");
  EXPECT_TRUE(std::isnan(nur.Arithmetic()));
  // nur.PrintString();
}

TEST(calculation_src_test, test_9) {
  s21::Model nur;
  nur.PolishNotation("100010001/3794*0.00034+9999999");
  double result = 10000007.962414428;
  double answer = nur.Arithmetic();
  EXPECT_NEAR(result, answer, ACCURACY);
}

TEST(calculation_src_test, test_10) {
  s21::Model nur;
  nur.PolishNotation("1.0/0.0+cos(180)-1.0/0.0");
  EXPECT_TRUE(std::isnan(nur.Arithmetic()));
}

TEST(calculation_src_test, test_11) {
  s21::Model nur;
  nur.PolishNotation("cos(180)-1.0/0.0");
  EXPECT_TRUE(std::isinf(nur.Arithmetic()));
}

TEST(calculation_src_test, test_12) {
  s21::Model nur;
  nur.PolishNotation("150-cos(180)*150/5+(-180)");
  double result = -12.046197928264263;
  double answer = nur.Arithmetic();
  EXPECT_NEAR(result, answer, ACCURACY);
}

TEST(calculation_src_test, test_13) {
  s21::Model nur;
  nur.PolishNotation("acos(100)");
  double answer = nur.Arithmetic();
  EXPECT_TRUE(std::isnan(answer));
  // nur.PrintString();
}

TEST(calculation_src_test, test_14) {
  s21::Model nur;
  nur.PolishNotation("cos(76-60)*(35mod7)-542/982");
  double answer = nur.Arithmetic();
  double result = -0.55193482688;
  EXPECT_NEAR(result, answer, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_15) {
  s21::Model nur;
  nur.PolishNotation("log(1000*ln(200*ln(1000)))");
  EXPECT_NEAR(nur.Arithmetic(), 3.85919608528, ACCURACY);
}

TEST(calculation_src_test, test_16) {
  s21::Model nur;
  nur.PolishNotation("150-cos(x)*150/5+(-x)");
  EXPECT_NEAR(nur.Arithmetic("180"), -12.046197928264263, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_17) {
  s21::Model nur;
  nur.PolishNotation("879231*(1/2)+atan(0)/(sqrt(982-237*0.34))");
  EXPECT_NEAR(nur.Arithmetic(), 439615.5, ACCURACY);
}

TEST(calculation_src_test, test_18) {
  s21::Model nur;
  nur.PolishNotation("cos(x)-x*(-5)");
  EXPECT_NEAR(5000.56237908, nur.Arithmetic("1000"), ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_19) {
  s21::Model nur;
  nur.PolishNotation("879231*(x)+atan(0)/(sqrt(982-x*0.34))");
  EXPECT_NEAR(1055077.2, nur.Arithmetic("1.2"), ACCURACY);
}

TEST(calculation_src_test, test_20) {
  s21::Model nur;
  nur.PolishNotation("acos(10)");
  EXPECT_TRUE(std::isnan(nur.Arithmetic()));
  // nur.PrintString();
}

TEST(calculation_src_test, test_21) {
  s21::Model nur;
  nur.PolishNotation("879231*(x)+atan(0)/(sqrt(982-x*0.34))");
  EXPECT_NEAR(0.0, nur.Arithmetic(), ACCURACY);
}

TEST(calculation_src_test, test_22) {
  s21::Model nur;
  nur.PolishNotation("8-cos(x^9)*7");
  EXPECT_NEAR(3.4785444, nur.Arithmetic("8"), ACCURACY);
}

TEST(calculation_src_test, test_23) {
  s21::Model nur;
  nur.PolishNotation("187/5+9*(ln(10)^3.5)");
  double answer = nur.Arithmetic();
  EXPECT_NEAR(204.1237307, answer, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_24) {
  s21::Model nur;
  nur.PolishNotation("46/3+5^2*(89+4)-sin(2)");
  double answer = nur.Arithmetic();
  EXPECT_NEAR(2339.424035906, answer, ACCURACY);
}

TEST(calculation_src_test, test_25) {
  s21::Model nur;
  nur.PolishNotation("46/3+5^2*(89+4)*sin(2)");
  double answer = nur.Arithmetic();
  EXPECT_NEAR(2129.4498507030432, answer, ACCURACY);
}

TEST(calculation_src_test, test_26) {
  s21::Model nur;
  nur.PolishNotation("987.65^(1/2)+7*tan(3/0.5)");
  double answer = nur.Arithmetic();
  EXPECT_NEAR(29.3898559, answer, ACCURACY);
}

TEST(calculation_src_test, test_27) {
  s21::Model nur;
  nur.PolishNotation("2+tan(45)/(7-90*(-4))");
  double answer = nur.Arithmetic();
  EXPECT_NEAR(2.0044135, answer, ACCURACY);
}

TEST(calculation_src_test, test_28) {
  s21::Model nur;
  nur.PolishNotation("cos(23.4+tan(23(-23)))");
  double answer = nur.Arithmetic();
  EXPECT_NEAR(-0.3047384, answer, ACCURACY);
}

TEST(calculation_src_test, test_29) {
  s21::Model nur;
  nur.PolishNotation("96mod2-98*(1/2)");
  double answer = nur.Arithmetic();
  EXPECT_NEAR(-49, answer, ACCURACY);
}

TEST(calculation_src_test, test_30) {
  s21::Model nur;
  nur.PolishNotation("96mod(x)-98*x");
  EXPECT_NEAR(9896, nur.Arithmetic("-100"), ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_31) {
  s21::Model nur;
  nur.PolishNotation("87.9/456+atan(1)-94");
  EXPECT_NEAR(-93.0218387, nur.Arithmetic(), ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_32) {
  s21::Model nur;
  EXPECT_THROW(nur.PolishNotation("cos(x)+(1-2"), std::invalid_argument);
}

TEST(calculation_src_test, test_33) {
  s21::Model nur;
  nur.PolishNotation("2^3^2");
  EXPECT_NEAR(512, nur.Arithmetic(), ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_34) {
  s21::Model nur;
  nur.PolishNotation("+1+1");
  EXPECT_NEAR(nur.Arithmetic(), 2, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_35) {
  s21::Model nur;
  nur.PolishNotation("-1+1");
  EXPECT_NEAR(nur.Arithmetic(), 0, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_36) {
  s21::Model nur;
  nur.PolishNotation("+0+");
  EXPECT_THROW(nur.Arithmetic(), std::invalid_argument);
  //  m.PrintString();
}

TEST(calculation_src_test, test_37) {
  s21::Model nur;
  EXPECT_THROW(nur.PolishNotation("((6)))"), std::invalid_argument);
  // nur.PrintString();
}

TEST(calculation_src_test, test_38) {
  s21::Model nur;
  nur.PolishNotation("5.");
  EXPECT_EQ(nur.Arithmetic(), 5);
  // nur.PrintString();
}

TEST(calculation_src_test, test_39) {
  s21::Model nur;
  EXPECT_THROW(nur.PolishNotation("tam(10)"), std::invalid_argument);
  // nur.PrintString();
}

TEST(calculation_src_test, test_40) {
  s21::Model nur;
  nur.PolishNotation("(5+2)x");
  EXPECT_EQ(nur.Arithmetic("2"), 14);
}
//
TEST(calculation_src_test, test_41) {
  s21::Model nur;
  nur.PolishNotation("(+)1");
  EXPECT_THROW(nur.Arithmetic(), std::invalid_argument);
}
//
TEST(calculation_src_test, test_42) {
  s21::Model nur;
  nur.PolishNotation("++1");
  EXPECT_THROW(nur.Arithmetic(), std::invalid_argument);
  // nur.PrintString();
}

TEST(calculation_src_test, test_43) {
  s21::Model nur;
  nur.PolishNotation("100");
  EXPECT_EQ(nur.Arithmetic(), 100);
}
//
TEST(calculation_src_test, test_44) {
  s21::Model nur;
  nur.PolishNotation(".9");
  EXPECT_EQ(nur.Arithmetic(), 0.9);
}
//
TEST(calculation_src_test, test_45) {
  s21::Model nur;
  nur.PolishNotation("9.");
  EXPECT_EQ(nur.Arithmetic(), 9);
}
//
TEST(calculation_src_test, test_46) {
  s21::Model nur;
  nur.PolishNotation("(2)(2)");
  EXPECT_EQ(nur.Arithmetic(), 4);
  // nur.PrintString();
}

TEST(calculation_src_test, test_47) {
  s21::Model nur;
  nur.PolishNotation("2sqrt(4)");
  EXPECT_EQ(nur.Arithmetic(), 4);
  // nur.PrintString();
}

TEST(calculation_src_test, test_48) {
  s21::Model nur;
  EXPECT_THROW(nur.PolishNotation("6.6.6"), std::invalid_argument);
}
//
TEST(calculation_src_test, test_49) {
  s21::Model nur;
  nur.PolishNotation("(8).5");
  EXPECT_EQ(nur.Arithmetic(), 4);
}
//
TEST(calculation_src_test, test_50) {
  s21::Model nur;
  nur.PolishNotation("sqrt-9");
  EXPECT_THROW(nur.Arithmetic(), std::invalid_argument);
  // nur.PrintString();
}

TEST(calculation_src_test, test_51) {
  s21::Model nur;
  nur.PolishNotation("5mod-9");
  EXPECT_THROW(nur.Arithmetic(), std::invalid_argument);
  // nur.PrintString();
}

TEST(calculation_src_test, test_52) {
  s21::Model nur;
  nur.PolishNotation("sinsin2");
  EXPECT_THROW(nur.Arithmetic(), std::invalid_argument);
  // nur.PrintString();
}

TEST(calculation_src_test, test_53) {
  s21::Model nur;
  nur.PolishNotation("cospsinp");
  EXPECT_NEAR(nur.Arithmetic(), 0, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_54) {
  s21::Model nur;
  EXPECT_THROW(nur.PolishNotation("sin(2 3)"), std::invalid_argument);
  // nur.PrintString();
}

TEST(calculation_src_test, test_55) {
  s21::Model nur;
  nur.PolishNotation("pp");
  EXPECT_NEAR(nur.Arithmetic(), 9.8696044, ACCURACY);
  // nur.PrintString();
}

TEST(calculation_src_test, test_56) {
  s21::Model nur;
  nur.PolishNotation("123456789123456789");
  EXPECT_EQ(nur.Arithmetic(), 123456789123456789);
  // nur.PrintString();
}

TEST(calculation_src_test, test_57) {
  s21::Model nur;
  nur.PolishNotation("2e-2");
  EXPECT_EQ(nur.Arithmetic(), 0.02);
  // nur.PrintString();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}