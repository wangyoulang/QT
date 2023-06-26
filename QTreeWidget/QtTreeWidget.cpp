#include "QtTreeWidget.h"

QtTreeWidget::QtTreeWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtTreeWidgetClass)
{
    ui->setupUi(this);
    // 添加节点
    /*ui->treeWidget->setColumnCount(1);
    QList<QTreeWidgetItem*> items;
    for (int i = 0; i < 10; ++i)
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    ui->treeWidget->addTopLevelItems(items);*/

    //QObject::connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(on_item_clicked(QTreeWidgetItem*, int)));
    QObject::connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(on_item_double_clicked(QTreeWidgetItem*, int)));
    // 右击菜单栏可以使用两种方式：
    // 1、鼠标右击事件：contextMenuEvent(QContextMenuEvent* event)
    // 2、使用customContextMenuRequested信号，这种方式如下：
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu); 
    QObject::connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(on_item_right_cicked(const QPoint&)));


    // 添加节点方法1
    QTreeWidgetItem* group1 = new QTreeWidgetItem(ui->treeWidget, 1); // 1表示树节点type，类型为int
    group1->setText(0, "第一组");
    //group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    //group1->setCheckState(0, Qt::Unchecked); //状态为未选中
    QTreeWidgetItem* yuwen = new QTreeWidgetItem(2);
    yuwen->setText(0, "语文");
    group1->addChild(yuwen);
    //yuwen->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    //yuwen->setCheckState(0, Qt::Unchecked); //状态为未选中

    // 添加节点方法二--添加多列（此处添加主节点，子节点添加方式不变）
    QTreeWidgetItem *objListItem = new QTreeWidgetItem(QStringList()<<QString("Key")<<QString("Value"));
    ui->treeWidget->addTopLevelItem(objListItem);

}

QtTreeWidget::~QtTreeWidget()
{}

void QtTreeWidget::on_item_clicked(QTreeWidgetItem* item, int colum)
{
    QMessageBox::information(0, "提示", QString("'%1'被选中").arg(item->text(0)));
}
void QtTreeWidget::on_item_double_clicked(QTreeWidgetItem* item, int colum)
{
    // 判断选中节点是否含有父节点
    /*if (item->parent() != nullptr)
    {
        QMessageBox::information(0, "提示", QString("%1的父节点为%2").arg(item->text(0)).arg(item->parent()->text(0)));

    }*/
    // 判断选中节点是否含有子节点
    if (item->child(0) != nullptr)// 如果有子节点
    {
        QMessageBox::information(0, "提示", QString("%1的子节点是%2").arg(item->text(0)).arg(item->child(0)->text(0)));
    }
    else
    {
        QMessageBox::information(0, "提示", QString("%1没有子节点").arg(item->text(0)));
    }
}

// 第一种方式：鼠标右击事件
void QtTreeWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QPoint pos = event->globalPos();  // 获取全局坐标
    QPoint widgetPos = ui->treeWidget->mapFromGlobal(pos); // 将全局坐标转换为相对于树部件的坐标
    QTreeWidgetItem* item = ui->treeWidget->itemAt(widgetPos);  // 获取鼠标位置下的树节点
    /*
    菜单
    */
    designTable = new QAction("第一组");
    designTable->setStatusTip("第一组");
    closeConnection = new QAction("语文");
    closeConnection->setStatusTip("语文");
    globle = new QAction("全局");
    globle->setStatusTip("全局");
    connect(designTable, &QAction::triggered, this, &QtTreeWidget::add_designTable);
    connect(closeConnection, &QAction::triggered, this, &QtTreeWidget::add_closeConnection);
    connect(globle, &QAction::triggered, this, &QtTreeWidget::add_globle);

    menu->clear();
    if (item == nullptr)
    {
        menu->addAction(globle);
        menu->exec(QCursor::pos());
        return;
    }
    int type = item->type();
    if (type == 1)
    {
        menu->addAction(designTable);
    }
    else if (type == 2)
    {
        menu->addAction(closeConnection);
    }
    menu->exec(QCursor::pos());
    //menu->exec(ui->treeWidget->mapToGlobal(pos));
}

// 第二种方式
void QtTreeWidget::on_item_right_cicked(const QPoint& pos)
{
    /*
    菜单
    */
    designTable = new QAction("第一组");
    designTable->setStatusTip("第一组");
    closeConnection = new QAction("语文");
    closeConnection->setStatusTip("语文");
    globle = new QAction("全局");
    globle->setStatusTip("全局");
    connect(designTable, &QAction::triggered, this, &QtTreeWidget::add_designTable);
    connect(closeConnection, &QAction::triggered, this, &QtTreeWidget::add_closeConnection);
    menu->clear();
    QTreeWidgetItem* item = ui->treeWidget->itemAt(pos);
    if (item == nullptr)
    {
        menu->addAction(globle);
        menu->exec(ui->treeWidget->mapToGlobal(pos));
        return;
    }
    int type = item->type();
    if (type == 1)
    {
        menu->addAction(designTable);
    }
    else if (type == 2)
    {
        menu->addAction(closeConnection);
    }
    //menu->exec(QCursor::pos());
    menu->exec(ui->treeWidget->mapToGlobal(pos));
    
}
void QtTreeWidget::add_designTable()
{
    qDebug() << "是第一组这个东西";
}
void QtTreeWidget::add_closeConnection()
{
    qDebug() << "是语文这个东西";
}
void QtTreeWidget::add_globle()
{
    qDebug() << "globle";
}
