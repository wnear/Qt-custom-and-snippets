#include "mainwindow.h"
#include "viewdelegate.h"

#include "listwidget.h"
#include "graphotowidget.h"
#include "textbrowser.h"
#include "treewidget.h"
#include "regex.h"


MainWindow::MainWindow() : QMainWindow(nullptr) {
    // this->setCentralWidget(new GraphotoWidget(this));
    this->setCentralWidget(new TextBrowser(this));
    // Regex::test();
    // this->setCentralWidget(new TreeWidget(this));
    // this->setCentralWidget(new TextBrowser(this));

}

