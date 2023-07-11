#include "mainwindow.h"
#include "viewdelegate.h"

#include "listwidget.h"
#include "graphotowidget.h"


MainWindow::MainWindow() : QMainWindow(nullptr) {
    this->setCentralWidget(new GraphotoWidget(this));

}

