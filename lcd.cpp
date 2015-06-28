#include "lcd.h"
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>

lcd::lcd(QObject *parent) : QObject(parent)
{
    //新建一个QLCDNumber对象
    lcd = new QLCDNumber();
    //设置晶体管控件QLCDNumber能显示的位数
    lcd->setDigitCount(10);
    //设置显示的模式为十进制
    lcd->setMode(QLCDNumber::Dec);
    //设置显示方式
    lcd->setSegmentStyle(QLCDNumber::Flat);

    //新建一个QTimer对象
    timer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(1000);
    //启动定时器
    timer->start();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(lcd);
    //信号和槽
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    //重新设置窗口的布局管理器
    this->setLayout(layout);
    //重新设置窗口的大小
    this->resize(200, 100);
    //重新设置窗口的标题
    this->setWindowTitle("QTimerDemo");
}


void lcd::onTimerOut()
{
  //获取系统当前时间
  QTime time = QTime::currentTime();
  //设置晶体管控件QLCDNumber上显示的内容
  lcd->display(time.toString("hh:mm:ss"));
}
