#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QObject>
#include <QString>
#include <QtXml>
#include <QModelIndex>
#include <QStandardItem>
#include <QStandardItemModel>
#include "person.h"
#include "dataservices.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_repairButton_clicked();

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void on_sortButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    DataServices data;
    QList<person> listP;
    QString xmlFileName = "C:/Users/hp/Documents/TableViewDemo-master/DemoXml3.xml";
    void setModel(int, person);
    void setModelForTableView();
    bool sosanh(person, person);
    QList<person> bubble_sort(QList<person>);
};

#endif // MAINWINDOW_H
