#ifndef DIALOG_DEVICELIST_H
#define DIALOG_DEVICELIST_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class Dialog_deviceList;
}

class Dialog_deviceList : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_deviceList(QWidget *parent = 0);
    ~Dialog_deviceList();
    QString httpOperarte(const QString &url, const QString &data, const QString &type);

private:
    Ui::Dialog_deviceList *ui;
    int row = 0;
    bool isLoading = false;
    bool isFirst = false;
    void findDeviceStatuswithRow(const int row);

private slots:
    void on_pushButton_StartLoad_clicked();
    void on_pushButton_ReadFile_clicked();
    void slotHeaderClicked(int column);
    void keyPressEvent(QKeyEvent *event);
    void on_tableWidget_cellDoubleClicked(int row, int column);
};

#endif // DIALOG_DEVICELIST_H
