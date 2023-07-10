#pragma once

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsView>
#include <QGraphicsScene>

class PhotoWidget : public QGraphicsObject {
    Q_OBJECT
  public:
    PhotoWidget(QGraphicsItem *parent = nullptr): QGraphicsObject(parent) {}

    QRectF boundingRect() const override{return {};}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override{}
  private:
};

class GraphotoWidget : public QWidget {
    Q_OBJECT
  public:
    GraphotoWidget(QWidget *parent = nullptr);

  private:
};
