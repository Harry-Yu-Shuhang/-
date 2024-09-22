#include "output.h"
#include "input.h"
#include <QLabel>
#include<QFont>
#include <math.h>
#define windowx_s 500
#define windowy_s 300
#define output_label1x_l 30
#define output_label1y_l 60
#define deltay 50

output::output(QWidget *parent) : QWidget(parent)
{
    //创建界面
    init_ui0();
}
void output::init_ui0(){

    //设置主窗口关闭时，关闭子窗口
    this->setAttribute(Qt::WA_QuitOnClose,false);

    //设置窗口的标题,this指向my_widget,表示在窗口上
    this->setWindowTitle("计算结果");
    //设置窗口大小
    this->resize(windowx_s,windowy_s);
    //设置窗口位置
    this->move(common_data::inputx_l+windowx_s*1.79,common_data::inputy_l);
    //设置窗口图标
    this->setWindowIcon(QIcon("./photo/icon.jpg"));

    output_label1=new QLabel(this);
    output_label2=new QLabel(this);
    output_label3=new QLabel(this);
    output_label4=new QLabel(this);

    output_label1->setParent(this);
    output_label2->setParent(this);
    output_label3->setParent(this);
    output_label4->setParent(this);

    output_label1->setText("直接经费为:");//common_data::output
    output_label1->move(output_label1x_l,output_label1y_l);
    output_label1->setFont(QFont("宋体",12));


//    output_label2->setText(QString::number(common_data::A,'f',4).append("万元"));//保留两位小数
    output_label2->setText(QString::number(ceil(common_data::A)).append("万元"));//向上取整
    output_label2->move(output_label1x_l,output_label1y_l+deltay);  
    QFont font_num;
    font_num.setBold(true);
    font_num.setFamily("宋体");
    font_num.setPointSize(12);
    output_label2->setFont(font_num);
    output_label2->setStyleSheet("color:red;");

    output_label3->setText("间接经费为:");
    output_label3->move(output_label1x_l,output_label1y_l+deltay*2);
    output_label3->setFont(QFont("宋体",12));

//    output_label4->setText(QString::number(common_data::B,'f',4).append("万元"));//保留两位小数
    output_label4->setText(QString::number(floor(common_data::B)).append("万元"));//向下取整
    output_label4->move(output_label1x_l,output_label1y_l+deltay*3);
    output_label4->setFont(font_num);
    output_label4->setStyleSheet("color:red;");
    common_data::output_closed=false;
}

output::~output(){
}

