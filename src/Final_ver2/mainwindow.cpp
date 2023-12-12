#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlResult>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ptrLobby = new Lobby();
    ptrSignUp = new SignUp();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrLobby;
}


void MainWindow::on_btnPlay_clicked()
{
    QString username = ui->txtUserName->text();
    QString password = ui->txtPassword->text();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName("C:/Users/ADMIN/Documents/HUST_CODE/2023.1/NetworkProgramming/Final_Project/database/data.db");

    if(QFile::exists("C:/Users/ADMIN/Documents/HUST_CODE/2023.1/NetworkProgramming/Final_Project/database/data.db") )
        qDebug() << "Database file exists";
    else{
        qDebug() << "Database file doesn' t exist";
        return;
    }

    if( !database.open()){
        qDebug() << "Error: Unable open Database!";
        return;

    }else{
        qDebug() << "Database opens successfully!   ";
    }
    qDebug() << "UserName: " << username << ", Password: " << password;
    QSqlQuery query(database);
    query.prepare("select * from Player where UserName = '" + username + "' AND Password ='" + password + "'" );
    query.exec();

    int cnt = 0;

    while(query.next()) cnt++;

    if ( cnt == 1){
    // hide current window
        this->hide();
        ptrLobby->show();

    }else{
        QMessageBox::warning(this, "Warning", "Incorrect account!");

    }

    // qDebug() << "Result:|" << query.value(0) << "|";
    query.finish();query.clear();
    qDebug() << "Last error : "<< query.lastError().text();

    ui->txtUserName->clear();
    ui->txtPassword->clear();



}


void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    ptrSignUp->show();

}


