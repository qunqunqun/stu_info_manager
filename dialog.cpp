#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [=](){ qDebug("Ok");}); //绑定
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, [=](){ qDebug("Cancel"); });
    this->is_ok = false;
    this->new_input._Sex= "男";
    this->searcd_mode = false; //不为空
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::check_ok() //判断当前输入的合法性
{
    this->is_ok = true;
    //必须都不为空
    if(this->ui->lineEdit->text().isEmpty() == true)
    {
        this->is_ok = false;
    }
    if(this->ui->lineEdit_2->text().isEmpty()== true)
    {
        this->is_ok = false;
    }
    if(this->ui->lineEdit_3->text().isEmpty() == true)
    {
        this->is_ok = false;
    }
    if(this->ui->lineEdit_4->text().isEmpty() == true)
    {
        this->is_ok = false;
    }
    if(this->ui->lineEdit_5->text().isEmpty() == true)
    {
        this->is_ok = false;
    }
    return this->is_ok;
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))   //判断按下的是否为"确定”按钮
    {
       if(this->check_ok() == true || this->searcd_mode == true) //可以添加或者search_mode
       {
           this->new_input._Id = this->ui->lineEdit->text();
           this->new_input._Name = this->ui->lineEdit_2->text();
           this->new_input._Birth = this->ui->lineEdit_3->text();
           this->new_input._Birthplace = this->ui->lineEdit_4->text();
           this->new_input._Address = this->ui->lineEdit_5->text();
           if(this->searcd_mode == true)
           {
               this->searcd_mode = false; //设置为错误
           }
       }
    }
    else if(button == ui->buttonBox->button((QDialogButtonBox::Cancel)))
    {
        this->is_ok = false;
        qDebug()<<"Cancel";
    }
}

info_of_student Dialog:: get_newinput()
{
     return this->new_input; //返回当前的新的输入
}

bool Dialog:: is_ok_toadd()
{
     return this->is_ok; //是否能加入
}

void Dialog::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
         this->new_input._Sex= "男";
    }
    else
    {
         this->new_input._Sex= "女";
    }
}

bool Dialog::set_info(info_of_student temp)
{
    qDebug()<<temp._Sex;
    this->ui->comboBox->setCurrentText(temp._Sex);
    this->new_input._Sex= temp._Sex;
    this->ui->lineEdit->setText(temp._Id);
    this->ui->lineEdit_2->setText(temp._Name);
    this->ui->lineEdit_3->setText(temp._Birth);
    this->ui->lineEdit_4->setText(temp._Birthplace);
    this->ui->lineEdit_5->setText(temp._Address);
}

void Dialog:: set_search_mode()
{
    this->searcd_mode = true;
}
