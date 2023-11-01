#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtCore/QDate>

#include "../Model/BankCalc.h"
#include "../Model/Model.h"

namespace s21 {
//! Класс контроллер
/*!
  Используется для связи интерфейса и системы
*/
class Controller {
 public:
  Model model;   /*!< Арифметический класс   */
  BankCalc bank; /*!< Класс для работы с банковскими платежами */

 public:
  Controller() : model(), bank(){};
  ~Controller() = default;

 public:
  std::string Calc(
      std::string content,
      std::string x = "0"); /*!< Функция считывания строки и ее расчета */
  void Graf(double* x, double* y, double a, double b, double* ymax,
            double* ymin, std::string content); /*!< Функция расчета координат
                                                   точек текущего выражения*/
  std::string* CreditCalculation(double sum, double time, double percent,
                                 bool annuity,
                                 std::string* str); /*!< Расчет кредита */
  void Deposit(int sum, int time, double percent, double tax, QDate today,
               std::string period, bool capitalization, std::string addperiod,
               QDate adddate, int sumadd, std::string subperiod, QDate subdate,
               int sumsub, std::string* str); /*!< Расчет депозита */
};
}  // namespace s21
#endif
