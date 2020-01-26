#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
namespace Ui {
class MainWindow;
}
struct User {
    int id = 0;
    QString name = "";
    QString log = "";
    QString pas = "";
    QString status = "";
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

    void loginUser();
public:
    int govno;

private:
    User user;
};


#endif // MAINWINDOW_H
