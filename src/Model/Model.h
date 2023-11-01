#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <list>
#include <map>

#define ACCURACY 1e-6
#define MAXMONTH 12

namespace s21 {
//! Арифметический класс
/*!
  Класс для работы со строкой и арифметическими преобразоаниями
*/
class Model {
 public:
  using pair = std::pair<double, double>;
  using string = std::string;
  long double data; /*!< Результат арифметических преобразований как число */
  std::string
      str_data; /*!< Результат арифметических преобразований как строка */
  std::list<std::string> polish; /*!< Польская нотация из полученой строки */
  std::string content; /*!< Полученая строка */
  std::map<std::string, std::pair<std::function<double(pair)>, int>> operators{
      {"+", {[](pair x) { return x.first + x.second; }, 2}},
      {"-", {[](pair x) { return x.first - x.second; }, 2}},
      {"*", {[](pair x) { return x.first * x.second; }, 3}},
      {"/", {[](pair x) { return x.first / x.second; }, 3}},
      {"mod", {[](pair x) { return fmod(x.first, x.second); }, 3}},
      {"^", {[](pair x) { return pow(x.first, x.second); }, 4}},
      {"sin", {[](pair x) { return sin(x.second); }, 5}},
      {"cos", {[](pair x) { return cos(x.second); }, 5}},
      {"tan", {[](pair x) { return tan(x.second); }, 5}},
      {"asin", {[](pair x) { return asin(x.second); }, 5}},
      {"acos", {[](pair x) { return acos(x.second); }, 5}},
      {"atan", {[](pair x) { return atan(x.second); }, 5}},
      {"sqrt", {[](pair x) { return sqrt(x.second); }, 5}},
      {"ln", {[](pair x) { return log(x.second); }, 5}},
      {"log", {[](pair x) { return log10(x.second); }, 5}},
  }; /*!< Список функций и возможных лексем */

 public:
  Model() : data(), str_data{}, polish{}, content{} {};
  ~Model() = default;

 public:
  double Arithmetic(std::string str_x = "0"); /*!< Функция расчета выражения */
  void PolishNotation(
      std::string content); /*!< Функция преобразования в польскую нотацию */
  void BuildGraf(
      double* x, double* y, double a, double b, double* ymax,
      double* ymin); /*!< Функция расчета координат точек текущего выражения */
  std::string Round(double x); /*!< Округление чисел */
  std::string RoundStr();      /*!< Округление строк */
  int CreditAnnuity(double* arr1, double* arr2, double* arr3, double sum,
                    double time, double proc,
                    bool annuity); /*!< Функция расчета кредита */

 private:
  int IsOperator(int i);
  bool IsDigit(char c);
  void AddOperations();
  void PrintString();
  bool isError();
  bool CheckCorrectData();
  void PushConstant(int* i);
  void PushDigit(int* i);
  void PushOperator(int* i, std::list<std::string>* stek);
  void PushBracket(int i, std::list<std::string>* stek);
  void PushStek(std::list<std::string>* stek);
  void OperatorsInput(std::list<double>* arr,
                      std::list<std::string>::iterator it);
  void NumbersInput(std::list<double>* arr, std::list<std::string>::iterator it,
                    double x);

  void ScientificNotation(int i);
  void ZerroAdd(int i);
  void xAdd(int i);
  void MultAdd(int i);
};

}  // namespace s21
#endif
