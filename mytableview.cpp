#include "mytableview.h"
#include <QFileDialog>
#include<QMessageBox>
#include <QtAlgorithms> //实现排序
#include <iconv.h>
#include <windows.h>

myTableView::myTableView()
{
    //初始化插入数据
    this->setColumnCount(6); //设置列数为5
    this->setRowCount(0); //设置行数为10
    QStringList header;
    header<<"学号"<<"姓名"<<"性别"<<"出生年日"<<"籍贯"<<"住址";
    this->setHorizontalHeaderLabels(header);
    stu_number = 0; //初始化学生信息
    this->is_modify = false; //未曾修改
    this->is_loaded = false; //判断是否是被加载
    loaded_file.clear();
    this->temp_dialog = nullptr;
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置为不可编辑
    this->show();
    stus.clear(); //清空这个数据结构
}

myTableView::~myTableView()
{
    //系统自动进行清空操作
}

void myTableView::add_info()
{
    this->temp_dialog = new Dialog();
    this->temp_dialog->exec();
    if(this->temp_dialog->is_ok_toadd() == true)//可以增加
    {
        info_of_student temp = this->temp_dialog->get_newinput();
        bool is_exist = false;
        for(int i = 0; i < this->stus.size(); i++)
        {
            if(this->stus[i]._Id == temp._Id)
            {
                is_exist = true;
            } //学号相同无法添加
        }
        if(is_exist == false)
        {
            this->insertRow(stu_number);
            this->setItem(stu_number,0,new QTableWidgetItem(temp._Id));
            this->setItem(stu_number,1,new QTableWidgetItem(temp._Name));
            this->setItem(stu_number,2,new QTableWidgetItem(temp._Sex));
            this->setItem(stu_number,3,new QTableWidgetItem(temp._Birth));
            this->setItem(stu_number,4,new QTableWidgetItem(temp._Birthplace));
            this->setItem(stu_number,5,new QTableWidgetItem(temp._Address));
            this->stus.push_back(temp); //存进入temp
            //增加一行
            stu_number++;
            qDebug()<<stu_number<<" "<<this->rowCount();
            is_modify = true; //被修改了
        }
        else
        {
             QMessageBox::warning(nullptr,tr("警告"),tr("学号相同无法添加!"),QMessageBox::Ok);
        }
    }
}

void myTableView::delete_info(int cur)
{
    auto a = stus.begin();
    for(int i = 0; i < this->stus.size(); i++)
    {
        if(this->item(cur,0)->text() == stus[i]._Id)
        {
            break;
        }
        a++;
    }
    this->stus.erase(a); //清除这一行数据
    this->removeRow(cur);
    if(stu_number >= 1)
    {
        is_modify = true; //被修改了
        stu_number--;
    }
}

void myTableView::modify_info(int cur) //修改信息
{
    this->temp_dialog = new Dialog();
    //获取当前信息
    info_of_student temp; 
    temp._Id = this->item(cur,0)->text();
    temp._Name = this->item(cur,1)->text();
    temp._Sex = this->item(cur,2)->text();
    temp._Birth = this->item(cur,3)->text();
    temp._Birthplace = this->item(cur,4)->text();
    temp._Address = this->item(cur,5)->text();
    QString save_ID = temp._Id; //保存下来的save

    this->temp_dialog->set_info(temp);
    this->temp_dialog->exec();
    if(this->temp_dialog->is_ok_toadd() == true)//可以增加
    {
        info_of_student temp = this->temp_dialog->get_newinput();
        if(temp._Id == save_ID) //没有改变学号
        {
            this->setItem(cur,0,new QTableWidgetItem(temp._Id));
            this->setItem(cur,1,new QTableWidgetItem(temp._Name));
            this->setItem(cur,2,new QTableWidgetItem(temp._Sex));
            this->setItem(cur,3,new QTableWidgetItem(temp._Birth));
            this->setItem(cur,4,new QTableWidgetItem(temp._Birthplace));
            this->setItem(cur,5,new QTableWidgetItem(temp._Address));
            auto a = stus.begin();
            for(int i = 0; i < this->stus.size(); i++)
            {
                if(this->item(cur,0)->text() == stus[i]._Id)
                {
                    break;
                }
                a++;
            }
            *a = temp;
        }
        else //改变了学号
        {
            bool is_exist = false;
            for(int i = 0; i < this->stus.size(); i++)
            {
                if(this->stus[i]._Id == temp._Id && temp._Id != save_ID)
                {
                    is_exist = true;
                } //学号相同无法添加
            }
            if(is_exist == false)
            {
                this->setItem(cur,0,new QTableWidgetItem(temp._Id));
                this->setItem(cur,1,new QTableWidgetItem(temp._Name));
                this->setItem(cur,2,new QTableWidgetItem(temp._Sex));
                this->setItem(cur,3,new QTableWidgetItem(temp._Birth));
                this->setItem(cur,4,new QTableWidgetItem(temp._Birthplace));
                this->setItem(cur,5,new QTableWidgetItem(temp._Address));
                auto a = stus.begin();
                for(int i = 0; i < this->stus.size(); i++)
                {
                    if(this->item(cur,0)->text() == stus[i]._Id)
                    {
                        break;
                    }
                    a++;
                }
                *a = temp;
            }
            else
            {
                 QMessageBox::warning(nullptr,tr("警告"),tr("学号相同无法修改!"),QMessageBox::Ok);
            }

        }
        is_modify = true; //被修改了
    }
}

void myTableView::sort_table(int row_num)
{
    is_modify = true; //被修改了
    if(row_num == 0)
    {
        this->sortItems(row_num);
    }
    else if(row_num == 1)
    {
         this->sortItems(row_num,Qt::SortOrder::AscendingOrder);
    }
}

void myTableView::saveTable(int way)
{
    QString fileName;
    if(way == 0) //表示保存
    {
        if(this->loaded_file.isEmpty() == true)
        {
            fileName = QFileDialog::getSaveFileName(nullptr,tr("保存文件"),
                                                    tr("/root/Projects/product/bin/config/未命名.txt"),
                                                    tr("file(*.txt )"));
            loaded_file = fileName; //记录下表格所存在的地址
        }
        else
        {
            fileName = loaded_file;
        }
    }
    else if(way == 1) //表示另存为
    {
        fileName = QFileDialog::getSaveFileName(nullptr,tr("保存文件"),
                                                tr("/root/Projects/product/bin/config/未命名.txt"),
                                                tr("file(*.txt )"));
         if(this->loaded_file.isEmpty() == true) loaded_file = fileName; //记录下表格所存在的地址
    }

    if(!fileName.isEmpty())
    {
        //将表格数据写入文件
        if(QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".xls");
        }
        QFile file;
        file.setFileName(fileName);
        //打开文件
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox msg;
            msg.setText("打开文件失败!");
            msg.exec();
        }
        else
        {
            this->is_modify = false;
            qDebug("open file success:::");
            QTextStream out(&file);
            int rowCount = this->rowCount();
            int colCount = this->columnCount();
            //将表头写入文件
            qDebug("saveTable start:::");
            //读取单元格的数据并写入文件
            qDebug()<<"row count:::"<<rowCount<<"col count:::"<<colCount;
            for(int row = 0; row < rowCount; row++)
            {
                for(int col = 0; col < colCount; col++)
                {
                    QString text = this->item(row,col)->text();
                    qDebug()<<"text:::"<<text;
                    if(text.isEmpty())
                    {
                        out << "null" << "\t";
                    }
                    else
                    {
                        out << text << "\t";
                    }
                }
                out << "\n";       //linux下换行符是'\n'
            }
            out.flush();
            qDebug("saveTable end:::");
            file.close();       //关闭文件
            QMessageBox::information(nullptr,tr("提示"),tr("导出成功!"));
        }
    }
    else
    {
        QMessageBox::warning(nullptr,tr("警告"),tr("文件名未指定!"),QMessageBox::Ok);
    }
}

//将文件数据导入表格
void myTableView::importTable()
{
    if(this->is_modify == true)//如果被修改了，则进行保存操作
    {
         QMessageBox::StandardButton rb = QMessageBox::warning(nullptr, "warning", "内容被修改，是否进行保存？",
                                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
         if(rb == QMessageBox::Yes)//确定是被修改的
         {
                  if(this->loaded_file.isEmpty()) //如果为空，进行另存为操作
                  {
                      this->saveTable(1);
                  }
                  else //进行保存操作
                  {
                      this->saveTable(0);
                  }
        }
    }
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("导入文件"),
                                                tr("/root/Projects/product/bin/config"),
                                                tr("file(*.txt)"));
    if(this->loaded_file.isEmpty()) //原来的为空
    {
        this->loaded_file = fileName;
    }
    if(!fileName.isEmpty())
    {
        QFile file;
        file.setFileName(fileName);
        //打开文件
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox msg;
            msg.setText("打开文件失败!");
            msg.exec();
        }
        else
        {
            if(!file.size())
            {
                QMessageBox::warning(nullptr,tr("警告"),tr("文件大小为空!"),QMessageBox::Ok);
            }
            else
            {
                //将文件数据导入表格
                int r_count = 0;        //统计文件的行数
                QStringList textList;   //记录文件中每一行的数据
                QTextStream in(&file);
                while (!in.atEnd())
                {
                    QString line = in.readLine();
                    textList.append(line);          //保存文件的数据
                    r_count++;                      //记录文件的行数
                }
                file.close();       //关闭文件
                if(!textList.isEmpty())
                {
                    QStringList listRowHeader = textList.at(0).split("\t");
                    int c_count = listRowHeader.count();
                    this->clear();
                    this->setRowCount(r_count);      //前两行是行列表头
                    this->setColumnCount(c_count-1);   //最后一行是“\t"
                    qDebug()<<"start importTable row count:::"<<r_count<<"col count:::"<<c_count;
                    for(int row = 0; row < r_count; row++)
                    {
                        QStringList tmpList;
                        tmpList = textList.at(row).split("\t");
                        info_of_student temp;
                        for(int col = 0; col < c_count; col++)
                        {
                            QTableWidgetItem *item = new QTableWidgetItem(tmpList.at(col));
                            this->setItem(row, col, item);
                        }
                        //获取相应的item
                        temp._Id = this->item(row,0)->text();
                        temp._Name = this->item(row,1)->text();
                        temp._Sex = this->item(row,2)->text();
                        temp._Birth = this->item(row,3)->text();
                        temp._Birthplace = this->item(row,4)->text();
                        temp._Address = this->item(row,5)->text();
                        this->stus.push_back(temp); //存进入stus中
                    }
                    this->stu_number = r_count;
                    QMessageBox::information(nullptr,tr("提示"),tr("导入成功!"));
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(nullptr,tr("警告"),tr("文件名未指定!"),QMessageBox::Ok);
    }
}

void myTableView:: closeEvent(QCloseEvent *e)
{
     if(this->is_modify == true)//如果被修改了，则进行保存操作
     {
         QMessageBox::StandardButton rb = QMessageBox::warning(nullptr, "warning", "内容被修改，是否进行保存？",
                                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
         if(rb == QMessageBox::Yes)//确定是被修改的
         {
               if(this->loaded_file.isEmpty()) //如果为空，进行另存为操作
               {
                   this->saveTable(1);
               }
               else //进行保存操作
               {
                   this->saveTable(0);
               }
         }
     }
}

void myTableView::  search_info()
{
    this->temp_dialog = new Dialog();
    this->temp_dialog->exec(); //执行新的Dialog
    info_of_student temp = this->temp_dialog->get_newinput();
    //进行查询活动
    int i = 0;
    for(; i < this->rowCount(); i++)
    {
        if(this->item(i,0)->text() == temp._Id && this->item(i,1)->text() == temp._Name && this->item(i,2)->text() == temp._Sex
        && this->item(i,3)->text() == temp._Birth  && this->item(i,4)->text() == temp._Birthplace && this->item(i,5)->text() == temp._Address)
        {
            break;
        }
    }
    if( i >=  this->rowCount())
        QMessageBox::about(nullptr, tr("about"), tr("信息不存在"));
    else
        QMessageBox::about(nullptr, tr("about"), tr("信息在第")+(QString::number(i+1)+"行"));
    this->selectRow(i);
}

bool myTableView:: is_modify_end()
{
    return this->is_modify;
}


