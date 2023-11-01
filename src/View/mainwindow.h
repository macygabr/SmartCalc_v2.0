#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qcustomplot.h>

#include <QDate>
#include <QMainWindow>

#include "../Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  s21::Controller controller;
  Ui::MainWindow *ui;

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void function();
  void on_pushButton_18_clicked();
  void on_pushButton_15_clicked();
  void on_pushButton_32_clicked();
  void BuildGraf(double arg1, double arg2);
  void CreditCalc();
  void on_doubleSpinBox_valueChanged(double arg1);
  void on_doubleSpinBox_2_valueChanged(double arg1);
  void on_lineEdit_6_editingFinished();
  void on_pushButton_34_clicked();
  void on_lineEdit_editingFinished();
};
#endif  // MAINWINDOW_H
