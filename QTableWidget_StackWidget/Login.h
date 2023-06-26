#pragma once
#include "ui_Login.h"
#include <QDialog> 
namespace Ui { class Form; }
class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();

private:
    Ui::Form*ui;

private slots:
    void on_btnLogin_clicked();
};

