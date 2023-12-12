#include "signup.h"
#include "ui_signup.h"
#include <QString>
#include <QMessageBox>

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()
{
    QString username = ui->txtUserName->text();
    QString fullname = ui->txtFullName->text();
    QString password = ui->txtPassword->text();
    QString emailOrPhone = ui->txtEmailOrPhoneNumber->text();

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

    query.exec("insert into Player(Username, Password, Fullname, EmailOrPhone) values ('" + username + "','" + password +"' , '" + fullname + "','" + emailOrPhone + "')" );
    int cnt = 0;
    while( query.next()) cnt++;
    if( cnt == 1){
        QMessageBox::information(this, "Sign up", "Create new account successfully!");
    }else{
        QMessageBox::warning(this, "Sign up", "Create new account successfully!");

    }

    ui->txtFullName->clear();
    ui->txtUserName->clear();
    ui->txtPassword->clear();
    ui->txtEmailOrPhoneNumber->clear();
}

