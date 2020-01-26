#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
namespace Ui {
class MainWindow;
}
struct User {
    int id = 0;
    QString login = "";
    int role = 0;
    bool authorized = false;
    int cartCount = 0;
    int productsID[20];
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void showProduct();
    void getProduct();
public:
    int govno;

private:
    User user;
};


#endif // MAINWINDOW_H
