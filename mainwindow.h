#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString httpsOperarte(const QString &url, const QString &data, const QString &type);

private:
    Ui::MainWindow *ui;
    QMenu *pTableMenu;

private slots:
    void on_pushButton_FindDeviceLog_clicked();
    void on_pushButton_findDevice_clicked();
    void on_pushButton_GPS_clicked();
    void on_pushButton_GSM_clicked();
    void on_pushButton_LOG_clicked();
    void on_pushButton_SETTING_clicked();
    void on_pushButton_BATTERY_clicked();
    void on_pushButton_REBOOT_clicked();
    void on_pushButton_UPGRADE_clicked();

};

#endif // MAINWINDOW_H
