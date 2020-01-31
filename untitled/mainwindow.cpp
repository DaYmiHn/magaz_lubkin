#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>
#include <QDir>
#include <QHBoxLayout>
#include <QLineEdit>


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


    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(loginUser()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(regUser()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(exitUser()));
    ui->stackedWidget->setCurrentIndex(3);
    MainWindow::showProduct();
}

MainWindow::~MainWindow()
{
    delete ui;
}

