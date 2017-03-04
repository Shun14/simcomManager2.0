#include "dialog_devicelist.h"
#include "ui_dialog_devicelist.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMenu>
#include <QInputDialog>
#include <QFileDialog>

Dialog_deviceList::Dialog_deviceList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_deviceList)
{
    ui->setupUi(this);
    this->setWindowTitle("小安宝设备查询软件");
}

Dialog_deviceList::~Dialog_deviceList()
{
    delete ui;
}
void Dialog_deviceList::on_pushButton_ReadFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("小安宝设备查询软件"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("小安宝设备查询软件"), tr("文件打开失败:\n%1").arg(path));
            return;
        }
        QTextStream stream(&file);
        QString line;
        ui->tableWidget->setRowCount(0);//clear the table
        while(!stream.atEnd())
        {
            line = stream.readLine(); // 一行一行读取，不包括“/n”的一行文本
            int rowNum = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(rowNum+1);

            ui->tableWidget->setItem(rowNum, 0, new QTableWidgetItem(line));
            ui->tableWidget->item(rowNum, 0)->setForeground(Qt::blue);
        }
        ui->tableWidget->resizeColumnsToContents();

        file.close();
    }
}

void Dialog_deviceList::on_pushButton_StartLoad_clicked()
{
    static int row = 0;

    if(!isLoading && ui->tableWidget->rowCount() != 0)
    {
        isLoading = true;
        ui->pushButton_StartLoad->setText("停止查询");
        for(; row < ui->tableWidget->rowCount() && isLoading ; row++)
        {
            findDeviceStatuswithRow(row);
        }
    }
    else
    {
        ui->pushButton_StartLoad->setText("继续查询");
        row--;
        isLoading = false;
    }
}

void Dialog_deviceList::findDeviceStatuswithRow(const int row){

    MainWindow *ptr = (MainWindow*)parentWidget();

    QString imeiString = ui->tableWidget->item(row, 0)->text();
    QString url = "http://" + ptr->ui->lineEdit_IP->text().toLatin1() +
                  ":"+ptr->ui->lineEdit_port->text().toLatin1() +
                  "/v1/imeiData/" + imeiString;
    qDebug()<<url;

    QString result = httpsOperarte(url, NULL, "GET");
    qDebug()<<result;
    if(result.isEmpty()){
        return;
    }

    QJsonDocument jsonDocument = QJsonDocument::fromJson(result.toLatin1());
    if( jsonDocument.isNull() )
    {
        qDebug()<< "please check the string "<< result;
        return;
    }
    QJsonObject object = jsonDocument.object();

    QJsonValue code = object.take("code");
    if(!code.isUndefined())
    {
        return;
    }

    int version = object.take("version").toInt();
    int version_a = version / 65536;
    int version_b = (version % 65536) / 256;
    int version_c = version % 256;
    qDebug()<<version;
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString("%1.%2.%3").arg(version_a).arg(version_b).arg(version_c)));

    int state = object.take("state").toInt();
    qDebug()<<state;

    if(state){
        ui->tableWidget->setItem(row,2,new QTableWidgetItem("online"));
        ui->tableWidget->item(row, 2)->setForeground(Qt::green);
    }
    else{
        ui->tableWidget->setItem(row,2,new QTableWidgetItem("offline"));
        ui->tableWidget->item(row, 2)->setForeground(Qt::red);
    }

    QDateTime time = QDateTime::fromTime_t(object.take("timestamp").toInt());
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(time.toString("yyyy.MM.dd hh:mm:ss dddd")));

    double lat = object.take("latitude").toDouble();
    double lon = object.take("longitude").toDouble();
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString("%1,  %2").arg(lat).arg(lon)));

    int GSM = object.take("GSM").toInt();
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString("%1").arg(GSM)));
    if(GSM > 20){
        ui->tableWidget->item(row, 5)->setBackground(Qt::green);
    }
    else if(GSM > 10){
        ui->tableWidget->item(row, 5)->setBackground(Qt::yellow);
    }
    else{
        ui->tableWidget->item(row, 5)->setBackground(Qt::red);
    }
    int voltage = object.take("voltage").toInt();
    ui->tableWidget->setItem(row,6,new QTableWidgetItem(QString("%1").arg(voltage)));

    int speed = object.take("speed").toInt();
    ui->tableWidget->setItem(row,7,new QTableWidgetItem(QString("%1").arg(speed)));

    int course = object.take("course").toInt();
    ui->tableWidget->setItem(row,8,new QTableWidgetItem(QString("%1").arg(course)));
    ui->tableWidget->resizeColumnsToContents();

}

QString Dialog_deviceList::httpsOperarte(const QString &url, const QString &data, const QString &type)
{
    QNetworkRequest _request;
    _request.setUrl(QUrl(url));
    QSslConfiguration _sslCon = _request.sslConfiguration();
    _sslCon.setPeerVerifyMode(QSslSocket::VerifyNone);
    _request.setSslConfiguration(_sslCon);
    _request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    QNetworkAccessManager m_NtwkAccManager;
    QNetworkReply *_reply;
    if(type == "POST"){
        _reply = m_NtwkAccManager.post(_request, data.toLatin1());
    }

    if(type == "GET"){
        _reply = m_NtwkAccManager.get(_request);
    }

    if(type == "DELETE"){
        _reply = m_NtwkAccManager.deleteResource(_request);
    }

    if(type == "PUT"){
        _reply = m_NtwkAccManager.put(_request, data.toLatin1());
    }
    _reply->ignoreSslErrors();

    QTime _t;
    _t.start();

    int TIMEOUT = (5 * 1000);
    bool _timeout = false;

    while (!_reply->isFinished()){
        QApplication::processEvents();
        if (_t.elapsed() >= TIMEOUT) {
            _timeout = true;
            break;
        }
    }

    QString _result;
    if (!_timeout && _reply->error() == QNetworkReply::NoError){
        _result = _reply->readAll();
    }
    else{
        QMessageBox::information(this, QString("小安提示"),QString("访问失败：") + QString::number(_reply->error()) + "!\n");
    }
    _reply->deleteLater();

    return _result;
}
