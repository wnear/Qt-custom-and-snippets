
#include "treewidget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStringListModel>

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent) {
    populateData();

    this->setLayout(new QHBoxLayout);
    auto *view = new QTreeView(this);
    auto *model = new QStringListModel;
    model->setStringList({"hello", "world"});
    view->setModel(model);

    this->layout()->addWidget(view);
}

void TreeWidget::populateData() {
    m_data.insert("hi", nullptr);
}

