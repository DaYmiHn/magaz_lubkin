#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QString>
#include <QDir>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(showProduct()));

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QDir tmpCurrDir = QDir::current();
    tmpCurrDir.cdUp();
    QString url = tmpCurrDir.path() + "/database.db3";

    db.setDatabaseName(url);
    db.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
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
        query.next();
        QWidget* pWidget = new QWidget();
        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("Купить");
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->tableWidget->setCellWidget(i, 3, pWidget);
    }
    MainWindow::showProduct();

}
void MainWindow::showProduct(){
    ui->statusBar->showMessage("sdfsdf");
}
