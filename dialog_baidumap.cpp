#include "dialog_baidumap.h"
#include "ui_dialog_baidumap.h"
#include "mainwindow.h"

#include <QDir>
#include <QDebug>
#include <QUrlQuery>
#include <QTextCodec>
#include <QWebEnginePage>
#include <QWebEngineView>
#include <QWebChannel>

Dialog_baiduMap::Dialog_baiduMap(QWidget *parent, double longitude, double latitude) :
    QDialog(parent),
    ui(new Ui::Dialog_baiduMap)
{
    ui->setupUi(this);
    view = new QWebEngineView(this);

    connect(view->page(), SIGNAL(loadFinished(bool)),this, SLOT(baiduMapLoadFinish()));

    qDebug()<<"connect";
    QWebChannel * channel = new QWebChannel(view->page());
    view->page()->setWebChannel(channel);
    channel->registerObject(QString("ReinforcePC"), this);

    lat = latitude;
    lon = longitude;

    QString filePath = QFileInfo("./mapFile/baiduMap.html").absoluteFilePath();
    QUrl url = "file:///" + filePath;
    qDebug()<<url;
    view->setUrl(url);
    view->show();
}

Dialog_baiduMap::~Dialog_baiduMap()
{
    delete ui;
}

void Dialog_baiduMap::baiduMapLoadFinish()
{
    QString cmd = QString("showAddress(\"%1\",\"%2\")").arg(lon).arg(lat);
    view->page()->runJavaScript(cmd,0);
}
