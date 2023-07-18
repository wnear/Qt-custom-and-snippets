#include "graphotowidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDir>
#include <QDebug>

#include <QCoreApplication>
PhotoItem::PhotoItem(QGraphicsItem *parent) : QGraphicsObject(parent) {
    this->setFlags(QGraphicsItem::ItemIsMovable);
    m_filelist = QDir("/home/bill/Pictures").entryInfoList({"*.png", "*.jpg"});
    next();
}

void PhotoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
    painter->drawPixmap(m_pixmap.rect(), m_pixmap);

    // line thickness should depend on the scale.
    painter->setPen(QPen(Qt::black, 1 / m_scale));
    painter->drawRect(m_pixmap.rect());

    auto shadow_real = m_padding_shadow / m_scale;
    auto p1 = this->boundingRect().topRight();
    auto p2 = this->boundingRect().bottomRight();
    auto p3 = this->boundingRect().bottomLeft();
    QGradientStops stops;
    stops << QGradientStop(0.0, Qt::black);
    stops << QGradientStop(1.0, m_board_bgcolor);

    QLinearGradient gradient(this->boundingRect().topRight(),
                             this->boundingRect().topRight() + QPointF(shadow_real, 0));
    painter->setPen(Qt::NoPen);
    gradient.setStops(stops);
    painter->setBrush(QBrush(gradient));
    QPointF points[4] = {
        p1, p1 + QPointF(shadow_real, 1 *shadow_real),
        p2 + QPointF(shadow_real, 1* shadow_real), p2
    };
    painter->drawConvexPolygon(points, 4);

    QLinearGradient gradient2(this->boundingRect().bottomLeft(),
                             this->boundingRect().bottomLeft() + QPointF(0, shadow_real));
    gradient2.setStops(stops);
    painter->setBrush(QBrush(gradient2));
    QPointF points2[4] = {
        p2, p2 + QPointF(shadow_real, 1 *shadow_real),
        p3 + QPointF(shadow_real, 1* shadow_real), p3
    };
    painter->drawConvexPolygon(points2, 4);

    // painter->setBrush(Qt::darkGray);
    // painter->drawRect(m_pixmap.rect());
}

void PhotoItem::setBoardSize(QSize val) { m_board_size = val; }

void PhotoItem::recalScale() {
    auto itemsize = this->boundingRect();

    auto w = itemsize.width();
    auto h = itemsize.height();

    auto tw = m_board_size.width();
    auto th = m_board_size.height();

    auto s1 = (tw - shadowPadding()) / w;
    auto s2 = (th - shadowPadding()) / h;

    auto s = std::min(s1, s2);
    s = std::min(s, m_scaleMax);  // s will not excede 2.0 .

    qDebug() << QString("size:%1 x %2 inside %3 x %4").arg(w).arg(h).arg(tw).arg(th);
    qDebug() << QString("s1:%1, s2:%2, s:%3").arg(s1).arg(s2).arg(s);
    qDebug() << "";

    m_scale = s;
}

double PhotoItem::getScale() { return m_scale; }

void PhotoItem::setImage(const QString &file) { assert(0); }

void PhotoItem::next() {
    m_index++;
    if (m_index == m_filelist.size()) m_index = 0;
    m_pixmap = QPixmap::fromImage(QImage(m_filelist[m_index].absoluteFilePath()));
    recalScale();
    assert(!m_pixmap.isNull());
    emit photoChanged();
}

void PhotoItem::prev() {
    m_index--;
    if (m_index == -1) m_index = m_filelist.size() - 1;
    m_pixmap = QPixmap::fromImage(QImage(m_filelist[m_index].absoluteFilePath()));
    recalScale();
    assert(!m_pixmap.isNull());
    emit photoChanged();
}

QRectF PhotoItem::boundingRect() const { return m_pixmap.rect(); }

// TODO:
// 0. auto scale. (scale to best view.)
//   1.1 size with value.
//   1.2 size with hidth/weight of item.
// 1. draw frame and shadow around the single page.
// 1. use item as layoutitem, (two-page, or continuous mode)
// 2. put qwidget in view. (e.g. put qtext, in qgraphics)
// 4. drag item. (look around)
// 5. parent-item relationship's existence.
//
GraphotoWidget::GraphotoWidget(QWidget *parent) : QWidget(parent) {
    this->setLayout(new QVBoxLayout);

    m_photoItem = new PhotoItem;
    m_photoItem->setPos(0, 0);

    m_scene = new QGraphicsScene(0, 0, 400, 400);
    m_scene->addItem(m_photoItem);
    m_scene->setSceneRect(m_photoItem->boundingRect());
    m_photoItem->setPos(0, 0);
    // scene->addText("hello world");

    m_view = new GraphicsView(m_scene);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_view->setBackgroundBrush(QColor(230, 200, 167));
    m_view->setWindowTitle("Drag and Drop Robot");
    m_view->show();
    // NOTE: a little tricky,  wait for gui inited, then autoscale.
    QCoreApplication::processEvents();
    m_photoItem->setBoardSize(boardSize());
    m_photoItem->setBoardBackground(m_view->backgroundBrush().color());
    m_photoItem->recalScale();
    qDebug() << __LINE__;
    displayInfo();
    // TODO:
    // set item Screen size.

    qDebug() << m_view->backgroundBrush().color();
    autoscale();

    {
        auto widget = new QWidget;
        auto lay = new QHBoxLayout(widget);
        this->layout()->addWidget(widget);
        auto btn1 = new QPushButton("next");
        auto btn2 = new QPushButton("prev");
        auto btn3 = new QPushButton("zoom-in");
        auto btn4 = new QPushButton("zoom-out");
        // auto btn5 = new QPushButton("fit-1");
        // auto btn6 = new QPushButton("fit-2");

        lay->addWidget(btn1);
        lay->addWidget(btn2);
        lay->addWidget(btn3);
        lay->addWidget(btn4);
        // lay->addWidget(btn5);
        // lay->addWidget(btn6);
        connect(btn1, &QPushButton::clicked, m_photoItem, &PhotoItem::next);
        connect(btn2, &QPushButton::clicked, m_photoItem, &PhotoItem::prev);
        connect(m_photoItem, &PhotoItem::photoChanged, this, &GraphotoWidget::autoscale);

        connect(btn3, &QAbstractButton::clicked, this,
                [this]() { m_view->scale(1.1, 1.1); });
        connect(btn4, &QAbstractButton::clicked, this,
                [this]() { m_view->scale(0.9, 0.9); });
    }

    this->layout()->addWidget(m_view);
}

void GraphotoWidget::setScale(float incr) {
    m_scale += incr;
    if (m_scale < 0.1) m_scale = 0.1;
}

void GraphotoWidget::autoscale() {
    auto itemsize = m_photoItem->boundingRect();
    auto s = m_photoItem->getScale();
    m_scene->setSceneRect(itemsize);
    m_view->resetTransform();
    m_view->scale(s, s);
    m_scene->update();
    m_photoItem->setBoardSize(boardSize());
}

void GraphotoWidget::displayInfo() const {
    auto crec = m_view->contentsRect();
    auto rect = m_view->rect();
    auto size = m_view->size();
    qDebug() << QString("contentsRect:") << crec;
    qDebug() << QString("rect:") << rect;
    qDebug() << QString("size:") << size;
}

QSize GraphotoWidget::boardSize() const {
    return {m_view->contentsRect().width() - 2 * m_padding_leftright,
            m_view->contentsRect().height() - 2 * m_padding_topbottom

    };
}
