#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <info_system.h>
#include <mytableview.h>
#include <QMdiSubWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void refresh_sys();
    void closeEvent(QCloseEvent * e);
    ~MainWindow();

private slots:
    void on_actionnew_file_triggered();

    void on_actionadd_triggered();

    void on_actiondelete_triggered();

    void on_actionsearch_triggered();

    void on_actionmodify_triggered();

    void on_actionstunum_triggered();

    void on_actionstuname_triggered();

    void on_actiond_2_triggered();

    void on_actiond_triggered();

    void on_actiond_3_triggered();

    void on_actionhelp_triggered();

    void on_actiond_4_triggered();

    void on_actions_triggered();

    void on_actions2_triggered();

    void on_actionhide_triggered();

private:
    Ui::MainWindow *ui;
    int table_view_num; //表格的多少的数量,只增不减
    QMap<QMdiSubWindow*,myTableView*>systems; //为信息管理系统的每个表格
    QMdiSubWindow * cur_subwindow;
    myTableView * cur_table;
    int max_window_num; //最多窗口
    myTableView * tables[20]; //数组
    bool show_tool_bar; //显示tool_bar
};

#endif // MAINWINDOW_H
