#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <output.h>
#include<QFont>
#include <QMessageBox>
#include <QFormLayout>
#include <QComboBox>
#include <QRadioButton>

class input : public QWidget
{
    Q_OBJECT
public:
    input(QWidget *parent = nullptr);
    ~input();
    void init_ui0();
    void calculate(double,double);
    void warningMessage(int);


signals:

private:
    QPushButton *b1;
    QLabel *label1;
    QLabel *label2;        
    output *subw;
    QLabel *copyright;
    QLabel *version;
    QFont font_label1;
    QFont font_copyright;
    QPixmap  bgimage;     //背景图片
    //2023/4/4update 选择是否软件开发、软科学研究、基础研究类项目
    QRadioButton *rb1;
    QRadioButton *rb2;
    QFont font_rb1;
    //end

//重写虚函数
protected:
    void paintEvent(QPaintEvent *event);
};

class common_data{//新建一个类存储全局变量
public:
    static double C;//中央财政专项资金
    static double a;//设备购置费
    static double A;//直接经费
    static double B;//间接经费
    static int inputx_l;
    static int inputy_l;
    static bool output_closed;
};

#endif // INPUT_H
