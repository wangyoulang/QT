#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Form)
{   
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    if (ui->lEdit_user->text() == "123456" && ui->lEdit_password->text() == "123456")
    {
        accept();
    }
    else
    {
        ui->lEdit_user->clear();
        ui->lEdit_password->clear();
    }
}
