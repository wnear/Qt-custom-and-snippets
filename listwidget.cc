
#include "listwidget.h"
#include <QHBoxLayout>
#include <QStringListModel>
#include <QMenu>
ListWidget::ListWidget(QWidget *parent) :QWidget(parent){
    this->setLayout(new QHBoxLayout);


    auto view = new QListView(this);
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    auto model = new QStringListModel(this);
    model->setStringList({"hello", "world", "number 2", "number 1"});
    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view, &QWidget::customContextMenuRequested, [this, view](auto &&pos) {
        auto menu = new QMenu;
        menu->addAction("test");
        menu->addAction("knew", [this, view]() {
            auto selectionmodel = view->selectionModel();
            auto is = selectionmodel->selectedIndexes();
            //sort indexes with  x.row() from big to small.
            std::sort(is.begin(), is.end(),
                      [](auto &&l, auto &&r) { return l.row() > r.row(); });
            auto model = view->model();
            for (auto idx : is) {
                model->removeRow(idx.row());
            }
        });
        menu->exec(mapToGlobal(pos));
    });
    // view->setItemDelegate(delegate);
    // view->installEventFilter(delegate);
    // view->hide();

    this->layout()->addWidget(view);
}

