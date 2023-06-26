#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_Enter.h"
#include <QSqlDatabase>   //mysql���ݿ���
#include <QSqlTableModel>  //mysql��ģ�Ϳ�
#include <QSqlQuery>       //mysql��ѯ���
#include <QSqlQueryModel>
#include <QMessageBox>
#include <qsqlerror.h>
#include <QSqlQuery>
#include <QDebug>

class Enter : public QMainWindow
{
    Q_OBJECT

public:
    Enter(QWidget *parent = nullptr);
    ~Enter();
    //��Ʒ����
    int goodsNum;
    //ְ������
    int employeesNum;
    //ְ��չʾ����
    int employeesCol = 6;
    //��Ʒչʾ����
    int goodsCol = 5;
    /*
    չʾ������Ʒ��Ϣ
    */
    void show_goods(QString sql);
    /*
    չʾ����Ա����Ϣ
    */
    void show_employees();
    /*
    ��ȡ��Ʒ����
    */
    void obtainQuantityOfProducts();
    /*
    ��ȡԱ������
    */
    void obtainEmloyeesNum();
    /*
    �������
    */
    void clearInput();
private:
    Ui::EnterClass *ui;

private slots:
    //������Ʒ��ť
    void on_addProductInformation_clicked();
    //��ʾ������Ʒ��ť
    void on_displayAllProducts_clicked();
    //��ѯ��Ʒ��ť
    void on_queryProductInformation_clicked();
    //�޸���Ʒ��ť
    void on_modifyProductInformation_clicked();
    //ɾ����Ʒ��ť
    void on_deleteProductInformation_clicked();
    // �л���Ʒ��Ϣ����ҳ��
    void on_commodityManagement_clicked();
    // �л�ְ����Ϣ����ҳ��
    void on_employeeManagement_clicked();
};

//����Mysql���ݿ�ľ�̬����
static bool createMySqlConn() {
    QSqlDatabase sqldb = QSqlDatabase::addDatabase("QMYSQL");
    sqldb.setHostName("120.46.200.124");
    sqldb.setPort(3306);
    sqldb.setDatabaseName("clouddb");    //���ݿ�����
    sqldb.setUserName("root");
    sqldb.setPassword("39a4c2f6ebb47c93");
    bool ok = sqldb.open();
    if (ok) {
        return true;
    }
    else {
        QMessageBox::warning(nullptr, "waring", sqldb.lastError().text());
        return false;
    }

}
