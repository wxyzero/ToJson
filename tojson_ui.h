#ifndef TOJSON_UI_H
#define TOJSON_UI_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "tojson_ui_treeview.h"

class ToJson_UI : public QMainWindow
{
    Q_OBJECT
public:
    explicit ToJson_UI(QWidget *parent = nullptr);

signals:
    void signal_UI_Open(QString fileName);      //将选择的文件名作为信号发出
    void signal_UI_Convert();                   //发出转换信号

public slots:
    void open();                        //打开按钮槽函数：打开文件选择对话框，选择需要转化的文件
    void convert();                     //转化按钮槽函数
    void setStatusBarTxt(QString str);  //设置状态栏中的文字

public slots:
    ToJson_UI_TreeView*     getTreeView(){return m_pTreeView;}  //返回表格

public:
    QLabel*                 m_pLabel;       //负责在状态栏中显示文字
    ToJson_UI_TreeView*     m_pTreeView;    //表格
};

#endif // TOJSON_UI_H
