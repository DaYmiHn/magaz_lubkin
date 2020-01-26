#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>
#include <QDir>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QDir tmpCurrDir = QDir::current();
    tmpCurrDir.cdUp();
    QString url = tmpCurrDir.path() + "/database.db3";

    db.setDatabaseName(url);
    db.open();

    MainWindow::showProduct();
}

MainWindow::~MainWindow()
{
    delete ui;
}


