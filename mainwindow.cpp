#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <time.h>
#include <QIcon>
#include <QLCDNumber>
#include <QMessageBox>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),rr(0),cc(0),score(0),step(4),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    for (int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            arr[i][j]=new square (this,i,j);
            connect(arr[i][j],SIGNAL(push(int,int)),this,SLOT(button_click(int,int))); //this->mainwindow
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::button_click(int r, int c) //判斷按鈕交換
{

    if(!flag) //第一次點下去 (if flag is false)
    {
         flag=true;
         rr=r;//紀錄
         cc=c;
     }
    else //第二次點了
    {
        ui->lcdNumber->display(score);
        ui->lcdNumber_2->display(step);
        if((rr==r-1 && cc==c) || (rr==r+1 && cc==c)) //rr要和r交換
        {
            int temp = arr[r][c]->number;
            arr[r][c]->number = arr[rr][c]->number; picture(r,c);
            arr[rr][c]->number = temp; picture(rr,c);
            step--;//算步數
            if(!is_three())//換回來
            {
                int temp = arr[r][c]->number;
                arr[r][c]->number = arr[rr][c]->number; picture(r,c);
                arr[rr][c]->number = temp; picture(rr,c);
                step++;
            }
        }
        else if((rr==r && c==cc-1) || (rr==r && c==cc+1)) //cc要和c交換
        {
            int temp = arr[r][c]->number;
            arr[r][c]->number = arr[r][cc]->number;picture(r,c);
            arr[r][cc]->number = temp;picture(r,cc);
            step--;
            if(!is_three())
            {
                int temp = arr[r][c]->number;
                arr[r][c]->number = arr[r][cc]->number;picture(r,c);
                arr[r][cc]->number = temp;picture(r,cc);
                step++;
            }

        }

        rr2=r;//第二下的
        cc2=c;

        star();
        clear_hol();
        clear_ver();
        boom();
        check_L();
        check_five();
        check_four();
        check_three();

        go_down();
        coo();
        end_game();
        ui->lcdNumber->display(score);
        ui->lcdNumber_2->display(step);
        flag=false;
    }
}


void MainWindow::start()
{
    int m;
    srand((unsigned)time(NULL));

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {   m = rand() % 4;
            arr[i][j]->number=m+1; //1234代表圖案
            picture(i,j); //插入圖片
        }
    }

    while(is_three())
    {
        check_three_no_score();
        go_down();
    }

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
           picture(i,j);
        }
    }
    flag=false; //還沒按兩次不用交換
    score=0;
    ui->lcdNumber->display(score);
    ui->lcdNumber_2->display(step);
}

void MainWindow::picture(int r,int c)
{

    switch(arr[r][c]->number){
       case 1:
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/1")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 2:
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/2")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 3:
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/3")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 4:
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/4")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 31: //紫炸彈
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/31")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 32: //綠炸彈
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/32")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 33: //黃炸彈
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/33")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 34: //紅炸彈
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/34")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 40: //星星
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/40")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 21: //橫紫條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/21")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 22: //橫綠條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/22")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 23: //橫黃條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/23")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 24: //橫紅條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/24")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 51: //直紫條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/51")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 52: //直綠條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/52")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 53: //直黃條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/53")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       case 54: //直紅條紋
           arr[r][c]->button->setIcon(QIcon(QPixmap(":/new/prefix1/54")));
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
       default:
           arr[r][c]->button->setIcon(QIcon(QPixmap(" ")));//圖形空掉的狀態
           arr[r][c]->button->setIconSize(arr[r][c]->button->size());
           break;
    }
}

void MainWindow::check_L()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(arr[i][j]->number==arr[i][j+1]->number && arr[i][j]->number==arr[i][j+2]->number)
            {
                if(arr[i][j]->number==arr[i+1][j]->number && arr[i][j]->number==arr[i+2][j]->number)//角在左上
                {
                    score=score+10;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i][j]->number=0;  picture(i,j);
                    arr[i+1][j]->number=0;  picture(i+1,j);
                    switch(arr[i+2][j]->number)
                    {
                     case 1:
                           arr[i+2][j]->number=31;  picture(i+2,j);
                        break;
                     case 2:
                           arr[i+2][j]->number=32;  picture(i+2,j);
                        break;
                     case 3:
                           arr[i+2][j]->number=33;  picture(i+2,j);
                        break;
                     case 4:
                           arr[i+2][j]->number=34;  picture(i+2,j);
                        break;
                    }
                }

                if(arr[i][j+2]->number==arr[i+1][j+2]->number && arr[i][j+2]->number==arr[i+2][j+2]->number)//角在右上
                {
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j]->number=0; picture(i,j);
                    arr[i+1][j+2]->number=0;  picture(i+1,j+2);
                    arr[i][j+2]->number=0;  picture(i+2,j+2);
                    switch(arr[i+2][j+2]->number)
                    {
                     case 1:
                           arr[i+2][j+2]->number=31;  picture(i+2,j+2);
                        break;
                     case 2:
                           arr[i+2][j+2]->number=32;  picture(i+2,j+2);
                        break;
                     case 3:
                           arr[i+2][j+2]->number=33;  picture(i+2,j+2);
                        break;
                     case 4:
                           arr[i+2][j+2]->number=34;  picture(i+2,j+2);
                        break;
                    }

                }
            }
        }
    }

    for(int i=9;i>1;i--)
    {
        for(int j=0;j<8;j++)
        {
            if(arr[i][j]->number==arr[i][j+1]->number && arr[i][j+1]->number==arr[i][j+2]->number)
            {
                if(arr[i][j]->number==arr[i-1][j]->number && arr[i][j]->number==arr[i-2][j]->number)//角在左下
                {   score=score+10;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i-1][j]->number=0;  picture(i-1,j);
                    arr[i-2][j]->number=0;  picture(i-2,j);
                    switch(arr[i][j]->number)
                    {
                     case 1:
                           arr[i][j]->number=31;  picture(i,j);
                        break;
                     case 2:
                           arr[i][j]->number=32;  picture(i,j);
                        break;
                     case 3:
                           arr[i][j]->number=33;  picture(i,j);
                        break;
                     case 4:
                           arr[i][j]->number=34;  picture(i,j);
                        break;
                    }

                }
                if(arr[i][j+2]->number==arr[i-1][j+2]->number && arr[i][j+2]->number==arr[i-2][j+2]->number)//角在右下
                {
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j]->number=0; picture(i,j);
                    arr[i-1][j+2]->number=0;  picture(i-1,j+2);
                    arr[i-2][j+2]->number=0;  picture(i-2,j+2);
                    switch(arr[i][j+2]->number)
                    {
                     case 1:
                           arr[i][j+2]->number=31;  picture(i,j+2);
                        break;
                     case 2:
                           arr[i][j+2]->number=32;  picture(i,j+2);
                        break;
                     case 3:
                           arr[i][j+2]->number=33;  picture(i,j+2);
                        break;
                     case 4:
                           arr[i][j+2]->number=34;  picture(i,j+2);
                        break;
                    }
                }
            }
        }
    }
}

void MainWindow::check_five()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(arr[i][j]->number==arr[i][j+1]->number && arr[i][j]->number==arr[i][j+2]->number && arr[i][j]->number==arr[i][j+3]->number && arr[i][j]->number==arr[i][j+4]->number)
            {//橫的
                score=score+20;
                arr[i][j]->number=0;  picture(i,j);
                arr[i][j+1]->number=0; picture(i,j+1);
                arr[i][j+3]->number=0;  picture(i,j+3);
                arr[i][j+4]->number=0;  picture(i,j+4);
                arr[i][j+2]->number=40; picture(i,j+2);
            }
        }
    }
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(arr[i][j]->number==arr[i+1][j]->number && arr[i][j]->number==arr[i+2][j]->number && arr[i][j]->number==arr[i+3][j]->number && arr[i][j]->number==arr[i+4][j]->number)
            {//直的
                score=score+20;
                arr[i][j]->number=0;  picture(i,j);
                arr[i+1][j]->number=0; picture(i+1,j);
                arr[i+3][j]->number=0;  picture(i+3,j);
                arr[i+4][j]->number=0;  picture(i+4,j);
                arr[i+2][j]->number=40; picture(i+2,j);
            }
        }
    }
}

void MainWindow::check_four()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(arr[i][j]->number==arr[i][j+1]->number && arr[i][j]->number==arr[i][j+2]->number && arr[i][j]->number==arr[i][j+3]->number)
            {//橫的
                if(i==rr && j==cc)
                {
                    score=score+15;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i][j+3]->number=0;  picture(i,j+3);

                    switch(arr[i][j]->number)
                    {
                     case 1:
                           arr[i][j]->number=21;  picture(i,j);
                        break;
                     case 2:
                           arr[i][j]->number=22;  picture(i,j);
                        break;
                     case 3:
                           arr[i][j]->number=23;  picture(i,j);
                        break;
                     case 4:
                           arr[i][j]->number=24;  picture(i,j);
                        break;
                    }
                }
                else if(i==rr2 && j==cc2)
                {
                    score=score+15;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i][j+3]->number=0;  picture(i,j+3);

                    switch(arr[i][j]->number)
                    {
                     case 1:
                           arr[i][j]->number=21;  picture(i,j);
                        break;
                     case 2:
                           arr[i][j]->number=22;  picture(i,j);
                        break;
                     case 3:
                           arr[i][j]->number=23;  picture(i,j);
                        break;
                     case 4:
                           arr[i][j]->number=24;  picture(i,j);
                        break;
                    }
                }

                if(i==rr && j+1==cc)
                {
                    score=score+15;
                    arr[i][j]->number=0; picture(i,j);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i][j+3]->number=0;  picture(i,j+3);

                    switch(arr[i][j+1]->number)
                    {
                     case 1:
                           arr[i][j+1]->number=21;  picture(i,j+1);
                        break;
                     case 2:
                           arr[i][j+1]->number=22;  picture(i,j+1);
                        break;
                     case 3:
                           arr[i][j+1]->number=23;  picture(i,j+1);
                        break;
                     case 4:
                           arr[i][j+1]->number=24;  picture(i,j+1);
                        break;
                    }
                }
                else if(i==rr2 && j+1==cc2)
                {
                    score=score+15;
                    arr[i][j]->number=0; picture(i,j);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i][j+3]->number=0;  picture(i,j+3);

                    switch(arr[i][j+1]->number)
                    {
                     case 1:
                           arr[i][j+1]->number=21;  picture(i,j+1);
                        break;
                     case 2:
                           arr[i][j+1]->number=22;  picture(i,j+1);
                        break;
                     case 3:
                           arr[i][j+1]->number=23;  picture(i,j+1);
                        break;
                     case 4:
                           arr[i][j+1]->number=24;  picture(i,j+1);
                        break;
                    }
                }

                if(i==rr && j+2==cc)
                {
                    score=score+15;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j]->number=0; picture(i,j);
                    arr[i][j+3]->number=0;  picture(i,j+3);

                    switch(arr[i][j+2]->number)
                    {
                     case 1:
                           arr[i][j+2]->number=21;  picture(i,j+2);
                        break;
                     case 2:
                           arr[i][j+2]->number=22;  picture(i,j+2);
                        break;
                     case 3:
                           arr[i][j+2]->number=23;  picture(i,j+2);
                        break;
                     case 4:
                           arr[i][j+2]->number=24;  picture(i,j+2);
                        break;
                    }
                }
                else if(i==rr2 && j+2==cc2)
                {
                    score=score+15;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j]->number=0; picture(i,j);
                    arr[i][j+3]->number=0;  picture(i,j+3);

                    switch(arr[i][j+2]->number)
                    {
                     case 1:
                           arr[i][j+2]->number=21;  picture(i,j+2);
                        break;
                     case 2:
                           arr[i][j+2]->number=22;  picture(i,j+2);
                        break;
                     case 3:
                           arr[i][j+2]->number=23;  picture(i,j+2);
                        break;
                     case 4:
                           arr[i][j+2]->number=24;  picture(i,j+2);
                        break;
                    }
                }

                if(i==rr && j+3==cc)
                {
                    score=score+15;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i][j]->number=0;  picture(i,j);

                    switch(arr[i][j+3]->number)
                    {
                     case 1:
                           arr[i][j+3]->number=21;  picture(i,j+3);
                        break;
                     case 2:
                           arr[i][j+3]->number=22;  picture(i,j+3);
                        break;
                     case 3:
                           arr[i][j+3]->number=23;  picture(i,j+3);
                        break;
                     case 4:
                           arr[i][j+3]->number=24;  picture(i,j+3);
                        break;
                    }
                }
                else if(i==rr2 && j+3==cc2)
                {
                    score=score+15;
                    arr[i][j+1]->number=0; picture(i,j+1);
                    arr[i][j+2]->number=0; picture(i,j+2);
                    arr[i][j]->number=0;  picture(i,j);

                    switch(arr[i][j+3]->number)
                    {
                     case 1:
                           arr[i][j+3]->number=21;  picture(i,j+3);
                        break;
                     case 2:
                           arr[i][j+3]->number=22;  picture(i,j+3);
                        break;
                     case 3:
                           arr[i][j+3]->number=23;  picture(i,j+3);
                        break;
                     case 4:
                           arr[i][j+3]->number=24;  picture(i,j+3);
                        break;
                    }
                }
            }
        }
    }
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<10;j++)
        {//直的
            if(arr[i][j]->number==arr[i+1][j]->number && arr[i][j]->number==arr[i+2][j]->number && arr[i][j]->number==arr[i+3][j]->number)
            {
                    score=score+15;
                    arr[i+1][j]->number=0; picture(i+1,j);
                    arr[i+2][j]->number=0; picture(i+2,j);
                    arr[i][j]->number=0; picture(i+3,j);

                    switch(arr[i+3][j]->number)
                    {
                     case 1:
                           arr[i+3][j]->number=51;  picture(i+3,j);
                        break;
                     case 2:
                           arr[i+3][j]->number=52;  picture(i+3,j);
                        break;
                     case 3:
                           arr[i+3][j]->number=53;  picture(i+3,j);
                        break;
                     case 4:
                           arr[i+3][j]->number=54;  picture(i+3,j);
                        break;
                    }
               }
          }
     }
}

void MainWindow::check_three()
{

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(arr[i][j]->number==arr[i][j+1]->number && arr[i][j]->number==arr[i][j+2]->number)
            {//橫的
                score=score+10;
                arr[i][j]->number=0;  picture(i,j);
                arr[i][j+1]->number=0; picture(i,j+1);
                arr[i][j+2]->number=0; picture(i,j+2);

            }
        }
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(arr[i][j]->number==arr[i+1][j]->number && arr[i][j]->number==arr[i+2][j]->number)
            {//直的
                score=score+10;
                arr[i][j]->number=0;  picture(i,j);
                arr[i+1][j]->number=0; picture(i+1,j);
                arr[i+2][j]->number=0; picture(i+2,j);

            }
        }
    }
}

void MainWindow::check_three_no_score()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(arr[i][j]->number==arr[i][j+1]->number && arr[i][j]->number==arr[i][j+2]->number)
            {//橫的
                arr[i][j]->number=0;  picture(i,j);
                arr[i][j+1]->number=0; picture(i,j+1);
                arr[i][j+2]->number=0; picture(i,j+2);

            }
        }
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(arr[i][j]->number==arr[i+1][j]->number && arr[i][j]->number==arr[i+2][j]->number)
            {//直的
                arr[i][j]->number=0;  picture(i,j);
                arr[i+1][j]->number=0; picture(i+1,j);
                arr[i+2][j]->number=0; picture(i+2,j);

            }
        }
    }
}

void MainWindow::go_down()
{
    int count=0;
    while(count<=10)//往下掉
    {
    for(int j=0;j<10;j++)
    {
        for(int i=9;i>0;i--)
        {
           if(arr[i][j]->number==0)
           {
               arr[i][j]->number = arr[i-1][j]->number;
               arr[i-1][j]->number=0;
           }
        }
    }
    count++;
    }

    srand((unsigned)time(NULL));
    for(int i=0;i<10;i++) //補上新的方塊
    {
        for(int j=0;j<10;j++)
        {
           if(arr[i][j]->number==0)
           {
                   int n;
                   n = rand() % 4;
                   arr[i][j]->number=n+1;
           }
        }
    }

    while(is_three()) //直到沒有可以換的時候才停止
    {
        check_three_no_score();
        go_down();
    }

    for(int j=0;j<10;j++)//印出圖片
    {
        for(int i=9;i>=0;i--)
        {
            picture(i,j);
        }
    }
}

void MainWindow::star()
{
    if(arr[rr][cc]->number!=40 && arr[rr2][cc2]->number==40)
    {//石頭和星星換

        switch(arr[rr][cc]->number) //指向的是石頭
        {
            case 1://把數字1的石頭全部消掉

                arr[rr2][cc2]->number=0; picture(rr2,cc2);
                for(int i=0;i<10;i++)
                {
                    for(int j=0;j<10;j++)
                    {
                        if(arr[i][j]->number==1)
                        {
                            score=score+1;
                        arr[i][j]->number=0; picture(i,j);

                        }
                    }
                }
                go_down();
                break;
             case 2:

                 arr[rr2][cc2]->number=0; picture(rr2,cc2);
                 for(int i=0;i<10;i++)
                 {
                    for(int j=0;j<10;j++)
                    {
                          if(arr[i][j]->number==2)
                         {
                            score=score+1;
                            arr[i][j]->number=0;picture(i,j);

                         }
                    }
                 }
                 go_down();
                 break;
             case 3:

                   arr[rr2][cc2]->number=0; picture(rr2,cc2);
                   for(int i=0;i<10;i++)
                   {
                        for(int j=0;j<10;j++)
                        {
                           if(arr[i][j]->number==3)
                            {
                                score=score+1;
                                arr[i][j]->number=0;picture(i,j);

                            }
                        }
                   }
                   go_down();
                   break;
            case 4:

                  arr[rr2][cc2]->number=0; picture(rr2,cc2);
                  for(int i=0;i<10;i++)
                  {
                        for(int j=0;j<10;j++)
                        {
                            if(arr[i][j]->number==4)
                            {
                                score=score+1;
                                arr[i][j]->number=0; picture(i,j);

                            }
                        }
                  }
                  go_down();
                  break;
         }
    }
    if(arr[rr2][cc2]->number!=40 && arr[rr][cc]->number==40)
    {
        switch(arr[rr2][cc2]->number) //指向的是石頭
        {
           case 1://把數字1的石頭全部消掉

               arr[rr][cc]->number=0; picture(rr,cc);
               for(int i=0;i<10;i++)
               {
                   for(int j=0;j<10;j++)
                   {
                       if(arr[i][j]->number==1)
                       {
                           score=score+1;
                           arr[i][j]->number=0; picture(i,j);

                       }
                   }
               }
               go_down();
               break;
           case 2:

               arr[rr][cc]->number=0; picture(rr,cc);
               for(int i=0;i<10;i++)
               {
                   for(int j=0;j<10;j++)
                   {
                       if(arr[i][j]->number==2)
                       {
                           score=score+1;
                           arr[i][j]->number=0;picture(i,j);

                       }
                   }
               }
               go_down();
               break;
           case 3:

               arr[rr][cc]->number=0; picture(rr,cc);
               for(int i=0;i<10;i++)
               {
                   for(int j=0;j<10;j++)
                   {
                       if(arr[i][j]->number==3)
                       {
                           score=score+1;
                           arr[i][j]->number=0;picture(i,j);

                       }
                   }
               }
               go_down();
               break;
           case 4:

               arr[rr][cc]->number=0; picture(rr,cc);
               for(int i=0;i<10;i++)
               {
                   for(int j=0;j<10;j++)
                   {
                       if(arr[i][j]->number==4)
                       {
                           score=score+1;
                           arr[i][j]->number=0; picture(i,j);

                       }
                   }
               }
               go_down();
               break;
        }
    }
}

void MainWindow::coo()
{
    for(int i=0;i<10;i++)
    {
           for(int j=0;j<10;j++)
           {
               std::cout<<arr[i][j]->number
                       <<" ";
           }
           std::cout<<std::endl;
       }
    std::cout<<std::endl;

}

void MainWindow::clear_hol()
{
    for(int i=0;i<10;i++) //橫的
    {
        for(int j=0;j<8;j++)
        {
            if(arr[i][j]->number%10==arr[i][j+1]->number%10 && arr[i][j]->number%10==arr[i][j+2]->number%10)
            {
                if(arr[i][j]->number>20 || arr[i][j+1]->number>20 || arr[i][j+2]->number>20){
                if((arr[i][j]->number%20==arr[i][j+1]->number%20) && (arr[i][j]->number%20==arr[i][j+2]->number%20) && (arr[i][j+1]->number%20==arr[i][j+2]->number%20))
                {
                    for(int h=0;h<10;h++)
                    {
                        arr[i][h]->number=0; picture(i,h);
                        score=score+5;
                    }
                }
                }
            }
        }
    }

    for(int i=0;i<8;i++) //十字的
    {
        for(int j=0;j<10;j++)
        {
            if(arr[i][j]->number%10==arr[i+1][j]->number%10 && arr[i][j]->number%10==arr[i+2][j]->number%10)
            {
                if(arr[i][j]->number>20)
                {
                     if((arr[i][j]->number%20==arr[i+1][j]->number%20) && (arr[i][j]->number%20==arr[i+2][j]->number%20))
                     {
                         arr[i+1][j]->number=0; picture(i,j);cout<<"a3";
                         arr[i+2][j]->number=0; picture(i,j);
                        for(int h=0;h<10;h++)
                        {
                            arr[i][h]->number=0; picture(i,h);
                            score=score+5;
                        }
                     }
                }

                if( arr[i+1][j]->number>20)
                {
                    if((arr[i][j]->number%20==arr[i+1][j]->number%20) && (arr[i][j]->number%20==arr[i+2][j]->number%20))
                    {
                        arr[i][j]->number=0; picture(i,j); cout<<"a1";
                        arr[i+2][j]->number=0; picture(i+2,j);
                       for(int h=0;h<10;h++)
                       {
                           arr[i+1][h]->number=0; picture(i+1,h);
                           score=score+5;

                       }
                    }
                }

                if( arr[i+2][j]->number>20)
                {
                    if((arr[i][j]->number%20==arr[i+1][j]->number%20))
                    {
                        arr[i+1][j]->number=0; picture(i+1,j);cout<<"a2";
                        arr[i][j]->number=0; picture(i,j);
                       for(int h=0;h<10;h++)
                       {
                           arr[i+2][h]->number=0; picture(i+2,h);
                           score=score+5;
                       }
                    }
                }
            }
        }
    }

}

bool MainWindow::is_three()
{
   for(int i=1;i<9;i++)
    {
        for(int j=0;j<10;j++)
        {//橫的
            if(arr[i-1][j]->number%10 ==arr[i][j]->number%10 && arr[i+1][j]->number%10 ==arr[i][j]->number%10)
            {
                    return true;
            }
        }
    }

    for(int j=1;j<9;j++)
    {
        for(int i=0;i<10;i++)
        {//直的
            if(arr[i][j-1]->number%10 ==arr[i][j]->number%10 && arr[i][j+1]->number%10 ==arr[i][j]->number%10)
            {
                    return true;
            }
        }
    }
    return false;
}

void MainWindow::boom()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if((arr[i][j]->number%30==arr[i][j+1]->number%30) && (arr[i][j]->number%30==arr[i][j+2]->number%30))
            {
                if(arr[i][j]->number>30)
                {   score=score+45;
                    arr[i][j]->number=0;
                    arr[i][j+1]->number=0;
                    arr[i][j-1]->number=0;
                    arr[i+1][j]->number=0;
                    arr[i+1][j+1]->number=0;
                    arr[i+1][j-1]->number=0;
                    arr[i-1][j]->number=0;
                    arr[i-1][j+1]->number=0;
                    arr[i-1][j-1]->number=0;
                }
                if(arr[i][j+1]->number>30)
                {
                    score=score+45;
                    arr[i][j+1]->number=0;
                    arr[i][j+2]->number=0;
                    arr[i][j]->number=0;
                    arr[i+1][j+1]->number=0;
                    arr[i+1][j+2]->number=0;
                    arr[i+1][j]->number=0;
                    arr[i-1][j+1]->number=0;
                    arr[i-1][j+2]->number=0;
                    arr[i-1][j]->number=0;
                }
                if(arr[i][j+2]->number>30)
                {
                    score=score+45;
                    arr[i][j+2]->number=0;
                    arr[i][j+3]->number=0;
                    arr[i][j+1]->number=0;
                    arr[i+1][j+2]->number=0;
                    arr[i+1][j+3]->number=0;
                    arr[i+1][j+1]->number=0;
                    arr[i-1][j+2]->number=0;
                    arr[i-1][j+3]->number=0;
                    arr[i-1][j+1]->number=0;
                }

            }
        }
    }

    for(int j=0;j<8;j++)
    {
        for(int i=0;i<8;i++)
        {
            if((arr[i][j]->number%30==arr[i+1][j]->number%30) && (arr[i][j]->number%30==arr[i+2][j]->number%30))
            {
                if(arr[i][j]->number>30)
                {
                    score=score+45;
                    arr[i][j]->number=0;
                    arr[i+1][j]->number=0;
                    arr[i-1][j]->number=0;
                    arr[i][j+1]->number=0;
                    arr[i+1][j+1]->number=0;
                    arr[i-1][j+1]->number=0;
                    arr[i][j-1]->number=0;
                    arr[i+1][j-1]->number=0;
                    arr[i-1][j-1]->number=0;
                }
                if(arr[i][j+1]->number>30)
                {
                    score=score+45;
                    arr[i+1][j]->number=0;
                    arr[i+2][j]->number=0;
                    arr[i][j]->number=0;
                    arr[i+1][j+1]->number=0;
                    arr[i+2][j+1]->number=0;
                    arr[i][j+1]->number=0;
                    arr[i+1][j-1]->number=0;
                    arr[i+2][j-1]->number=0;
                    arr[i][j-1]->number=0;
                }
                if(arr[i][j+2]->number>30)
                {
                    score=score+45;
                    arr[i+1][j]->number=0;
                    arr[i+2][j]->number=0;
                    arr[i+3][j]->number=0;
                    arr[i+1][j+1]->number=0;
                    arr[i+2][j+1]->number=0;
                    arr[i+3][j+1]->number=0;
                    arr[i+1][j-1]->number=0;
                    arr[i+2][j-1]->number=0;
                    arr[i+3][j-1]->number=0;
                }

            }
        }
    }
}

void MainWindow::clear_ver()
{
    for(int j=0;j<10;j++) //直的
    {
        for(int i=0;i<8;i++)
        {
            if(arr[i][j]->number%10==arr[i+1][j]->number%10 && arr[i][j]->number%10==arr[i+2][j]->number%10)
            {
                if(arr[i][j]->number>50 || arr[i+1][j]->number>50 || arr[i+2][j]->number>50){
                if((arr[i][j]->number%50==arr[i+1][j]->number%50) && (arr[i][j]->number%50==arr[i+2][j]->number%50))
                {
                    for(int h=0;h<10;h++)
                    {
                        arr[h][j]->number=0; picture(h,j);
                        score=score+5;
                    }
                }
                }
            }
        }
    }

    for(int j=0;j<8;j++) //十字的
    {
        for(int i=0;i<10;i++)
        {
            if(arr[i][j]->number%10==arr[i][j+1]->number%10 && arr[i][j]->number%10==arr[i][j+2]->number%10)
            {
                if(arr[i][j]->number>50)
                {
                     if((arr[i][j]->number%50==arr[i][j+1]->number%50) && (arr[i][j]->number%20==arr[i][j+2]->number%50))
                     {
                         arr[i][j+1]->number=0; picture(i,j+1);
                         arr[i][j+2]->number=0; picture(i,j+2);
                        for(int h=0;h<10;h++)
                        {
                            arr[h][j]->number=0; picture(h,j);
                            score=score+5;
                        }
                     }
                }

                if( arr[i][j+1]->number>50)
                {
                    if((arr[i][j]->number%50==arr[i][j+1]->number%50) && (arr[i][j]->number%20==arr[i][j+2]->number%50))
                    {
                        arr[i][j]->number=0; picture(i,j);
                        arr[i][j+2]->number=0; picture(i,j+2);
                       for(int h=0;h<10;h++)
                       {
                           arr[h][j+1]->number=0; picture(h,j+1);
                           score=score+5;

                       }
                    }
                }

                if( arr[i][j+2]->number>50)
                {
                    if((arr[i][j]->number%50==arr[i+1][j]->number%50) && (arr[i][j]->number%50==arr[i+2][j]->number%50))
                    {
                        arr[i][j+1]->number=0; picture(i,j+1);cout<<"a2";
                        arr[i][j]->number=0; picture(i,j);
                       for(int h=0;h<10;h++)
                       {
                           arr[h][j+2]->number=0; picture(h,j+2);
                           score=score+5;
                       }
                    }
                }
            }
        }
    }
}

void MainWindow::end_game()
{
    if(step==0)
    {
        QMessageBox::information( this, "end game","the end", QMessageBox::Ok, 0 );
    }
}


void MainWindow::on_pushButton_clicked()
{
    start();
}

