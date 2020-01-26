#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>
#include <QDir>
#include <QHBoxLayout>
#include <QPushButton>


void MainWindow::loginUser(){
    QString login = ui->textEdit->toPlainText();
    QString password = ui->textEdit_2->toPlainText();
//    QString q = "SELECT * FROM user WHERE log = '"+login+"' AND pas = '"+password+"'";
    QSqlQuery query;
    query.exec("SELECT * FROM user WHERE log = '"+login+"' AND pas = '"+password+"'");
    query.first();
    if(query.value(2) == login){
        user.id = query.value(0).toInt();
        user.name = query.value(1).toString();
        user.log = query.value(2).toString();
        user.pas = query.value(3).toString();
        user.status = query.value(4).toString();
        ui->statusBar->showMessage("Здравствуй, "+user.name);
        ui->textEdit->hide();ui->textEdit_2->hide();ui->pushButton->hide();ui->pushButton_2->hide();ui->pushButton_3->hide();
    } else {
        ui->statusBar->showMessage("Неправильный логин или пароль, ну или сломалось всё :-(");
    }

}
