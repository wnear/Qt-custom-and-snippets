#pragma once

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileInfo>

class PhotoItem : public QGraphicsObject {
    Q_OBJECT
  public:
    PhotoItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void setImage(const QString &file);
    void next();
    void prev();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

  signals:
    void photoChanged();

  private:
    int m_index{0};
    QFileInfoList m_filelist{};
    QPixmap m_pixmap;
};

class GraphotoWidget : public QWidget {
    Q_OBJECT
  public:
    GraphotoWidget(QWidget *parent = nullptr);
    void setScale(float incr);

  private:
    float m_scale = 1.0;
};
