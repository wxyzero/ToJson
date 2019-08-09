#include "tojson.h"

ToJson::ToJson(QObject *parent) : QObject(parent)
{
    m_pUI = new ToJson_UI;
    m_pTreeView = m_pUI->getTreeView();

    connect(m_pUI, &ToJson_UI::signal_UI_Open, this, &ToJson::setTxtFileName);
    connect(m_pUI, &ToJson_UI::signal_UI_Convert, this, &ToJson::convertTxt2Json);
}

void ToJson::setTxtFileName(QString fileName)
{
    m_strTxtFileName = fileName;

    this->refreshUI();
}

void ToJson::convertTxt2Json()
{    
    QStringList tempList;
    if(!readTxt(tempList))
        return;

    QString tempJson;
    if(!responseTxt(tempList, tempJson))
        return;

    if(!writeJson(tempJson))
        return;
}

bool ToJson::readTxt(QStringList &txtList)
{
    if(m_strTxtFileName.isEmpty())
        return false;

    QFile file;
    file.setFileName(m_strTxtFileName);

    //打开文件
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QStringList tempList;
    QTextStream stream(&file);
    QString line;
    do
    {
        line = stream.readLine();
        if(!line.isEmpty())
            tempList.append(line);
    }
    while(!line.isEmpty());

    if(tempList.isEmpty())
        return false;

    file.close();

    txtList = tempList;
    return true;
}

bool ToJson::responseTxt(QStringList txtList, QString &strJson)
{
    if(txtList.isEmpty())
        return false;

    if(!m_pTreeView->getItem()->child(0))
        return false;

    QStandardItem* childItem = dynamic_cast<QStandardItem*>(m_pTreeView->getItem()->child(0));
    if(childItem->text() != QString(QStringLiteral("数组")))
        return false;


    QStringList templist = txtList;
    QJsonArray json;

    for(int i=0; i<templist.size(); i++)
    {
        QStringList pieces = QString(templist[i]).split("\t", QString::SkipEmptyParts);
        json.append(getValue_Json(childItem, pieces));
    }

    QJsonDocument tDocument;
    tDocument.setArray(json);
    QByteArray byteArray = tDocument.toJson(QJsonDocument::Compact); //QJsonDocument::Indented
    strJson = QString(byteArray);

    return true;
}

bool ToJson::writeJson(QString strJson)
{
    QString strTemp = m_strTxtFileName;
    QString strJsonFileName = strTemp.remove(".txt") + ".json";

    QFile file;
    file.setFileName(strJsonFileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << strJson;

    return true;
}

void ToJson::refreshUI()
{
    m_pUI->setStatusBarTxt(m_strTxtFileName);
}


QJsonValue ToJson::getValue_Json(QStandardItem *parentItem, QStringList list)
{
    QJsonValue value;
    QJsonObject object;
    int rowCount = parentItem->rowCount();
    for(int i=0; i<rowCount; i++)
    {
        QStandardItem* childItem = parentItem->child(i);
        if(childItem->text() == QString(QStringLiteral("键")))
        {
            value = getValue_Key(childItem, list);
        }
        else if(childItem->text() == QString(QStringLiteral("数组")))
        {
            value = getValue_Array(childItem, list);
        }
        else if(childItem->text() == QString(QStringLiteral("对象")))
        {
            value = getValue_Object(childItem, list);
        }
        else if(childItem->text() == QString(QStringLiteral("值")))
        {
            value = getValue_Value(childItem, list);
        }
    }
    if(value.isNull())
    {
        return object;
    }
    else
    {
        return value;
    }
}

QJsonValue ToJson::getValue_Value(QStandardItem *item, QStringList list)
{
    QJsonValue value;
    QModelIndex childIndex = item->index();
    QVariant variant = childIndex.sibling(childIndex.row(), childIndex.column() + 2).data();
    if(list.isEmpty())
    {
        value = variant.toString();
    }
    else
    {
        value = list.value(variant.toInt()-1);
    }
    return value;
}

QJsonValue ToJson::getValue_Key(QStandardItem *item, QStringList list)
{
    QJsonValue value;
    int rowCount = item->rowCount();
    for(int i=0; i<rowCount; i++)
    {
        QStandardItem* childItem = item->child(i);
        if(childItem->text() == QString(QStringLiteral("值")))
        {
            value = getValue_Value(childItem, list);
        }
        else if(childItem->text() == QString(QStringLiteral("对象")))
        {
            value = getValue_Object(childItem, list);
        }
        else if(childItem->text() == QString(QStringLiteral("数组")))
        {
            value = getValue_Array(childItem, list);
        }
    }
    return value;
}

QJsonValue ToJson::getValue_Array(QStandardItem *item, QStringList list)
{
    QJsonArray array;
    int rowCount = item->rowCount();
    for(int i=0; i<rowCount; i++)
    {
        QStandardItem* childItem = item->child(i);
        if(childItem->text() == QString(QStringLiteral("值")))
        {
            QJsonValue value = getValue_Value(childItem, list);
            array.append(value);
        }
        else if(childItem->text() == QString(QStringLiteral("对象")))
        {
            QJsonValue value = getValue_Object(childItem, list);
            array.append(value);
        }
        else if(childItem->text() == QString(QStringLiteral("数组")))
        {
            QJsonValue value = getValue_Array(childItem, list);
            array.append(value);
        }
    }
    return array;
}

QJsonValue ToJson::getValue_Object(QStandardItem *item, QStringList list)
{
    QJsonObject object;
    int rowCount = item->rowCount();
    for(int i=0; i<rowCount; i++)
    {
        QStandardItem* childItem = item->child(i);
        QModelIndex childIndex = childItem->index();
        if(childItem->text() == QString(QStringLiteral("键")))
        {
            object.insert(childIndex.sibling(childIndex.row(), childIndex.column() + 1).data().toString(), getValue_Key(childItem, list));
        }
    }
    return object;
}
