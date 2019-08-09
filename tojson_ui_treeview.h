#ifndef TOJSON_UI_TREEVIEW_H
#define TOJSON_UI_TREEVIEW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTreeView>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QToolTip>
#include <QMouseEvent>
#include <QList>
#include <QFileDialog>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QHeaderView>

class ToJson_UI_TreeView : public QTreeView
{
    Q_OBJECT
public:
    ToJson_UI_TreeView(QWidget *parent = nullptr);

public:
    QStandardItem* getItem(){return dynamic_cast<QStandardItemModel*>(this->model())->item(0, 0);}

public:
    void createModel();     //创建Model
    void createMenu();      //创建右键菜单

public:
    void actionValue_Clicked();     //在所选择的单元格内添加子节点-"值"
    void actionKey_Clicked();       //在所选择的单元格内添加子节点-"键"
    void actionArray_Clicked();     //在所选择的单元格内添加子节点-"数组"
    void actionObject_Clicked();    //在所选择的单元格内添加子节点-"对象"
    void actionDelete_Clicked();    //在所选择的单元格内添加子节点-"删除"

    QList<QStandardItem*> createValue(const QString value);    //创建列表项-“值”
    QList<QStandardItem*> createKey(const QString key);        //创建列表项-“键”
    QList<QStandardItem*> createArray(const QString array);    //创建列表项-“数组”
    QList<QStandardItem*> createObject(const QString object);  //创建列表项-“对象”
};


#endif // TOJSON_UI_TREEVIEW_H
