#ifndef SQUARE_H
#define SQUARE_H
#include <QPushButton>
#include <QObject>
#include <time.h>

class square : public QObject
{
    Q_OBJECT
public:
    explicit square(QWidget *parent,int r,int c); //QWidget *parent讓他知道媽媽是mainwindow
    ~square();
    QPushButton* button;
    const int row; //位置的屬性 設定位置
    const int col;
    int number;

public slots: //定義可以給別人使用的slot的function
    void click();

signals:
    void push(int r,int c); //宣告說要傳兩個參數


};

#endif // SQUARE_H
