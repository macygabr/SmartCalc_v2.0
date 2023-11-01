#include "BankCalc.h"

namespace s21 {
//_____________________________________________________________Credit_________________________________________________________________

int BankCalc::DebetArifmetic(double* arr1, double* arr2, double* arr3,
                             double* arr4) {
  QDate copy_date = today;
  if (addate < today || (today.addDays(time)) < addate)
    throw std::invalid_argument("Invalid Syntax");
  today = copy_date;
  QDate end_peroid = today.addYears(1);
  today = copy_date;
  percent = percent / 100.0 / today.daysInYear();
  tax /= 100;
  int i = 0;
  int days = 0;
  int copy_time = time;
  double allProcent = 0;
  double allBalanceChange = 0;
  double allPay = 0;
  double allTax = 0;
  for (i = 0; sum > 0 && copy_time > 0; i++, copy_time -= days) {
    days = map_period[period](pair(&copy_date, copy_time));
    if (copy_time - days <= 0) days = copy_time;
    AddSum(copy_date, &sum, &sumadd, days, addperiod, &addate, time);
    SubSum(copy_date, &sum, &sumsub, days, subperiod, &subdate, time);
    arr1[i] = ProcentAccrual(&sum, percent, days, capitalization);
    arr2[i] = BalanceChange(arr1[i], capitalization, sumadd, sumsub);
    arr3[i] = Pay(arr1[i], capitalization);
    arr4[i] = sum;
    copy_date = copy_date.addDays(days);
    allProcent += arr1[i];
    allBalanceChange += arr2[i];
    allPay += arr3[i];
    if (allProcent > INCOME && copy_date < end_peroid)
      allTax += allProcent * tax;
    else
      allTax = 0;
  }
  arr1[++i] = allProcent;
  arr2[i] = allBalanceChange;
  arr3[i] = allPay;
  arr4[i] = allTax;
  return i;
}

void BankCalc::AddSum(QDate today, int* sum, int* sumadd, int days,
                      std::string addperiod, QDate* addate, int time) {
  if (!(*sumadd)) return;
  int date = addate->dayOfYear();
  while (today.dayOfYear() <= date && date < (today.dayOfYear() + days)) {
    *sum += *sumadd;
    int interval = map_period[addperiod](pair(addate, time));
    date += interval;
    *addate = addate->addDays(interval);
    std::cout << today.dayOfYear() << " < " << date << " < "
              << today.dayOfYear() + days << std::endl;
  }
}

void BankCalc::SubSum(QDate today, int* sum, int* sumsub, int days,
                      std::string subperiod, QDate* subdate, int time) {
  if (!(*sumsub)) return;
  int date = subdate->dayOfYear();
  while (today.dayOfYear() <= date && date < (today.dayOfYear() + days)) {
    *sum -= *sumsub;
    int interval = map_period[subperiod](pair(subdate, time));
    date += interval;
    *subdate = subdate->addDays(interval);
    std::cout << today.dayOfYear() << " < " << date << " < "
              << today.dayOfYear() + days << std::endl;
  }
}

double BankCalc::ProcentAccrual(int* sum, double percent, int days,
                                bool capitalization) {
  double res = 0;
  res = (*sum) * (percent)*days;
  if (capitalization) *sum += res;
  return res;
}

double BankCalc::BalanceChange(double arr, bool capitalization, int sumadd,
                               int sumsub) {
  double res = 0;
  if (capitalization) res += arr;
  return res;
}
double BankCalc::Pay(double arr, bool capitalization) {
  if (!capitalization) return arr;
  return 0;
}

//_____________________________________________________________EndCredit_________________________________________________________________
}  // namespace s21
