#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QObject>
#include "square.h"
#include <time.h>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void start();
    void picture(int r,int c);
    bool flag;
    void check_L();
    void check_five();
    void check_four();
    void check_three();
    bool is_three();
    void go_down();
    void star();
    void clear_ver();
    void clear_hol();
    void boom();
    void check_three_no_score();
    void coo();
    void end_game();
    int score;
    int step;


public slots:
    void button_click(int r,int c);

private slots:


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    square *arr[10][10];
    int rr;
    int cc;
    int rr2=0;
    int cc2=0;
};

#endif // MAINWINDOW_H
