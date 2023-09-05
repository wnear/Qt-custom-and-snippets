#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dragtab.h"
#include "plaintextwithdrop.h"
#include <QTextEdit>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    QSplitter *p = new QSplitter(this);
    m_pTabWidget = new myTabWidget(this);
    //m_pTabWidget->setMovable(true);
    m_pTabWidget->setTabsClosable(true);
//    m_pTabWidget->setTabShape(QTabWidget::Triangular);
    //添加4个tab页
    m_pTabWidget->addTab(new QTextEdit,"eidt 1");
    m_pTabWidget->addTab(new QTextEdit,"eidt 2");
    m_pTabWidget->addTab(new QTextEdit,"eidt 3");
    m_pTabWidget->addTab(new QTextEdit,"eidt 4");
    myTabWidget *m_pTabWidget1 = new myTabWidget(this);
    //m_pTabWidget1->setMovable(true);
    m_pTabWidget1->setTabsClosable(true);
//    m_pTabWidget1->setTabShape(QTabWidget::Triangular);
    //添加4个tab页
    m_pTabWidget1->addTab(new QTextEdit,"eidt 1");
    m_pTabWidget1->addTab(new QTextEdit,"eidt 2");
    m_pTabWidget1->addTab(new QTextEdit,"eidt 3");
    m_pTabWidget1->addTab(new QTextEdit,"eidt 4");
//    m_pTabWidget->setMovable(true);
//    m_pTabWidget1->setMovable(true);
    p->addWidget(m_pTabWidget);
    p->addWidget(m_pTabWidget1);
    setCentralWidget(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}

