#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QPushButton* arr[29] = {
      ui->pushButton,    ui->pushButton_2,  ui->pushButton_3,
      ui->pushButton_4,  ui->pushButton_5,  ui->pushButton_6,
      ui->pushButton_7,  ui->pushButton_8,  ui->pushButton_9,
      ui->pushButton_10, ui->pushButton_11, ui->pushButton_19,
      ui->pushButton_16, ui->pushButton_12, ui->pushButton_13,
      ui->pushButton_14, ui->pushButton_20, ui->pushButton_21,
      ui->pushButton_22, ui->pushButton_23, ui->pushButton_17,
      ui->pushButton_27, ui->pushButton_28, ui->pushButton_29,
      ui->pushButton_24, ui->pushButton_25, ui->pushButton_26,
      ui->pushButton_30, ui->pushButton_31};

  for (int i = 0; i < 29; i++)
    connect(arr[i], SIGNAL(clicked()), this, SLOT(function()));

  connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(CreditCalc()));
  connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(CreditCalc()));
  connect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)), this,
          SLOT(CreditCalc()));
  connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(CreditCalc()));

  ui->dateEdit_2->setDisplayFormat("dd.MM.yyyy");
  ui->dateEdit_2->setDate(QDate::currentDate());
  ui->dateEdit_3->setDisplayFormat("dd.MM.yyyy");
  ui->dateEdit_3->setDate(QDate::currentDate());
  ui->dateEdit_4->setDisplayFormat("dd.MM.yyyy");
  ui->dateEdit_4->setDate(QDate::currentDate());
  ui->radioButton->setChecked(true);
}

void MainWindow::on_pushButton_18_clicked() { ui->lineEdit->setText(""); }

void MainWindow::on_pushButton_32_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "x");
}

MainWindow::~MainWindow() { delete ui; }

//_____________________________________________________________Calc_________________________________________________________________
void MainWindow::function() {
  QPushButton* btn = qobject_cast<QPushButton*>(sender());
  ui->lineEdit->setText(ui->lineEdit->text() + btn->text());
}

void MainWindow::on_pushButton_15_clicked() {
  try {
    QString qstr1 = ui->lineEdit->text();
    QString qstr2 = ui->doubleSpinBox_6->text();
    std::string str = qstr1.toStdString();
    std::string str2 = qstr2.toStdString();
    ui->lineEdit->setText(QString::fromStdString(controller.Calc(str, str2)));
  } catch (const std::invalid_argument& oor) {
    ui->lineEdit->setText(oor.what());
  }
}

//_____________________________________________________________EndCalc_________________________________________________________________

//______________________________________________________________Graf_________________________________________________________________
void MainWindow::BuildGraf(double a, double b) {
  int N = 500;
  double ymin = 100, ymax = 100;
  QVector<double> x(N), y(N);
  double* xd = &x[0];
  double* yd = &y[0];
  try {
    controller.Graf(xd, yd, a, b, &ymax, &ymin,
                    ui->lineEdit_6->text().toStdString());
  } catch (const std::invalid_argument& oor) {
    ui->lineEdit_6->setText(oor.what());
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRange(a, b);
  ui->widget->yAxis->setRange(ymin, ymax);
  ui->widget->replot();
}

void MainWindow::on_lineEdit_6_editingFinished() {
  BuildGraf(ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value());
}

void MainWindow::on_lineEdit_editingFinished() { on_pushButton_15_clicked(); }

void MainWindow::on_doubleSpinBox_valueChanged(double arg1) {
  BuildGraf(arg1, ui->doubleSpinBox_2->value());
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg2) {
  BuildGraf(ui->doubleSpinBox->value(), arg2);
}
//______________________________________________________________EndGraf_________________________________________________________________

//_____________________________________________________________Credit_________________________________________________________________
void MainWindow::CreditCalc() {
  std::string str[3];
  double mounth = ui->spinBox_2->value();
  double percent = ui->doubleSpinBox_3->value();
  double rub = ui->spinBox->value();
  controller.CreditCalculation(rub, mounth, percent,
                               ui->radioButton->isChecked(), str);
  ui->textEdit_5->setText(QString::fromStdString(str[0]));
  ui->textEdit_8->setText(QString::fromStdString(str[1]));
  ui->textEdit_9->setText(QString::fromStdString(str[2]));
}
//_____________________________________________________________EndCredit_________________________________________________________________

//_____________________________________________________________Credit_________________________________________________________________

void MainWindow::on_pushButton_34_clicked() {
  try {
    std::string str[4];
    controller.Deposit(
        ui->spinBox_3->value(), ui->spinBox_4->value(),
        ui->doubleSpinBox_4->value(), ui->doubleSpinBox_5->value(),
        ui->dateEdit_2->date(), ui->comboBox->currentText().toStdString(),
        ui->checkBox->checkState(), ui->comboBox_3->currentText().toStdString(),
        ui->dateEdit_3->date(), ui->spinBox_6->value(),
        ui->comboBox_4->currentText().toStdString(), ui->dateEdit_4->date(),
        ui->spinBox_7->value(), str);
    ui->textEdit_3->setText(QString::fromStdString(str[0]));
    ui->textEdit_4->setText(QString::fromStdString(str[1]));
    ui->textEdit_6->setText(QString::fromStdString(str[2]));
    ui->textEdit_7->setText(QString::fromStdString(str[3]));
  } catch (const std::invalid_argument& oor) {
    ui->textEdit_3->setText(oor.what());
    ui->textEdit_4->setText(oor.what());
    ui->textEdit_6->setText(oor.what());
    ui->textEdit_7->setText(oor.what());
  }
}
//_____________________________________________________________EndCredit_________________________________________________________________
