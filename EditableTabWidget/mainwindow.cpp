#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabBar>
#include <QStackedWidget>
#include <QTextEdit>
#include "qtabwidgetwithcontrol.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    auto *x = new QTabWidgetWithControl(this);
    auto msg = QStringList{"hello"};
    for(auto i: msg){
        x->addTab(new QTextEdit, i);
    }
    auto *y = new WidgetGenerator;
    x->setupMenuAndActions(y->m_map);

    this->setCentralWidget(x);
}

MainWindow::~MainWindow()
{

}
