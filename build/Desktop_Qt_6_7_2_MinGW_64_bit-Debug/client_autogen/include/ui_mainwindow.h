/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *findBtn;
    QComboBox *typeComboBox;
    QTableWidget *tableWidget;
    QPushButton *folderBtn;
    QLineEdit *dirEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(575, 550);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        findBtn = new QPushButton(centralwidget);
        findBtn->setObjectName("findBtn");
        findBtn->setGeometry(QRect(180, 440, 221, 41));
        typeComboBox = new QComboBox(centralwidget);
        typeComboBox->setObjectName("typeComboBox");
        typeComboBox->setGeometry(QRect(40, 330, 91, 30));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(40, 10, 511, 301));
        folderBtn = new QPushButton(centralwidget);
        folderBtn->setObjectName("folderBtn");
        folderBtn->setGeometry(QRect(510, 330, 41, 29));
        dirEdit = new QLineEdit(centralwidget);
        dirEdit->setObjectName("dirEdit");
        dirEdit->setGeometry(QRect(140, 330, 361, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 575, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        findBtn->setText(QCoreApplication::translate("MainWindow", "\320\227\320\275\320\260\320\271\321\202\320\270", nullptr));
        folderBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
