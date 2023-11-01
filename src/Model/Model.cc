#include "Model.h"

#include <iomanip>  //setprecision(12)

namespace s21 {
//_____________________________________________________________Calc_________________________________________________________________

void Model::PolishNotation(std::string str) {
  content = str;
  std::list<std::string> stek;
  if (CheckCorrectData()) return;
  AddOperations();
  for (int i = 0; i < int(content.size()) && i < 255; i++) {
    PushConstant(&i);
    PushDigit(&i);
    if (content[i] == '(') stek.push_back("(");
    PushOperator(&i, &stek);
    PushBracket(i, &stek);
  }
  PushStek(&stek);
}

double Model::Arithmetic(std::string str_x) {
  double x = std::stod(str_x);
  if (polish.empty()) throw std::invalid_argument("String is empty");
  std::list<double> arr;
  for (auto it = polish.begin(); it != polish.end(); it++)
    if (operators.count(*it))
      OperatorsInput(&arr, it);
    else
      NumbersInput(&arr, it, x);
  if (arr.size() == 1)
    data = *arr.begin();
  else
    throw std::invalid_argument("Invalid Syntax");
  RoundStr();
  return data;
}

//_____________________________________________________________EndCalc_________________________________________________________________
int Model::CreditAnnuity(double* arr1, double* arr2, double* arr3, double rub,
                         double mounth, double perc, bool annuity) {
  if ((rub) == 0.0 || mounth == 0) return 0;
  double res = 0;
  double per = 0;
  double base = (rub / mounth);
  double copyrub = rub;
  perc = (perc / MAXMONTH) / 100.0;
  res = rub * (perc + (perc / (pow((1 + perc), mounth) - 1)));
  for (int i = 0; i < mounth; i++) {
    if (!annuity) res = base + perc * (rub);
    arr1[i] = res;
    if (annuity)
      arr2[i] = perc * copyrub;
    else
      arr2[i] = perc * rub;
    copyrub -= arr1[i] - arr2[i];
    arr3[i] = copyrub;
    if (!annuity) {
      rub -= base;
      per += perc * (rub);
    }
  }
  return mounth;
}
//______________________________________________________________Graf_________________________________________________________________

void Model::BuildGraf(double* x, double* y, double a, double b, double* ymax,
                      double* ymin) {
  if (a >= b) return;
  int N = 500;
  double h = (b - a) / N;
  double X = a;
  for (int i = 0; i < N; X += h, i++) {
    x[i] = X;
    y[i] = Arithmetic(std::to_string(X));
    if (!std::isnan(y[i]) && !std::isinf(y[i])) {
      *ymin = y[i];
      *ymax = y[i];
    }
  }
  for (int j = 0; j < N; j++) {
    if (*ymax < y[j] && !std::isnan(y[j]) && !std::isinf(y[j])) *ymax = y[j];
    if (*ymin > y[j] && !std::isnan(y[j]) && !std::isinf(y[j])) *ymin = y[j];
  }
}
//______________________________________________________________EndGraf_________________________________________________________________

// ____________________________________________________________Support______________________________________________________________________________

void Model::PushConstant(int* i) {
  if (content[*i] == 'x') {
    polish.push_back("x");
    (*i)++;
  }
  if (content[*i] == 'p') {
    polish.push_back("p");
    (*i)++;
  }
}

void Model::PushDigit(int* i) {
  if (IsDigit(content[*i])) {
    std::string str;
    int dot = 0;
    for (; IsDigit(content[*i]); (*i)++) {
      if (content[*i] == '.') dot++;
      str.push_back(content[*i]);
    }
    if (dot > 1) throw std::invalid_argument("Invalid Syntax");
    polish.push_back(str);
  }
}

void Model::PushOperator(int* i, std::list<std::string>* stek) {
  int res = IsOperator(*i);
  if (res) {
    std::string oper;
    for (int j = 0; j < res; j++) oper.push_back(content[(*i)++]);
    (*i)--;
    while (!stek->empty() && stek->back() != "(" &&
           operators[stek->back()].second >= operators[oper].second) {
      if (oper == "^" && stek->back() == "^") break;
      polish.push_back(stek->back());
      stek->erase(--stek->end());
    }
    stek->push_back(oper);
  }
}

void Model::PushBracket(int i, std::list<std::string>* stek) {
  if (content[i] == ')') {
    if (content[i - 1] == '(') throw std::invalid_argument("Invalid Syntax");
    while (!stek->empty() && stek->back() != "(") {
      polish.push_back(stek->back());
      stek->pop_back();
    }
    if (!stek->empty())
      stek->pop_back();
    else
      throw std::invalid_argument("Invalid Syntax");
  }
}

void Model::PushStek(std::list<std::string>* stek) {
  while (stek->size()) {
    if (stek->back() == "(") throw std::invalid_argument("Invalid Syntax");
    polish.push_back(stek->back());
    if (stek->size()) stek->erase(--stek->end());
  }
}

bool Model::IsDigit(char c) {
  return (isdigit(c) || c == '.' || c == 'x' || c == 'p');
}

int Model::IsOperator(int i) {
  char err[6] = {'(', ')', '\0'};
  for (int j = 0; j < 6; j++)
    if (content[i] == err[j] || IsDigit(content[i])) return 0;
  std::string func[15] = {"sin",  "cos",  "tan", "asin", "acos",
                          "atan", "sqrt", "ln",  "log",  "mod",
                          "+",    "-",    "*",   "/",    "^"};

  for (int j = 0; j < 15; j++)
    if (!func[j].compare(0, func[j].length(), content, i, func[j].length()))
      return func[j].length();

  throw std::invalid_argument("Unknown symbol");
}

void Model::AddOperations() {
  for (int i = 0; i < int(content.length()); i++) {
    ScientificNotation(i);
    ZerroAdd(i);
    xAdd(i);
    MultAdd(i);
  }
}

void Model::MultAdd(int i) {
  if (content[i] == '(' && i > 0 &&
      (IsDigit(content[i - 1]) || content[i - 1] == ')'))
    content.insert(i, "*");
  if (content[i] == ')' && i > 0 && IsDigit(content[i + 1]))
    content.insert(i + 1, "*");
  if (i > 0 && (IsDigit(content[i - 1]) || content[i - 1] == ')') &&
      (IsOperator(i) > 1) && content.compare(i, 3, "mod"))
    content.insert(i, "*");
}

void Model::xAdd(int i) {
  if ((content[i] == 'x' || content[i] == 'p') && i > 0 &&
      (content[i - 1] == ')' || IsDigit(content[i - 1])))
    content.insert(i, "*");
  if ((content[i] == 'x' || content[i] == 'p') &&
      (content[i + 1] == '(' || IsDigit(content[i + 1])))
    content.insert(i + 1, "*");
}

void Model::ZerroAdd(int i) {
  if ((content[i] == '-' || content[i] == '+') &&
      ((i > 0 && content[i - 1] == '(') || i == 0) && content[i + 1] != ')')
    content.insert(i, "0");
}

void Model::ScientificNotation(int i) {
  if ((content[i] == 'e' || content[i] == 'E') &&
      (IsDigit(content[i + 1]) || content[i + 1] == '-' ||
       content[i + 1] == '+')) {
    int j = i + 1;
    for (; IsDigit(content[++j]);)
      ;
    content.insert(j, ")");
    content.replace(i, 1, "*");
    content.insert(i + 1, "10^(");
  }
}

bool Model::CheckCorrectData() {
  if (content.empty() || isError()) return true;
  polish.clear();
  str_data.clear();
  data = 0;
  return false;
}

bool Model::isError() {
  return content == "Invalid Syntax" || content == "String is empty" ||
         content == "Unknown symbol" || content == "inf" || content == "nan" ||
         content == "stod: no conversion";
}

void Model::PrintString() {
  std::cout << "\033[31mcontent: " << content << std::endl;
  std::cout << "polish: ";
  for (std::string c : polish) std::cout << c << " ";
  std::cout << std::endl << "data: ";
  std::cout << std::fixed << std::setprecision(12) << data << std::endl
            << "\033[0m";
};

void Model::OperatorsInput(std::list<double>* arr,
                           std::list<std::string>::iterator it) {
  std::list<double>::iterator it_second = (--arr->end());
  std::list<double>::iterator it_first = it_second;
  std::pair<double, double> x = {*it_first, *it_second};
  if (operators[*it].second == 5) {
    arr->push_back(operators[*it].first(x));
    if (it_second != arr->end())
      arr->erase(it_second);
    else
      throw std::invalid_argument("Invalid Syntax");
  } else {
    if (arr->begin() == it_second)
      throw std::invalid_argument("Invalid Syntax");
    x = {*(--it_first), *it_second};
    arr->push_back(operators[*it].first(x));
    arr->erase(it_first);
    arr->erase(it_second);
  }
}

void Model::NumbersInput(std::list<double>* arr,
                         std::list<std::string>::iterator it, double x) {
  if (*it == "x")
    arr->push_back(x);
  else if (*it == "p")
    arr->push_back(M_PI);
  else
    arr->push_back(std::stod(*it));
}

std::string Model::RoundStr() {
  str_data = std::to_string(data);
  for (int i = int(str_data.length()) - 1; str_data[i--] == '0';)
    str_data.pop_back();
  if (str_data.back() == '.') str_data.pop_back();
  return str_data;
}

std::string Model::Round(double x) {
  x = std::round(x * 100) / 100;
  std::string str = std::to_string(x);
  for (int i = 0; i < 4; i++) str.pop_back();
  return str;
}
}  // namespace s21
