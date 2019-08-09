#include "tojson_ui.h"

ToJson_UI::ToJson_UI(QWidget *parent) : QMainWindow(parent)
{
    //菜单按钮
    QAction* action_Open = new QAction(QIcon(QString(":/open.png")), QString(QStringLiteral("打开文件")));
    QAction* action_Convert = new QAction(QIcon(QString(":/process.png")), QString(QStringLiteral("转换")));
    menuBar()->addAction(action_Open);
    menuBar()->addAction(action_Convert);

    //状态栏中的文字显示
    m_pLabel = new QLabel(QString("File :"));
    statusBar()->addWidget(m_pLabel);

    //表格
    m_pTreeView = new ToJson_UI_TreeView;
    this->setCentralWidget(m_pTreeView);
    this->resize(500, 500);

    connect(action_Open, &QAction::triggered, this, &ToJson_UI::open);
    connect(action_Convert, &QAction::triggered, this, &ToJson_UI::convert);
}

void ToJson_UI::open()
{
    //选择文件
    QString path = QFileDialog::getOpenFileName(NULL, QStringLiteral("Open File"), ".", QStringLiteral("Text Files(*.txt)"));

    //将文件名作为信号发出
    emit signal_UI_Open(path);
}

void ToJson_UI::convert()
{
    //确认是否转换
    int flag = QMessageBox::question(this, QStringLiteral("注意"), QStringLiteral("确定开始转化？"));
    if(flag != QMessageBox::Yes)
        return;

    //发出转换信号
    emit signal_UI_Convert();
}

void ToJson_UI::setStatusBarTxt(QString str)
{
    m_pLabel->setText("File :" + str);
}
