#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataservices.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel();
    listP = data.DocFile(xmlFileName);
    setModelForTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModelForTableView(){
    model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Age"));
    for(int i = 0; i < listP.count(); i++){
        person a = listP.at(i);
        setModel(i, a);
        ui->tableView->setModel(model);
    }
}

void MainWindow::setModel(int i, person a){
    QStandardItem *iID = new QStandardItem(QString("") + QString::number(a.ID));
    QStandardItem *iName = new QStandardItem(QString("") + a.name);
    QStandardItem *iAge = new QStandardItem(QString("") + QString::number(a.age));
    model->setItem(i, 0, iID);
    model->setItem(i, 1, iName);
    model->setItem(i, 2, iAge);
}
void MainWindow::on_addButton_clicked()
{
    person a;
    a.ID = ui->idLineEdit->text().toInt();
    a.name = ui->nameLineEdit->text();
    a.age = ui->ageLineEdit->text().toInt();
    listP.append(a);
    data.GhiFile(listP, xmlFileName);
    setModelForTableView();
}

void MainWindow::on_repairButton_clicked()
{
    int r = ui->tableView->currentIndex().row();
    person a = listP.at(r);
    ui->idLineEdit->setText(QString::number(a.ID));
    ui->nameLineEdit->setText(a.name);
    ui->ageLineEdit->setText(QString::number(a.age));
}

void MainWindow::on_saveButton_clicked()
{
    int r = ui->tableView->currentIndex().row();
    person a;
    a.ID = ui->idLineEdit->text().toInt();
    a.name = ui->nameLineEdit->text();
    a.age = ui->ageLineEdit->text().toInt();
    setModel(r, a);
    listP[r] = a;
    data.GhiFile(listP, xmlFileName);
}

void MainWindow::on_deleteButton_clicked()
{
    if(listP.count() == 0){
        return;
    }
    int r = ui->tableView->currentIndex().row();
    ui->tableView->model()->removeRow(r);
    listP.removeLast();
    data.GhiFile(listP, xmlFileName);
}

bool MainWindow::sosanh(person a, person b){
    if(a.ID > b.ID)
       return true;
    return false;
}

QList<person> MainWindow::bubble_sort(QList<person> list){
    int n = list.count();
    for(int i = 0; i < n; i++){
        for(int j = n - 1; j > i; j--){
            if(sosanh(list.at(j - 1), list.at(j)) == true){
                list.swap(j - 1, j);
            }
        }
    }
    return list;
}
void MainWindow::on_sortButton_clicked()
{
        listP = bubble_sort(listP);
        setModelForTableView();
        data.GhiFile(listP, xmlFileName);
}
