#ifndef INFO_SYSTEM_H
#define INFO_SYSTEM_H
#include<QString>

struct info_of_student //信息的结构
{
    QString _Id; //学生的学号，为了确定不会超过一定的限制和合法输入，进行输入的判断
    QString _Name; //学生的姓名
    QString _Sex; //学生的性别，只有男和女的输入值，所以不可以超过这两个值

    QString _Birth; //学生的生日，有差别输入，如"1997-12-08"

    QString _Birthplace; //籍贯即出生地
    QString _Address; //当前的住址

    bool operator == (const info_of_student & x)
    {
        bool is_equal = true;
        if(_Id != x._Id || _Name != x._Name || _Sex != x._Sex || _Birth != x._Birth || _Birthplace != x._Birthplace || _Address != x._Address)
        {
            is_equal = false;
        }
        return is_equal;
    }
};


#endif // INFO_SYSTEM_H
