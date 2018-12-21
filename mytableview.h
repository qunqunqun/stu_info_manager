#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableWidget>
#include <QStandardItemModel>
#include <QDebug>
#include <dialog.h>


class myTableView : public QTableWidget
{

public:
    myTableView();
    ~myTableView();
    void add_info();
    void delete_info(int cur);
    void modify_info(int cur); //对于某一个行进行修改
    void sort_table(int row_num); //对于某一列进行排序
    void saveTable(int way); //保存表格内容
    void importTable();//导入表格内容
    void search_info(); //进行查询输入
    void closeEvent(QCloseEvent * e);
    bool is_modify_end();//返回是否被修改了

private:
    Dialog * temp_dialog;
    QStandardItemModel * model;
    int stu_number; //学生信息的数量
    bool is_empty; //是否是空文件，来进行保存操作
    bool is_modify;
    bool is_loaded; //判断是否是被加载
    QString loaded_file;
    QVector<info_of_student> stus; //用于保存当前的信息，进行查询
};


#endif
