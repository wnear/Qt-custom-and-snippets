#include "mainwindow.h"
#include "viewdelegate.h"

#include "listview.h"

MainWindow::MainWindow() : QMainWindow(nullptr) {
    this->setCentralWidget(new ListWidget(this));

}

