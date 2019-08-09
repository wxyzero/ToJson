#include "tojson_ui_treeview.h"

ToJson_UI_TreeView::ToJson_UI_TreeView(QWidget *parent) : QTreeView(parent)
{
    //创建model
    this->createModel();
    //创建右键菜单
    this->createMenu();
}

void ToJson_UI_TreeView::createModel()
{
    QStandardItemModel* model = new QStandardItemModel;

    //创建根节点
    QIcon objectIcon(":/O.png");
    QStandardItem* item_Main = new QStandardItem(objectIcon, QStringLiteral("JSON"));

    //添加子节点（数组）
    QList<QStandardItem*> templist;
    QStandardItem* item_array_0 = new QStandardItem(QIcon(":/A.png"), QString(QStringLiteral("数组")));
    QStandardItem* item_array_1 = new QStandardItem(QString(""));
    QStandardItem* item_array_2 = new QStandardItem(QString(""));
    templist.append(item_array_0);
    templist.append(item_array_1);
    templist.append(item_array_2);
    item_Main->appendRow(templist);

    //设置表格行标题
    model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("类型") << QStringLiteral("键(名)") << QStringLiteral("值(序号)"));
    //添加根节点
    model->appendRow(item_Main);

    //添加model
    this->setModel(dynamic_cast<QStandardItemModel*>(model));
}

void ToJson_UI_TreeView::createMenu()
{
    //二级菜单
    QAction* actionValue = new QAction(QStringLiteral("值"), this);
    QAction* actionKey = new QAction(QStringLiteral("键"), this);
    QAction* actionArray = new QAction(QStringLiteral("数组"), this);
    QAction* actionObject = new QAction(QStringLiteral("对象"), this);
    QMenu* menu = new QMenu;
    menu->addAction(actionValue);
    menu->addAction(actionKey);
    menu->addAction(actionArray);
    menu->addAction(actionObject);

    //一级菜单
    QAction* actionNew = new QAction(QStringLiteral("插入子节点"), this);
    QAction* actionDelete = new QAction(QStringLiteral("删除该节点"), this);
    this->addAction(actionNew);
    this->addAction(actionDelete);

    //一级菜单与二级菜单绑定
    actionNew->setMenu(menu);

    //生成右键菜单
    this->setContextMenuPolicy(Qt::ActionsContextMenu); //设置contextMenuPolicy属性值为"以Actions为弹出菜单的菜单项组成菜单"

    //绑定功能按钮与对应槽
    connect(actionValue, &QAction::triggered, this, &ToJson_UI_TreeView::actionValue_Clicked);
    connect(actionKey, &QAction::triggered, this, &ToJson_UI_TreeView::actionKey_Clicked);
    connect(actionArray, &QAction::triggered, this, &ToJson_UI_TreeView::actionArray_Clicked);
    connect(actionObject, &QAction::triggered, this, &ToJson_UI_TreeView::actionObject_Clicked);
    connect(actionDelete, &QAction::triggered, this, &ToJson_UI_TreeView::actionDelete_Clicked);
}

void ToJson_UI_TreeView::actionValue_Clicked()
{
    dynamic_cast<QStandardItemModel*>(this->model())->itemFromIndex(currentIndex())->appendRow(createValue(QStringLiteral("value")));
}

void ToJson_UI_TreeView::actionKey_Clicked()
{
    dynamic_cast<QStandardItemModel*>(this->model())->itemFromIndex(currentIndex())->appendRow(createKey(QStringLiteral("key")));
}

void ToJson_UI_TreeView::actionArray_Clicked()
{
    dynamic_cast<QStandardItemModel*>(this->model())->itemFromIndex(currentIndex())->appendRow(createArray(QStringLiteral("")));
}

void ToJson_UI_TreeView::actionObject_Clicked()
{
    dynamic_cast<QStandardItemModel*>(this->model())->itemFromIndex(currentIndex())->appendRow(createObject(QStringLiteral("")));
}

void ToJson_UI_TreeView::actionDelete_Clicked()
{
    if(currentIndex().parent().isValid())
        dynamic_cast<QStandardItemModel*>(this->model())->itemFromIndex(currentIndex())->parent()->removeRow(currentIndex().row());
}

QList<QStandardItem*> ToJson_UI_TreeView::createValue(const QString value)
{
    QList<QStandardItem*> templist;
    QStandardItem* item_value_0 = new QStandardItem(QIcon(":/V.png"), QString(QStringLiteral("值")));
    QStandardItem* item_value_1 = new QStandardItem(QString(""));
    QStandardItem* item_value_2 = new QStandardItem(QString(value));
    templist.append(item_value_0);
    templist.append(item_value_1);
    templist.append(item_value_2);
    return templist;
}

QList<QStandardItem*> ToJson_UI_TreeView::createKey(const QString key)
{
    QList<QStandardItem*> templist;
    QStandardItem*  item_key_0 = new QStandardItem(QIcon(":/K.png"), QString(QStringLiteral("键")));
    QStandardItem*  item_key_1 = new QStandardItem(QString(key));
    QStandardItem*  item_key_2 = new QStandardItem(QString(""));
    templist.append(item_key_0);
    templist.append(item_key_1);
    templist.append(item_key_2);
    return templist;
}

QList<QStandardItem*> ToJson_UI_TreeView::createArray(const QString array)
{
    QList<QStandardItem*> templist;
    QStandardItem* item_array_0 = new QStandardItem(QIcon(":/A.png"), QString(QStringLiteral("数组")));
    QStandardItem* item_array_1 = new QStandardItem(QString(array));
    QStandardItem* item_array_2 = new QStandardItem(QString(""));
    templist.append(item_array_0);
    templist.append(item_array_1);
    templist.append(item_array_2);
    return templist;
}

QList<QStandardItem*> ToJson_UI_TreeView::createObject(const QString object)
{
    QList<QStandardItem*> templist;
    QStandardItem* item_object_0 = new QStandardItem(QIcon(":/O.png"), QString(QStringLiteral("对象")));
    QStandardItem* item_object_1 = new QStandardItem(QString(object));
    QStandardItem* item_object_2 = new QStandardItem(QString(""));
    templist.append(item_object_0);
    templist.append(item_object_1);
    templist.append(item_object_2);
    return templist;
}



