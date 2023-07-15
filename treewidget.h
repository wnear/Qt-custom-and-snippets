
#pragma once

#include <QWidget>
#include <QMap>
#include "dataitem.h"

class TreeWidget : public QWidget {
    Q_OBJECT

  public:
    TreeWidget(QWidget *parent = nullptr);
    void populateData();

  private:
    QMap<QString, ActorItem *> m_data;
};
