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


    // 添加节点方法1
    QTreeWidgetItem* group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, "第一组");
    //group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    //group1->setCheckState(0, Qt::Unchecked); //状态为未选中
    QTreeWidgetItem* yuwen = new QTreeWidgetItem();
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
