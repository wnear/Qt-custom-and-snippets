#include "graphotowidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDir>
#include <QDebug>

PhotoItem::PhotoItem(QGraphicsItem *parent) : QGraphicsObject(parent) {
    this->setFlags(QGraphicsItem::ItemIsMovable);
    m_filelist = QDir("/home/bill/Pictures").entryInfoList({"*.png", "*.jpg"});
    next();
}

void PhotoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
    painter->drawPixmap(m_pixmap.rect(), m_pixmap);
}

void PhotoItem::setImage(const QString &file) { assert(0); }

void PhotoItem::next() {
    m_index++;
    if (m_index == m_filelist.size()) m_index = 0;
    m_pixmap = QPixmap::fromImage(QImage(m_filelist[m_index].absoluteFilePath()));
    assert(!m_pixmap.isNull());
    emit photoChanged();
}
void PhotoItem::prev() {
    m_index--;
    if (m_index == -1) m_index = m_filelist.size()-1;
    m_pixmap = QPixmap::fromImage(QImage(m_filelist[m_index].absoluteFilePath()));
    assert(!m_pixmap.isNull());
    emit photoChanged();
}

QRectF PhotoItem::boundingRect() const { return m_pixmap.rect(); }

class GraphicsView : public QGraphicsView {
  public:
    using QGraphicsView::QGraphicsView;

  protected:
    // void resizeEvent(QResizeEvent *) override
    // {}
};

//TODO:
//0. auto scale. (scale to best view.)
//  1.1 size with value.
//  1.2 size with hidth/weight of item.
//0. draw frame and shadow around the single page.
//1. use item as layoutitem, (two-page, or continuous mode)
//2. put qwidget in view. (e.g. put qtext, in qgraphics)
//4. drag item. (look around)
//5. parent-item relationship's existence.
//
GraphotoWidget::GraphotoWidget(QWidget *parent) : QWidget(parent) {
    this->setLayout(new QVBoxLayout);

    QString imgpath = "";
    auto *photo = new PhotoItem;

    photo->setPos(0, 0);

    auto scene = new QGraphicsScene(0, 0, 400, 400);
    scene->addItem(photo);
    scene->setSceneRect(photo->boundingRect());
    photo->setPos(0, 0);
    // photo->setPos(50, 50);
    // scene->addText("hello world");

    //! [1]
    //! [2]
    // GraphicsView view(&scene);
    auto *view = new GraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setBackgroundBrush(QColor(230, 200, 167));
    view->setWindowTitle("Drag and Drop Robot");
    // view->scale(1.1, 1.1);
    view->show();

    {
        auto widget = new QWidget;
        auto lay = new QHBoxLayout(widget);
        this->layout()->addWidget(widget);
        auto btn1 = new QPushButton("next");
        auto btn2 = new QPushButton("prev");
        auto btn3 = new QPushButton("zoom-in");
        auto btn4 = new QPushButton("zoom-out");
        lay->addWidget(btn1);
        lay->addWidget(btn2);
        lay->addWidget(btn3);
        lay->addWidget(btn4);
        connect(btn1, &QPushButton::clicked, photo, &PhotoItem::next);
        connect(btn2, &QPushButton::clicked, photo, &PhotoItem::prev);
        connect(photo, &PhotoItem::photoChanged, this, [=]() {
            scene->setSceneRect(photo->boundingRect());
            view->resetTransform();
            scene->update();
        });

        connect(btn3, &QAbstractButton::clicked, this,
                [this, view]() { view->scale(1.1, 1.1); });
        connect(btn4, &QAbstractButton::clicked, this, [this, view]() {
            view->scale(0.8, 0.8);

        });
    }

    this->layout()->addWidget(view);
}

void GraphotoWidget::setScale(float incr) {
    m_scale += incr;
    if (m_scale < 0.1) m_scale = 0.1;
}

void GraphotoWidget::reset() {

}

