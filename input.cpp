#include "input.h"
#include <QDebug>
#include <QLineEdit>
#include <QIntValidator>
#include <QButtonGroup>

double common_data::C=0;
double common_data::a=0;
double common_data::A=0;
double common_data::B=0;
int common_data::inputx_l=300;
int common_data::inputy_l=250;
bool common_data::output_closed;//判断是否需要删掉旧窗口
#define output_label1x_l 30
#define output_label1y_l 100
#define deltay 50

//l表示location,s表示size
#define windowx_s 890
#define windowy_s 550
#define buttonx_s 120
#define buttony_s 60
#define label1x_l 240
#define label1y_l 150
#define label2x_l 240
#define label2y_l 260
//2023/4/4update
#define rb1x_l 240
#define rb1y_l 80
//#define combobox1x_l 260
//#define combobox1y_l 160
//#define combobox1x_s 400
//#define combobox1y_s 40
//end
#define textCx_s 400
#define textCy_s 40

input::input(QWidget *parent)
    : QWidget(parent)
{
    //创建界面
    init_ui0();
}

//初始化界面
void input::init_ui0(){

    //设置窗口的标题,this指向widget,表示在窗口上
    this->setWindowTitle("间接费用计算器(上海版)");//2023/4/4update 名称
    //设置窗口大小
    this->resize(windowx_s,windowy_s);
    // 移动窗口位置
    this->move(common_data::inputx_l,common_data::inputy_l);


    //设置窗口图标
    this->setWindowIcon(QIcon("./photo/icon.jpg"));
    //设置主窗口关闭时，关闭子窗口
    this->setAttribute(Qt::WA_QuitOnClose,true);



    b1=new QPushButton("确定",this);
    //设置按钮大小
    b1->resize(buttonx_s,buttony_s);

    //设置按钮文字大小
    b1->setFont(QFont("宋体",18));

    //文本框的标题
    label1=new QLabel("请输入中央财政专项资金(万元):",this);



    font_label1.setBold(true);
    font_label1.setFamily("宋体");
    font_label1.setPointSize(12);
    label1->setFont(font_label1);

    label2=new QLabel("请输入购置设备费(万元):",this);

    label2->setFont(font_label1);


    //文本框
    QLineEdit *C = new QLineEdit(this);

    C->resize(textCx_s,textCy_s);
    C->setFont(QFont("宋体",15));
    QLineEdit *a = new QLineEdit(this);

    a->resize(textCx_s,textCy_s);
    a->setFont(QFont("宋体",15));

    //2023/4/4update:单选框
    rb1=new QRadioButton("软件项目",this);
    rb1->move(rb1x_l,rb1y_l);
    font_rb1.setBold(true);
    font_rb1.setFamily("宋体");
    font_rb1.setPointSize(14);
    rb1->setFont(font_rb1);
    rb1->setChecked(1);//默认选中

    rb2=new QRadioButton("其它项目",this);
    rb2->move(label1x_l+textCx_s-140,rb1y_l);
    rb2->setFont(font_rb1);
    //创建按钮组
    QButtonGroup* btngroup1=new QButtonGroup(this);
    btngroup1->addButton(rb1,0);
    btngroup1->addButton(rb2,1);
    //end

    //改变位置（移动）
    b1->move((windowx_s-buttonx_s)/2,(windowy_s-buttony_s)*0.85);
    label1->move(label1x_l,label1y_l);
    label2->move(label2x_l,label2y_l+20);
    C->move(label1x_l,label1y_l+textCy_s);
    a->move(label2x_l,label2y_l+textCy_s*3/2);

    //版权所有
    copyright=new QLabel("Copyright © 2022 Harry Yu.",this);
    copyright->move(windowx_s*0.65,windowy_s-30);
    font_copyright.setBold(true);
    font_copyright.setFamily("宋体");
    font_copyright.setPointSize(10);
    copyright->setFont(font_copyright);
    copyright->setStyleSheet("color:white;");
    //版本号
    version =new QLabel("version:1.3.2",this);
    version->move(windowx_s*0.65,windowy_s-60);
    version->setFont(font_copyright);
    version->setStyleSheet("color:white;");


    //设置窗口为父类防止占用内存
    C->setParent(this);
    a->setParent(this);
    b1->setParent(this);
    label1->setParent(this);
    label2->setParent(this);

    //回车换行
    //    connect(C,SIGNAL(editingFinished()),
    //            a,SLOT(setFocus()));
    //回车确定
    connect(C, SIGNAL(returnPressed()),
            b1, SIGNAL(clicked()), Qt::UniqueConnection);
    connect(a, SIGNAL(returnPressed()),
            b1, SIGNAL(clicked()), Qt::UniqueConnection);



    // 限定输入
    QDoubleValidator* CDoubleValidator = new QDoubleValidator;
    C->setValidator(CDoubleValidator);
    QDoubleValidator* aDoubleValidator = new QDoubleValidator;
    a->setValidator(aDoubleValidator);

    common_data::output_closed=true;//初始化，否则会出错

    //获取文本框的输入。(按下按钮即时的动作)
    connect(b1,&QPushButton::clicked,this,[=]()mutable{
        if(common_data::output_closed==false){
            delete subw;
        }
        QString linetextC=C->text();
        QString linetexta=a->text();
        //qDebug()<<linetext;
        //错误输入弹出警告
        if(linetextC.isEmpty()){
            warningMessage(1);
            common_data::output_closed=true;
            return;
        }//第一个空框
        if(linetexta.isEmpty()){
            warningMessage(2);
            common_data::output_closed=true;
            return;
        }//第二个空框
        if(linetextC.toDouble()<linetexta.toDouble()){
            warningMessage(3);
            common_data::output_closed=true;
            return;
        }//中央资金大于购置设备费       

        //qDebug()<<C->text();
        //获取输入框中的数据
        common_data::C=C->text().toDouble();
        //获取输入框中的数据
        common_data::a=a->text().toDouble();

        //qDebug()<<"C="<<common_data::C<<",a="<<common_data::a;


        //计算
        double i_C=common_data::C;//i是input的意思
        double i_a=common_data::a;
        double temp_A;
        temp_A=(i_C+0.3*i_a)/1.3;
        if(temp_A-i_a<=500){
            common_data::A=temp_A;
        }
        else{
            temp_A=i_a/5+i_C*4/5-20;
            if(temp_A-i_a>500&&temp_A-i_a<=1000){
                ;
            }
            else{
                temp_A=(i_a/5+i_C-75)/1.2;
            }
            common_data::A=temp_A;
        }
        common_data::B=common_data::C-common_data::A;
        //qDebug()<<"直接经费A为:"<<common_data::A<<",间接经费B为:"<<common_data::B;


        //2023/4/4 update
//        if(btngroup1->checkedId() == 0)
//        {
//           qDebug()<<"软件项目";
//        }
//        if(btngroup1->checkedId() == 1)
//        {
//           qDebug()<<"其它项目";
//        }
        //错误处理：软件项目,间接费用比例不超过60%
        if(btngroup1->checkedId() == 0){
            if(common_data::B>(common_data::A-common_data::a)*0.6){//直接费用-设备购置费用
            warningMessage(4);//错误04
            common_data::output_closed=true;
            return;
            }
        }
        //错误处理：其它项目,间接费用比例不超过40%
        if(btngroup1->checkedId() == 1){
            if(common_data::B>(common_data::A-common_data::a)*0.4){
            warningMessage(5);//错误05
            common_data::output_closed=true;
            return;
            }
        }
        //end

        subw=new output;
        subw->show();
    });



}

void input::paintEvent(QPaintEvent *event)//设置背景
{
    Q_UNUSED(event);// 不使用的参数不报错
    QPalette PAllbackground = this->palette();
    //QImage ImgAllbackground("./photo/background.png");//package用这个
    QImage ImgAllbackground("../price_calculation/photo/background.png");//运行用这个
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

void input::warningMessage(int error_type)
{
    QMessageBox box;
    if(error_type==1){
        box.setText("错误01:未输入中央财政专项资金!");
    }
    else if(error_type==2){
        box.setText("错误02:未输入购置设备费!");
    }
    else if(error_type==3){
        box.setText("错误03:中央财政专项资金<购置设备费!");
    }
    else if(error_type==4){
        box.setText("错误04:软件项目,间接费用比例不能超过60%!");
    }
    else if(error_type==5){
        box.setText("错误05:其它项目,间接费用比例不能超过40%!");
    }
    box.setWindowTitle("警告");
    box.setIcon(QMessageBox::Icon::Warning );
    box.setButtonText(QMessageBox::Ok ,"确定");
    box.exec();
}
input::~input()
{
    if(common_data::output_closed==false){
        delete subw;
    }
}

