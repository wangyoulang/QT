#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_QtTreeWidget.h"
#include <QMessageBox>

class QtTreeWidget : public QMainWindow
{
    Q_OBJECT

public:
    QtTreeWidget(QWidget *parent = nullptr);
    ~QtTreeWidget();
private slots:
    void on_item_clicked(QTreeWidgetItem*, int);
    void on_item_double_clicked(QTreeWidgetItem*, int);

private:
    Ui::QtTreeWidgetClass *ui;
};