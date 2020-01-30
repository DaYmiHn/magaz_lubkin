#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>
#include <QDir>
#include <QHBoxLayout>
#include <QPushButton>


void MainWindow::loginUser(){
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
//    QString q = "SELECT * FROM user WHERE log = '"+login+"' AND pas = '"+password+"'";
    QSqlQuery query;
    query.exec("SELECT * FROM user WHERE log = '"+login+"' AND pas = '"+password+"'");
    query.first();
    if(query.value(1) == login){
        user.id = query.value(0).toInt();
        user.log = query.value(1).toString();
        user.pas = query.value(2).toString();
        user.status = query.value(3).toString();
        ui->statusBar->showMessage("Здравствуй, "+user.log);
        ui->lineEdit->hide();ui->lineEdit_2->hide();ui->pushButton->hide();ui->pushButton_2->hide();ui->pushButton_3->hide();
    } else {
        ui->statusBar->showMessage("Неправильный логин или пароль или вас не существует, ну или сломалось всё :(");
    }

}

void MainWindow::regUser(){
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QSqlQuery query;
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

        ui->lineEdit->hide();ui->lineEdit_2->hide();ui->pushButton->hide();ui->pushButton_2->hide();ui->pushButton_3->hide();
    } else {
        ui->statusBar->showMessage("сломалось всё :-(");
        ui->lineEdit->setText(q);
    }

}

void MainWindow::exitUser(){
   ui->statusBar->showMessage("ВЫШЕЛ");

}

