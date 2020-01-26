#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\qt_project\\magaz\\database.db3");
    db.open();

    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM product");
    int count = 0;
    //Выводим значения из запроса
    while (query.next())
    {
//    QString id = query.value(1).toString();
//    count = QString::number(query.size());
//    ui->textEdit->insertPlainText(id+"\n");
    count++;
    }
    ui->statusBar->showMessage( QString::number(count));
    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(3);
    query.first();
    for(int i=0; i<count; i++){
        for(int j=0; j<3; j++){
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        query.next();
    }

}

