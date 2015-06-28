#ifndef LCD_H
#define LCD_H

#include <QObject>

class QLCDNumber;
class QTimer;
class lcd : public QObject
{
  Q_OBJECT
public:
  explicit lcd(QWidget *parent = 0);

signals:

public slots:

  void onTimerOut();
private:

  QLCDNumber *lcd;
  QTimer *timer;

#endif // LCD_H
