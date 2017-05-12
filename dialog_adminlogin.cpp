#include "dialog_adminlogin.h"
#include "ui_dialog_adminlogin.h"
#include "http_operate.h"

#include <QDebug>
#include <QMessageBox>
Dialog_adminlogin::Dialog_adminlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_adminlogin)
{
    ui->setupUi(this);
    ui->inputUsername->setText(username);
    ui->inputPasswd->setText(passwd);
}

Dialog_adminlogin::~Dialog_adminlogin()
{
    delete ui;
}

void Dialog_adminlogin::reject()
{
    Dialog_adminlogin::done(0);
}
void Dialog_adminlogin::accept()
{

    qDebug()<<ui->inputPasswd->text().toLatin1()<<":"<<ui->inputUsername->text().toLatin1();
    if (ui->inputPasswd->text().toLatin1().isEmpty() == 0 && ui->inputUsername->text().toLatin1().isEmpty() == 0) {
        username = ui->inputUsername->text().toLatin1();
        passwd = ui->inputPasswd->text().toLatin1();
        qDebug()<<"enter the main";
        QString url = "http://localhost:8083/admin/event";
        qDebug()<<url;
        QString result = http_operate::instance().httpOperarteWithAuth(url, NULL, "GET", username, passwd,this);
        qDebug()<<result;
        qDebug()<<result.isEmpty();
        if (result.isEmpty() == true) {
            qDebug()<<"login error";
            QMessageBox::information(this, tr("xiaoantishi"),tr("Please try again!\n"));
        } else {

            Dialog_adminlogin::done(1);
        }

    } else {
        qDebug()<<"input is empty";
        QMessageBox::information(this, tr("xiaoantishi"),tr("Please input username and password or click cancel get no permission!\n"));
    }
}
