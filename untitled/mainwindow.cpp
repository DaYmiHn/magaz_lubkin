#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\1.db3");
    db.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM contacts");

    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString age = query.value(2).toString();
    ui->textEdit->insertPlainText(id+" "+name+" "+age+"\n");
    }
    ui->statusBar->showMessage("Вывел");
}
