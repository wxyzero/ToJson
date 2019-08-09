#ifndef TOJSON_H
#define TOJSON_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "tojson_ui.h"
#include "tojson_ui_treeview.h"

class ToJson : public QObject
{
    Q_OBJECT
public:
    explicit ToJson(QObject *parent = nullptr);

signals:

public slots:
    //保存txt文件名
    void setTxtFileName(QString fileName);

    //转换
    void convertTxt2Json();

    //读取Txt中的内容，并保存在QStringList中
    bool readTxt(QStringList &txtList);

    //解析Txt中的内容(QStringList格式)，并按照用户指定格式转换为Json格式字符串
    bool responseTxt(QStringList txtList, QString &strJson);

    //将转换后的Json写入文件
    bool writeJson(QString strJson);

    //更新状态栏显示
    void refreshUI();

public:
    ToJson_UI* getUI(){return m_pUI;}

public:
    QJsonValue getValue_Key(QStandardItem *item, QStringList list = QStringList());
    QJsonValue getValue_Array(QStandardItem *item, QStringList list = QStringList());
    QJsonValue getValue_Object(QStandardItem *item, QStringList list = QStringList());
    QJsonValue getValue_Value(QStandardItem *item, QStringList list = QStringList());
    QJsonValue getValue_Json(QStandardItem *parentItem, QStringList list = QStringList());

public:
    QString                 m_strTxtFileName;

    ToJson_UI*              m_pUI;
    ToJson_UI_TreeView*     m_pTreeView;
};

#endif // TOJSON_H
