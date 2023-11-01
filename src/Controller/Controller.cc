#include "Controller.h"

namespace s21 {
std::string Controller::Calc(std::string content, std::string x) {
  model.PolishNotation(content);
  model.Arithmetic(x);
  return model.str_data;
};

void Controller::Graf(double* x, double* y, double a, double b, double* ymax,
                      double* ymin, std::string content) {
  model.PolishNotation(content);
  model.BuildGraf(x, y, a, b, ymax, ymin);
};

std::string* Controller::CreditCalculation(double sum, double time,
                                           double percent, bool annuity,
                                           std::string* str) {
  if (!time || !percent) return str;
  double arr1[int(round(time))];
  double arr2[int(round(time))];
  double arr3[int(round(time))];
  int ln = model.CreditAnnuity(arr1, arr2, arr3, sum, time, percent, annuity);
  for (int i = 0; i < ln; i++) {
    str[0] += "\t" + model.Round(arr1[i]) + "\n";
    str[1] += "\t" + model.Round(arr2[i]) + "\n";
    str[2] += "\t" + model.Round(arr3[i]) + "\n";
  }
  return str;
}

void Controller::Deposit(int sum, int time, double percent, double tax,
                         QDate today, std::string period, bool capitalization,
                         std::string addperiod, QDate addate, int sumadd,
                         std::string subperiod, QDate subdate, int sumsub,
                         std::string* str) {
  if (!time || !percent) return;
  bank.sum = sum;
  bank.time = time;
  bank.percent = percent;
  bank.tax = tax;
  bank.today = today;
  bank.period = period;
  bank.capitalization = capitalization;
  bank.addperiod = addperiod;
  bank.addate = addate;
  bank.sumadd = sumadd;
  bank.subperiod = subperiod;
  bank.subdate = subdate;
  bank.sumsub = sumsub;
  double arr1[20000];
  double arr2[20000];
  double arr3[20000];
  double arr4[20000];
  int ln = bank.DebetArifmetic(arr1, arr2, arr3, arr4);
  for (int i = 0; i < ln - 1; i++) {
    str[0] += model.Round(arr1[i]) + "\n";
    str[1] += model.Round(arr2[i]) + "\n";
    str[2] += model.Round(arr3[i]) + "\n";
    str[3] += model.Round(arr4[i]) + "\n";
  }
  str[0] += "Всего процентов: " + model.Round(arr1[ln]) + "\n";
  str[1] += model.Round(arr2[ln]) + "\n";
  str[2] += "Выплачено: " + model.Round(arr3[ln]) + "\n";
  str[3] += "Налог: " + model.Round(arr4[ln]) + "\n";
}

}  // namespace s21
