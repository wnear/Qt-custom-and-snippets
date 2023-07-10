#include "graphotowidget.h"
#include <QHBoxLayout>

class GraphicsView : public QGraphicsView
{
public:
    using QGraphicsView::QGraphicsView;

protected:
    void resizeEvent(QResizeEvent *) override
    {
    }
};

GraphotoWidget::GraphotoWidget(QWidget *parent):QWidget(parent) {
    this->setLayout(new QHBoxLayout);

    QString imgpath = "";
    auto *photo = new PhotoWidget;


    auto scene = new QGraphicsScene(-200, -200, 400, 400);
    scene->addItem(photo);
    scene->addText("hello world");

//! [1]
//! [2]
    // GraphicsView view(&scene);
    auto *view = new GraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setBackgroundBrush(QColor(230, 200, 167));
    view->setWindowTitle("Drag and Drop Robot");
    view->show();

    this->layout()->addWidget(view);
}
