#include "Enter.h"
#include "ui_Enter.h"

Enter::Enter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnterClass)
{
    ui->setupUi(this);
    // 设置tableWidget格式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置行适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列适应
    ui->tableWidget->setColumnCount(goodsCol);
    QStringList goods_headers;
    goods_headers << "商品编号" << "商品名称" << "商品数量" << "商品价格" << "商品种类";
    ui->tableWidget->setHorizontalHeaderLabels(goods_headers);
    // 设置职工管理的tableWidget_2格式
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置行适应
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列适应
    ui->tableWidget_2->setColumnCount(employeesCol);
    QStringList workerss_headers;
    workerss_headers << "职工编号" << "职工姓名" << "职工电话" << "职工账号" << "职工密码" << "职工籍贯";
    ui->tableWidget_2->setHorizontalHeaderLabels(workerss_headers);
    QString querySql = "select * from goods;";
    show_goods(querySql);
    show_employees();
    
}

Enter::~Enter()
{}

void Enter::on_commodityManagement_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void Enter::on_employeeManagement_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Enter::obtainQuantityOfProducts()
{
    QSqlQuery query;
    QString sql = "select count(*) from goods;";
    query.exec(sql);
    if (query.next())
    {
        goodsNum = query.value(0).toInt();
    }
}

void Enter::obtainEmloyeesNum()
{
    QSqlQuery query;
    QString sql = "select count(*) from worker;";
    query.exec(sql);
    if (query.next())
    {
        employeesNum = query.value(0).toInt();
    }
}
void Enter::clearInput()
{
    ui->lE_itemNumber->clear();
    ui->lE_tradeName->clear();
    ui->lE_quantityOfGoods->clear();
    ui->lE_commodityPrice->clear();
    ui->lE_commodityCategory->clear();
}
void Enter::show_goods(QString sql)
{
    obtainQuantityOfProducts();
    ui->tableWidget->setRowCount(goodsNum);
    //开始查数据库
    QSqlQuery query;
    if (query.exec(sql))
    {
        for (int i = 0; query.next(); i++)
        {
            for (int j = 0; j < goodsCol; j++)
            {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
            }
        }
        ui->tableWidget->show();
    }
    else
    {
        QMessageBox::warning(this, "waring", query.lastError().text());
    }
}

void Enter::show_employees()
{
    obtainEmloyeesNum();
    ui->tableWidget_2->setRowCount(employeesNum);
    //开始查数据库
    QString sql = "select * from worker;";
    QSqlQuery query;
    if (query.exec(sql))
    {
        for (int i = 0; query.next(); i++)
        {
            for (int j = 0; j < employeesCol; j++)
            {
                ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
            }
        }
        ui->tableWidget_2->show();
    }
    else
    {
        QMessageBox::warning(this, "waring", query.lastError().text());
    }
}
void Enter::on_addProductInformation_clicked()
{
    //int id = ui->lE_itemNumber->text().toInt();
    QString name = ui->lE_tradeName->text();
    int num = ui->lE_quantityOfGoods->text().toInt();
    double price = ui->lE_commodityPrice->text().toDouble();
    QString kind = ui->lE_commodityCategory->text();
    if (name != NULL && num != NULL && price != NULL && kind != NULL)
    {
        //QString sql = "insert into goods (name, num, price, kind) values (?, ?, ?, ?);";
        QString sql = QString("insert into goods (name, num, price, kind) values ('%1', '%2', '%3', '%4');").arg(name).arg(num).arg(price).arg(kind);
        QSqlQuery query;
        if (!query.exec(sql))
        {
            QMessageBox::warning(this, "增加商品失败", query.lastError().text());
        }
        else
        {
            clearInput();
            QMessageBox::information(this, "提示", "成功增加商品信息");
        }
    }
    else
    {
        QMessageBox::warning(this, "增加商品失败", "请完善信息，商品编号不用填！");
    }
    QString querySql = "select * from goods;";
    show_goods(querySql);
}


void Enter::on_displayAllProducts_clicked()
{
    QString querySql = "select * from goods;";
    show_goods(querySql);
}

void Enter::on_deleteProductInformation_clicked()
{
    int id = ui->lE_itemNumber->text().toInt();
    QString name = ui->lE_tradeName->text();
    if (id != NULL || name != NULL)
    {

        QString sql = id == NULL ? QString("delete from goods where name = '%1';").arg(name) : QString("delete from goods where id = %1;").arg(id);
        QSqlQuery query;
        if (!query.exec(sql))
        {
            QMessageBox::warning(this, "删除商品失败", query.lastError().text());
        }
        else
        {
            clearInput();
            QMessageBox::information(this, "提示", "成功删除商品信息");
        }
    }
    else
    {
        QMessageBox::warning(this, "增加商品失败", "请输入商品编号或商品名称！");
    }
    QString querySql = "select * from goods;";
    show_goods(querySql);
}

void Enter::on_modifyProductInformation_clicked()
{
    int id = ui->lE_itemNumber->text().toInt();
    QString name = ui->lE_tradeName->text();
    int num = ui->lE_quantityOfGoods->text().toInt();
    double price = ui->lE_commodityPrice->text().toDouble();
    QString kind = ui->lE_commodityCategory->text();
    if (id != NULL && name != NULL && num != NULL && price != NULL && kind != NULL)
    {
        //QString sql = "insert into goods (name, num, price, kind) values (?, ?, ?, ?);";
        QString sql = QString("update goods set name = '%1', num = '%2', price = '%3', kind = '%4' where id = '%5';").arg(name).arg(num).arg(price).arg(kind).arg(id);
        QSqlQuery query;
        if (!query.exec(sql))
        {
            QMessageBox::warning(this, "修改商品失败", query.lastError().text());
        }
        else
        {
            clearInput();
            QMessageBox::information(this, "提示", "成功修改商品信息");
        }
    }
    else
    {
        QMessageBox::warning(this, "增加商品失败", "请完善信息！");
    }
    QString querySql = "select * from goods;";
    show_goods(querySql);
}

void Enter::on_queryProductInformation_clicked()
{
    int id = ui->lE_itemNumber->text().toInt();
    QString name = ui->lE_tradeName->text();
    if (id != NULL || name != NULL)
    {
        QString querySql = id == NULL ? QString("select * from goods where name = '%1';").arg(name) : QString("select * from goods where id = %1;").arg(id);
        ui->tableWidget->clearContents();
        show_goods(querySql); 
    }
    else
    {
        QMessageBox::warning(this, "查询商品失败", "请输入商品编号或商品名称！");
    }
}