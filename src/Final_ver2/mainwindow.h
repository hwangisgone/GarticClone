#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "databaseheader.h"
#include "lobby.h"
#include "signup.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnPlay_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Lobby *ptrLobby;
    SignUp *ptrSignUp;
};
#endif // MAINWINDOW_H
