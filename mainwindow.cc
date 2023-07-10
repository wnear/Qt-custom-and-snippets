#include "mainwindow.h"
#include "viewdelegate.h"

#include "listview.h"
#include "graphotowidget.h"


MainWindow::MainWindow() : QMainWindow(nullptr) {
    this->setCentralWidget(new GraphotoWidget(this));

}

