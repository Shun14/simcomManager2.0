#ifndef DIALOG_ADMINLOGIN_H
#define DIALOG_ADMINLOGIN_H

#include <QDialog>

namespace Ui {
class Dialog_adminlogin;
}

class Dialog_adminlogin : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_adminlogin(QWidget *parent = 0);
    ~Dialog_adminlogin();
    QString username;
    QString passwd;
    bool isRoot;
private slots:
    void accept();
    void reject();
private:
    Ui::Dialog_adminlogin *ui;

};

#endif // DIALOG_ADMINLOGIN_H
