#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>
#include <QLabel>
//#include <QPlainTextEdit>

class output : public QWidget
{
    Q_OBJECT
public:
    explicit output(QWidget *parent = nullptr);
    void init_ui0();
    ~output();



signals:

private:
    QLabel*output_label1;
    QLabel*output_label2;
    QLabel*output_label3;
    QLabel*output_label4;
};

#endif // OUTPUT_H
