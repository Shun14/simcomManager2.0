#ifndef DIALOG_DEVICELIST_H
#define DIALOG_DEVICELIST_H

#include <QDialog>

namespace Ui {
class Dialog_deviceList;
}

class Dialog_deviceList : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_deviceList(QWidget *parent = 0);
    ~Dialog_deviceList();
    QString httpsOperarte(const QString &url, const QString &data, const QString &type);

private:
    Ui::Dialog_deviceList *ui;
    bool isLoading = false;
    void findDeviceStatuswithRow(const int row);

private slots:
    void on_pushButton_StartLoad_clicked();
    void on_pushButton_ReadFile_clicked();
};

#endif // DIALOG_DEVICELIST_H
