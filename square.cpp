#include "square.h"
#include <QPushButton>
#include <QObject>

square::square (QWidget* parent,int r,int c):
        QObject(parent),row(r),col(c)
{
    button = new QPushButton(parent); //按鈕要給mainwindow位置 就引進parent就好
    button ->setGeometry(col*50,row*50,50,50); //每一個button的位置是col*50,row*50,後面的50是按鈕大小
    connect(button,SIGNAL(clicked()),this,SLOT(click())); //this->square
}

void square::click()
{
    emit push(row,col); //emit是發出訊號 把數字丟出去給別人知道
}


square::~square()
{

}
