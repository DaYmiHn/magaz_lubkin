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
    QSqlQuery query;
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

void MainWindow::purchase(){
    QPushButton *button = (QPushButton *)sender();
    int id = button->property("myId").toInt();

    QSqlQuery query;
    query.exec("SELECT * FROM product WHERE id = "+QString::number(id));
    query.first();
    int count=query.value(3).toInt()-1;
    QString name = query.value(1).toString();
    query.exec("UPDATE product SET count = "+QString::number(count)+" WHERE id = "+QString::number(id)+";");
    query.first();

    query.exec("INSERT INTO `transaction`(`id`,`text`) VALUES (NULL,'"+user.log+" купил "+name+"');");
    query.first();

    ui->statusBar->showMessage(QString::number(id));
}

