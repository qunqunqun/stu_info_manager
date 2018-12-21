#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("囷的学生管理系统");
    //设置midArea来实现这个多文档的编辑系统
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    ui->mdiArea->setTabShape(QTabWidget::Triangular);   //设置窗口的形状
    ui->mdiArea->setTabPosition(QTabWidget::North); //设置窗口的位置
    ui->mdiArea->setTabsClosable(true);         //可关闭的
    ui->mdiArea->setTabsMovable(true);        //可移动的

    this->cur_table = nullptr;
    this->cur_subwindow = nullptr;
    this->table_view_num = 0; //初始化为0
    this->max_window_num = 20;
    this->systems.clear(); //项目清空
    for(int i = 0; i < 20 ;i++) this->tables[i] = nullptr; //清空
    show_tool_bar = true; //显示
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionnew_file_triggered() //如果出发了这个动作，新建一张表格
{
    if(this->table_view_num >= 20 )
    {
        return; //什么都不做
    }
    this->table_view_num ++;
    tables[table_view_num - 1] = new myTableView;
    QMdiSubWindow * temp = ui->mdiArea->addSubWindow(tables[table_view_num - 1]);
    ui->mdiArea->setActiveSubWindow(temp);
    this->systems[temp] = tables[table_view_num - 1];
    temp->setWindowTitle(QString("subWindow") +QString::number(this->table_view_num));
    temp->show();
    tables[table_view_num - 1]->showMaximized(); //使得最大化
}

void MainWindow::refresh_sys()
{
    cur_subwindow = ui->mdiArea->activeSubWindow(); //获取当前的subwindow
    cur_table = systems[cur_subwindow];
}

void MainWindow::on_actionadd_triggered()
{
    qDebug()<<"增加学生的信息";//增加学生信息
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        this->cur_table->add_info(); //增加学生的信息
    }
}

void MainWindow::on_actiondelete_triggered()
{
    qDebug()<<"删除学生的信息";//增加学生信息
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        int temp_row = this->cur_table->currentRow(); //指定行
        this->cur_table->delete_info(temp_row); //增加学生的信息
    }
}

void MainWindow::on_actionsearch_triggered()
{
      qDebug()<<"查询学生的信息";
      this->refresh_sys(); //重新获取新的窗口
      if(cur_table != nullptr)
      {
          int temp_row = this->cur_table->currentRow(); //指定行
          this->cur_table->search_info(); //增加学生的信息
      }
}

void MainWindow::on_actionmodify_triggered()
{
    qDebug()<<"删除学生的信息";//增加学生信息
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        int temp_row = this->cur_table->currentRow(); //指定行
        this->cur_table->modify_info(temp_row); //增加学生的信息
    }
}

void MainWindow::on_actionstunum_triggered()
{
    qDebug()<<"删除学生的信息";
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        this->cur_table->sort_table(0);
    }
}

void MainWindow::on_actionstuname_triggered()
{
    qDebug()<<"排序学生的信息";
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        this->cur_table->sort_table(1);
    }
}

void MainWindow::on_actiond_2_triggered()
{
    qDebug()<<"保存学生的信息";//增加学生信息
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        this->cur_table->saveTable(0);
    }
}

void MainWindow::on_actiond_3_triggered()
{
    qDebug()<<"保存学生的信息";//增加学生信息
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        this->cur_table->saveTable(1);
    }
}

void MainWindow::on_actiond_triggered()
{
    qDebug()<<"导入学生的信息";//增加学生信息
    this->refresh_sys(); //重新获取新的窗口
    if(cur_table != nullptr)
    {
        this->cur_table->importTable();
    }
}

void MainWindow::closeEvent(QCloseEvent * e)
{
    bool is_ok = true;
    for(int i = 0; i < this->table_view_num; i++)
    {
        if(tables[i]->is_modify_end() == true) //如果是被修改了
        {
            is_ok = false;
            QMessageBox::StandardButton rb = QMessageBox::warning(nullptr, "warning", "内容被修改，是否退出",
                                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb == QMessageBox::No)
            {
                e->ignore();
            }
        }
    }
}

void MainWindow::on_actionhelp_triggered()
{
    qDebug()<<"进行说明帮助的弹出";
    QMessageBox::about(nullptr, tr("About"), tr("学生管理系统，初始化需要输入用户名和登录密码进行验证输入"
                                                "学生信息表格的新建，导入，删除"
                                                "支持信息的插入，删除，修改，排序（学号和姓名）"
                                                "--作者161220097 戚赟"
                                                "@2018.12"));
}

void MainWindow::on_actiond_4_triggered()
{
    cur_subwindow = this->ui->mdiArea->activeSubWindow();
    this->cur_subwindow->close();
}

void MainWindow::on_actions_triggered()
{
    this->ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actions2_triggered()
{
    this->ui->mdiArea->tileSubWindows();
}

void MainWindow::on_actionhide_triggered()
{
    if(this->show_tool_bar == true)
    {
         this->show_tool_bar = false;
         this->ui->mainToolBar->hide();
    }
    else
    {
        this->show_tool_bar = true;
        this->ui->mainToolBar->show();
    }
}
