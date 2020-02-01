#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
namespace Ui {
class MainWindow;
}
struct User {
    int id = 0;
    QString log = "";
    QString pas = "";
    QString status = "";
    int tmpProduct = 0;
};


struct TmpProduct {
    int id = 0;
    QString name = "";
    QString price = "";
    QString count = "";
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    Ui::MainWindow *ui;
public slots:
    void showProduct();
    void purchase();

    void loginUser();
    void regUser();
    void exitUser();
    void getHistory();

    void showSellProduct();
    void sell_save_id();
    void editProduct();
    void OpenAddProduct();
    void addProduct();
    void updateProduct();
    void updateProduct1();

public:
    int govno;




private:
    User user;
    TmpProduct tmpProduct;
};


#endif // MAINWINDOW_H
