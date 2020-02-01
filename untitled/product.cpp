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

    query.exec("SELECT * FROM product WHERE count > 0");
    int count = 0;
    while (query.next())count++;

    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(4);
    query.first();
    for(int i=0; i<count; i++){
        for(int j=0; j<3; j++) ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));

        QWidget* pWidget = new QWidget();
        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("Купить");
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->tableWidget->setCellWidget(i, 3, pWidget);

        connect(btn_edit, SIGNAL(clicked()), this, SLOT(purchase()));
        btn_edit->setProperty("myId", query.value(0).toInt());
        ui->tableWidget->resizeRowsToContents();
        //ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->horizontalHeader()->hide(); ui->tableWidget->verticalHeader()->hide();
        query.next();
    }
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

    query.exec("INSERT INTO `history`(`id`,`text`) VALUES (NULL,'"+user.log+" купил "+name+"');");
    query.first();
    MainWindow::showProduct();
    ui->statusBar->showMessage(QString::number(id));
}

void MainWindow::showSellProduct(){
//    ui->statusBar->showMessage("Показал продукты");
    QSqlQuery query;

    query.exec("SELECT * FROM product");
    int count = 0;
    while (query.next())count++;

    ui->tableWidget_3->setRowCount(count);
    ui->tableWidget_3->setColumnCount(5);
    query.first();
    for(int i=0; i<count; i++){
        for(int j=0; j<4; j++) ui->tableWidget_3->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));

        QWidget* pWidget = new QWidget();
        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("Выбрать");
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->tableWidget_3->setCellWidget(i, 4, pWidget);

        connect(btn_edit, SIGNAL(clicked()), this, SLOT(sell_save_id()));
        btn_edit->setProperty("myId", query.value(0).toInt());
        ui->tableWidget_3->resizeRowsToContents();
        ui->tableWidget_3->horizontalHeader()->hide(); ui->tableWidget_3->verticalHeader()->hide();
        query.next();
    }
}


void MainWindow::sell_save_id(){
    QPushButton *button = (QPushButton *)sender();
    int id = button->property("myId").toInt();
    user.tmpProduct = id;
    ui->statusBar->showMessage(QString::number(id));
}


void MainWindow::editProduct(){
    if(ui->comboBox_3->currentText() == "Удаление"){
        QSqlQuery query;
        query.exec("DELETE FROM product WHERE id = "+QString::number(user.tmpProduct));
        MainWindow::showSellProduct();
        ui->statusBar->showMessage("Удалил строку"+QString::number(user.tmpProduct));
    }
    if(ui->comboBox_3->currentText() == "Изменение"){
        MainWindow::updateProduct();
        ui->statusBar->showMessage("Изменение");
    }
    if(ui->comboBox_3->currentText() == "Добавить"){
        MainWindow::OpenAddProduct();
        ui->statusBar->showMessage("Добавить");
    }
}

void MainWindow::OpenAddProduct(){
//    QWidget *form = new QWidget();
//    QLineEdit *text1 = new QLineEdit(form);
//    QLineEdit *text2 = new QLineEdit(form);
//    QLineEdit *text3 = new QLineEdit(form);
//    QPushButton *button = new QPushButton(form);
//    form->resize(100,150);
//    form->show();
//    text1->setGeometry(20,10,80,20);
//    text2->setGeometry(20,40,80,20);
//    text3->setGeometry(20,70,80,20);
//    button->setGeometry(25,100,70,30);
//    button->setText("Добавить");
    ui->stackedWidget->setCurrentIndex(4);
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(addProduct()));

//    return form;
}

void MainWindow::addProduct(){
    tmpProduct.name = ui->lineEdit_3->text();
    tmpProduct.price = ui->lineEdit_4->text();
    tmpProduct.count = ui->lineEdit_5->text();
    QSqlQuery query;
    QString q = "INSERT INTO `product`(`name`,`price`, `count`) VALUES ('"+tmpProduct.name+"','"+tmpProduct.price+"','"+tmpProduct.count+"');";
    query.first();
    query.exec(q);
//    ui->statusBar->showMessage(q);
    MainWindow::showSellProduct();
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::updateProduct(){
    QSqlQuery query;
    query.exec("SELECT * FROM product WHERE id = "+QString::number(user.tmpProduct));
    query.first();
    ui->lineEdit_6->setText( query.value(1).toString());
    ui->lineEdit_7->setText( query.value(2).toString());
    ui->lineEdit_8->setText( query.value(3).toString());
    ui->stackedWidget->setCurrentIndex(5);
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(updateProduct1()));
}

void MainWindow::updateProduct1(){
    QSqlQuery query;
//    QString q = "UPDATE product SET name = "+ui->lineEdit_6->text()+", price = "+ui->lineEdit_7->text()+",count = "+ui->lineEdit_8->text()+"  WHERE id = "+QString::number(user.tmpProduct)+";";
    query.first();
    query.exec("UPDATE product SET name = '"+ui->lineEdit_6->text()+"', price = '"+ui->lineEdit_7->text()+"',count = '"+ui->lineEdit_8->text()+"'  WHERE id = "+QString::number(user.tmpProduct)+";");
//    query.exec(q);
//    ui->statusBar->showMessage(q);
    MainWindow::showSellProduct();
    ui->stackedWidget->setCurrentIndex(1);
}
