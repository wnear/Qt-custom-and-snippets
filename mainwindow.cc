#include "mainwindow.h"
#include "viewdelegate.h"

#include "listwidget.h"
#include "graphicspageview.h"
#include "textbrowser.h"
#include "treewidget.h"
#include "regex.h"


MainWindow::MainWindow() : QMainWindow(nullptr) {
    this->setCentralWidget(new GraphicsPageView(this));
    // this->setCentralWidget(new TextBrowser(this));
    // Regex::test();
    // this->setCentralWidget(new TreeWidget(this));
    // this->setCentralWidget(new TextBrowser(this));

}

