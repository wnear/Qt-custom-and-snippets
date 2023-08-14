#include "mainwindow.h"
#include "viewdelegate.h"

#include "listwidget.h"
#include "graphicspageview.h"
#include "textbrowser.h"
#include "treewidget.h"
#include "regex.h"
#include "youdao.h"


MainWindow::MainWindow() : QMainWindow(nullptr) {
    this->setCentralWidget(new PageView(this));
    // YouDaoApi::test();
    // this->setCentralWidget(new TextBrowser(this));
    // Regex::test();
    // this->setCentralWidget(new TreeWidget(this));
    // this->setCentralWidget(new TextBrowser(this));

}

