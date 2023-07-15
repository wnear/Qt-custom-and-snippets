#include "mainwindow.h"
#include "viewdelegate.h"

#include "listwidget.h"
#include "graphotowidget.h"
#include "textbrowser.h"


MainWindow::MainWindow() : QMainWindow(nullptr) {
    this->setCentralWidget(new GraphotoWidget(this));
    // this->setCentralWidget(new TextBrowser(this));
}

