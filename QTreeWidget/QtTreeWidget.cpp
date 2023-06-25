#include "QtTreeWidget.h"

QtTreeWidget::QtTreeWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtTreeWidgetClass)
{
    ui->setupUi(this);
    // ��ӽڵ�
    /*ui->treeWidget->setColumnCount(1);
    QList<QTreeWidgetItem*> items;
    for (int i = 0; i < 10; ++i)
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    ui->treeWidget->addTopLevelItems(items);*/

    //QObject::connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(on_item_clicked(QTreeWidgetItem*, int)));
    QObject::connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(on_item_double_clicked(QTreeWidgetItem*, int)));


    // ���ҽڵ�
    QTreeWidgetItem* group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, "��һ��");
    group1->setText(1, "�ڶ���");
    //group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    //group1->setCheckState(0, Qt::Unchecked); //״̬Ϊδѡ��
    QTreeWidgetItem* yuwen = new QTreeWidgetItem();
    yuwen->setText(0, "����");
    group1->addChild(yuwen);
    //yuwen->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    //yuwen->setCheckState(0, Qt::Unchecked); //״̬Ϊδѡ��

}

QtTreeWidget::~QtTreeWidget()
{}

void QtTreeWidget::on_item_clicked(QTreeWidgetItem* item, int colum)
{
    QMessageBox::information(0, "��ʾ", QString("'%1'��ѡ��").arg(item->text(0)));
}
void QtTreeWidget::on_item_double_clicked(QTreeWidgetItem* item, int colum)
{
    // �ж�ѡ�нڵ��Ƿ��и��ڵ�
    /*if (item->parent() != nullptr)
    {
        QMessageBox::information(0, "��ʾ", QString("%1�ĸ��ڵ�Ϊ%2").arg(item->text(0)).arg(item->parent()->text(0)));

    }*/
    // �ж�ѡ�нڵ��Ƿ����ӽڵ�
    if (item->child(0) != nullptr)// ������ӽڵ�
    {
        QMessageBox::information(0, "��ʾ", QString("%1���ӽڵ���%2").arg(item->text(0)).arg(item->child(0)->text(0)));
    }
    else
    {
        QMessageBox::information(0, "��ʾ", QString("%1û���ӽڵ�").arg(item->text(0)));
    }
}
