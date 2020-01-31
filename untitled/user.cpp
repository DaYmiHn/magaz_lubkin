#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>
#include <QDir>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>

void MainWindow::loginUser(){
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QSqlQuery query;
    query.exec("SELECT * FROM user WHERE log = '"+login+"' AND pas = '"+password+"'");
    query.first();
    if(query.value(1) == login){
        user.id = query.value(0).toInt();
        user.log = query.value(1).toString();
        user.pas = query.value(2).toString();
        user.status = query.value(3).toString();
        ui->statusBar->showMessage("Здравствуй, "+user.log);
        if (user.status == "buy") ui->stackedWidget->setCurrentIndex(2);
        if (user.status == "sell") ui->stackedWidget->setCurrentIndex(1);
        if (user.status == "admin") ui->stackedWidget->setCurrentIndex(0);
    } else {
        ui->statusBar->showMessage("Неправильный логин или пароль или вас не существует, ну или сломалось всё :(");
    }

}

void MainWindow::regUser(){
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QSqlQuery query;
    query.first();
    QString q = "INSERT INTO `user`(`id`,`log`,`pas`,`status`) VALUES (NULL,'"+login+"','"+password+"','buy');";
    query.exec(q);
    query.exec("SELECT * FROM user WHERE log = '"+login+"' AND pas = '"+password+"'");
    query.first();
    if(query.value(1) == login){
        user.id = query.value(0).toInt();
        user.log = query.value(1).toString();
        user.pas = query.value(2).toString();
        user.status = query.value(3).toString();
        ui->statusBar->showMessage("Здравствуй, "+user.log);
        ui->stackedWidget->setCurrentIndex(2);
    } else {
        ui->statusBar->showMessage("сломалось всё :-(");
        ui->lineEdit->setText(q);
    }

}

void MainWindow::exitUser(){
   ui->lineEdit->setText("");
   ui->lineEdit_2->setText("");
   user.id = 0;
   user.log = "";
   user.pas = "";
   user.status = "";
   ui->statusBar->showMessage("ВЫШЕЛ");
   ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::getHistory(){
    QWidget *form = new QWidget();
    QTableWidget *table = new QTableWidget(form);
    form->resize(250,200);

    QSqlQuery query;

    query.exec("SELECT * FROM history");
    int count = 0;
    while (query.next())count++;

    table->setRowCount(count);
    table->setColumnCount(2);
    table->resizeRowsToContents();
//    table->resizeColumnsToContents();
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    query.first();
    for(int i=0; i<count; i++){
        for(int j=0; j<3; j++) table->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        query.next();
    }


    form->show();
}

