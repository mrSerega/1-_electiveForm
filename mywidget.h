#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QFrame>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QTableWidget>
#include <QButtonGroup>
#include <QTimer>
#include <QPushButton>
#include <QRadioButton>
#include <QApplication>
#include <iostream>

#include "paintwidget.h"

const int tasksCount = 2;

const std::string subTaskName[tasksCount] = {"calc matrix", "paint graph"};

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    double omega;

    QVBoxLayout *mainVLay;
    QLabel *mainLabel;

    QGroupBox *gbTaskSelect;
    QButtonGroup *rbgTasks;
    QGridLayout *taskSelectLay;
    QRadioButton *rbTask[tasksCount];

    QFrame *inputDataFrame;
    QGridLayout *inputLay;
    QLabel *inputMainText, *lInData, *lInMatrix;
    QLineEdit *leInData;
    QPlainTextEdit *inMatrixData;
    QPushButton *inputButton, *cancelButton;

    QFrame *calcMatrixFrame;
    QGridLayout *calcMatrixLay;
    QLabel *lRes1, *lRes2, *lResTotal;
    QLineEdit *leRes1;
    QTextBrowser *leRes2, *leResTotal;
    QTableWidget *tableRes2, *tableTotal;

    PaintWidget *graphFrame;

    void calculateFunction(const int);
    void calculateMatrix(double [][3]);
    QString matrixToOut(double [][3]);

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onInputButtonClicked();
    void onCancelButtonClicked();
    void onSubTaskChanged(int);
};

#endif // MYWIDGET_H
