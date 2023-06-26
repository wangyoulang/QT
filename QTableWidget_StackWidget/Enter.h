#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_Enter.h"
#include <QSqlDatabase>   //mysql数据库类
#include <QSqlTableModel>  //mysql表模型库
#include <QSqlQuery>       //mysql查询类库
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
    //商品数量
    int goodsNum;
    //职工数量
    int employeesNum;
    //职工展示列数
    int employeesCol = 6;
    //商品展示列数
    int goodsCol = 5;
    /*
    展示所有商品信息
    */
    void show_goods(QString sql);
    /*
    展示所有员工信息
    */
    void show_employees();
    /*
    获取商品数量
    */
    void obtainQuantityOfProducts();
    /*
    获取员工数量
    */
    void obtainEmloyeesNum();
    /*
    清除输入
    */
    void clearInput();
private:
    Ui::EnterClass *ui;

private slots:
    //增加商品按钮
    void on_addProductInformation_clicked();
    //显示所有商品按钮
    void on_displayAllProducts_clicked();
    //查询商品按钮
    void on_queryProductInformation_clicked();
    //修改商品按钮
    void on_modifyProductInformation_clicked();
    //删除商品按钮
    void on_deleteProductInformation_clicked();
    // 切换商品信息管理页面
    void on_commodityManagement_clicked();
    // 切换职工信息挂你页面
    void on_employeeManagement_clicked();
};

//访问Mysql数据库的静态方法
static bool createMySqlConn() {
    QSqlDatabase sqldb = QSqlDatabase::addDatabase("QMYSQL");
    sqldb.setHostName("120.46.200.124");
    sqldb.setPort(3306);
    sqldb.setDatabaseName("clouddb");    //数据库名称
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
