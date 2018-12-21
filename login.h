#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QCloseEvent>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    bool get_is_correct();
    bool get_is_ret();
    void closeEvent(QCloseEvent * e);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::login *ui;
    bool is_correct;
    bool is_ret;
};

#endif // LOGIN_H
