#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Rows.h"
#include <QWidget>
#include <QtGui>
#include <string>
#include <cmath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    int r, k, a, i;
    double b;
    bool c;
    QString str1, str3;
    Row<double>* ri;
    Knot<double>* ki;
    void createRows(int r);
    void createKnots(int k);
    ~MainWindow();

private slots:

    void doSlot();
    void cancel();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
