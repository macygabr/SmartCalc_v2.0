QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport core

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Controller/Controller.cc \
    ../Model/BankCalc.cc \
    ../Model/Model.cc \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../Controller/Controller.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui
