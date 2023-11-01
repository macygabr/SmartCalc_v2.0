#include <gtest/gtest.h>

#include "../Model/Model.h"

TEST(first, convert_1) {
  s21::Model Nurlan;
  std::string str = "1+5.5*2+3";
  std::list<std::string> origin = {"1", "5.5", "2", "*", "+", "3", "+"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_2) {
  s21::Model Nurlan;
  std::string str = "4*5+3-4/2*6";
  std::list<std::string> origin = {"4", "5", "*", "3", "+", "4",
                                   "2", "/", "6", "*", "-"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_3) {
  s21::Model Nurlan;
  std::string str = "2+(2+3/4-(4-3)-2)-1";
  std::list<std::string> origin = {"2", "2", "3", "4", "/", "+", "4", "3",
                                   "-", "-", "2", "-", "+", "1", "-"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_4) {
  s21::Model Nurlan;
  std::string str = "12+3mod2";
  std::list<std::string> origin = {"12", "3", "2", "mod", "+"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_5) {
  s21::Model Nurlan;
  std::string str = "2^4+3*(6-5*4)+(1-2)";
  std::list<std::string> origin = {"2", "4", "^", "3", "6", "5", "4", "*",
                                   "-", "*", "+", "1", "2", "-", "+"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_6) {
  s21::Model Nurlan;
  std::string str = "(-2)+(-2)";
  std::list<std::string> origin = {"0", "2", "-", "0", "2", "-", "+"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_7) {
  s21::Model Nurlan;
  std::string str = "sin(4*3)+2-cos(4-2)";
  std::list<std::string> origin = {"4", "3", "*", "sin", "2", "+",
                                   "4", "2", "-", "cos", "-"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_8) {
  s21::Model Nurlan;
  std::string str = "sqrt(tan(19))-cos(5+5^2)/ln(sin(3))";
  std::list<std::string> origin = {"19", "tan", "sqrt", "5",   "5",  "2", "^",
                                   "+",  "cos", "3",    "sin", "ln", "/", "-"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_9) {
  s21::Model Nurlan;
  std::string str = "12.345+654.3*4^3.4";
  std::list<std::string> origin = {"12.345", "654.3", "4", "3.4",
                                   "^",      "*",     "+"};
  Nurlan.PolishNotation(str);
  ASSERT_EQ(Nurlan.polish, origin);
}

TEST(test, convert_10) {
  s21::Model Nurlan;
  std::string str = "1x-(-2)cos5";
  std::list<std::string> origin = {"1", "x", "*",   "0", "2",
                                   "-", "5", "cos", "*", "-"};
  Nurlan.PolishNotation(str);
  Nurlan.Arithmetic("4");
  EXPECT_NEAR(Nurlan.data, 4.56732437093, ACCURACY);
  ASSERT_EQ(Nurlan.polish, origin);
  // Nurlan.PrintString();
}
