#pragma once

#include <random>

#include <QStyledItemDelegate>

class ViewDelegate: public QStyledItemDelegate
{
    public:
        ViewDelegate(){}
        void paint(QPainter *p, const QStyleOptionViewItem &, const QModelIndex &) const override;
        QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override;
    protected:
        bool editorEvent(QEvent *evt, QAbstractItemModel *,  const QStyleOptionViewItem &, const QModelIndex &) override;
        bool eventFilter(QObject *obj, QEvent *ev) override;

      protected:
};
        
