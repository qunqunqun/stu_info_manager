#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->is_correct = false;
    this->is_ret = true;
    this->setWindowTitle("登陆");
    this->ui->lineEdit->setText(tr("qunqun"));
    this->ui->lineEdit_2->setText(tr("beibei"));
}

login::~login()
{
    delete ui;
}



void login::closeEvent(QCloseEvent * e)
{
     this->is_ret = false;
}

bool login::get_is_correct()
{
    return this->is_correct;
}

bool login::get_is_ret()
{
    return this->is_ret;
}

void login::on_buttonBox_clicked(QAbstractButton *button)
{
    this->is_ret = true;
    qDebug()<<"clicked";
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))   //判断按下的是否为"确定”按钮
    {
         QString user = this->ui->lineEdit->text();
         QString password = this->ui->lineEdit_2->text(); //用户名，密码
         if(user == "qunqun" && password == "beibei") //密码输入正确!
         {
              qDebug()<<"correct";
              QMessageBox::about(nullptr,tr("about"),tr("密码输入正确"));
              this->is_correct = true;
         }
         else //输入错误
         {
             qDebug()<<"error";
             QMessageBox::warning(nullptr,tr("警告"),tr("用户名和密码不正确，重新输入!"),QMessageBox::Ok);
             this->is_correct = false;
         }
    }
    else if(button == ui->buttonBox->button((QDialogButtonBox::Cancel)))
    {
        this->is_ret = false;
    }
}
