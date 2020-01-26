#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>
#include <QDir>
#include <QHBoxLayout>
#include <QPushButton>

void MainWindow::showProduct(){
    ui->statusBar->showMessage("Показал продукты");
    QSqlQuery query;

    query.exec("SELECT * FROM product");
    int count = 0;
    while (query.next())count++;

    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(4);
    query.first();
    for(int i=0; i<count; i++){
        for(int j=0; j<3; j++){
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        QWidget* pWidget = new QWidget();
        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("Купить");
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->tableWidget->setCellWidget(i, 3, pWidget);

        connect(btn_edit, SIGNAL(clicked()), this, SLOT(getProduct()));
        btn_edit->setProperty("myId", query.value(0).toInt());
//        MainWindow::getProduct(6);

        query.next();
    }
}

void MainWindow::getProduct(){
    QPushButton *button = (QPushButton *)sender();
    int id = button->property("myId").toInt();
    ui->statusBar->showMessage("ID="+QString::number(id));
}
