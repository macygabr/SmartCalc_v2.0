#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QtCore/QDate>
#include <iostream>

#include "Model.h"

#define INCOME 140000

namespace s21 {
//! Класс для работы с банковскими платежами
/*!
  Методы и поля для работы с вкладами и кредитами
*/
class BankCalc {
 public:
  int sum;
  double time;
  double percent;
  double tax;
  QDate today;
  std::string period;
  bool capitalization;
  std::string addperiod;
  QDate addate;
  int sumadd;
  std::string subperiod;
  QDate subdate;
  int sumsub;

 public:
  using pair = std::pair<QDate*, int>;
  BankCalc() = default;
  ~BankCalc() = default;

  std::map<std::string, std::function<double(pair)>> map_period{
      {"Разовое", {[](pair x) { return x.second > 0 ? x.second : 1; }}},
      {"В конце срока", {[](pair x) { return x.second > 0 ? x.second : 1; }}},
      {"Каждый день", {[](pair x) { return x.second > 0 ? 1 : 1; }}},
      {"Каждую неделю", {[](pair x) { return x.second > 0 ? 7 : 1; }}},
      {"Раз в месяц", {[](pair x) {
         int res = x.first->daysInMonth();
         return x.second > 0 ? res : 1;
       }}},
      {"Раз в квартал", {[](pair x) {
         int res = 0;
         for (int i = 0; i < 3; i++, res += x.first->daysInMonth())
           ;
         return x.second > 0 ? res : 1;
       }}},
      {"Раз в полгода", {[](pair x) {
         int res = 0;
         for (int i = 0; i < 6; i++, res += x.first->daysInMonth())
           ;
         return x.second > 0 ? res : 1;
       }}},
      {"Раз в год", {[](pair x) {
         return x.second > 0 ? x.first->daysInYear() : 1;
       }}}}; /*!< Список для расчета количества дней, относительно выбора
                пользователя */

 public:
  int DebetArifmetic(double* arr1, double* arr2, double* arr3,
                     double* arr4); /*!< Функция расчета вклада */
  double ProcentAccrual(
      int* sum, double percent, int days,
      bool capitalization); /*!< Расчет начисленых процентов */
  double BalanceChange(double arr, bool capitalization, int sumadd,
                       int sumsub); /*!< Функция расчета изменения баланса */
  double Pay(double arr, bool capitalization); /*!< Расчет выплат */

  void AddSum(QDate addate, int* sum, int* sumadd, int days,
              std::string addperiod, QDate* adddate,
              int time); /*!< Функция, учитывающая дополнительные пополнения */
  void SubSum(QDate addate, int* sum, int* sumadd, int days,
              std::string addperiod, QDate* adddate,
              int time); /*!< Функция, учитывающая снятия */
};

}  // namespace s21
#endif
