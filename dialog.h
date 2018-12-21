#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <info_system.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    bool check_ok();
    bool is_ok_toadd();
    info_of_student get_newinput();
    bool set_info(info_of_student temp);
    void set_search_mode(); //设置为serach_mode

private:
    Ui::Dialog *ui;
    bool is_ok; //保证输入的合法性是正确的
    info_of_student new_input; //保证加入
    bool searcd_mode; //查询模式

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_comboBox_currentIndexChanged(int index);

};

#endif // DIALOG_H
