#include "viewdelegate.h"
#include <QDebug>
#include <QEvent>
#include <QPainter>


int offset = 0;
int focusIndex = -1;

void ViewDelegate::paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &index) const {
    auto newOpt{opt};
    if(focusIndex == index.row()){
        newOpt.rect.setHeight(100);
    } else {
        newOpt.rect.setHeight(50);
    }

    QString content = index.data().toString();
    if(content.startsWith("number")) {
    } else {
    }
    p->setClipRect(newOpt.rect );
    p->drawText(newOpt.rect, content);
    //QStyledItemDelegate::paint(p, newOpt, index);
}

QSize ViewDelegate::sizeHint(const QStyleOptionViewItem &opt, const QModelIndex &index) const {
    if(index.row() == focusIndex)
        return QSize(100+offset, 100+offset);
    else return QSize(50, 50);
}

bool ViewDelegate::editorEvent(QEvent *evt, QAbstractItemModel *model,  const QStyleOptionViewItem &opt, const QModelIndex &index) {
    return QStyledItemDelegate::editorEvent(evt, model, opt, index);

    qDebug()<<"editor event: "<<evt->type();
    switch (evt->type()){
        case QEvent::MouseButtonPress:
        focusIndex = index.row();
            break;
        case QEvent::FocusIn:
            qDebug()<<"focus in";
            break;
        case QEvent::FocusOut:
            qDebug()<<"focus out";
            break;
        default:
        break;
    }
    return QStyledItemDelegate::editorEvent(evt, model, opt, index);
}

bool ViewDelegate::eventFilter(QObject *obj, QEvent *ev) {
    return QStyledItemDelegate::eventFilter(obj, ev);

    switch(ev->type()){
    case QEvent::Polish:
        break;
    default:
        qDebug()<<ev->type();
        break;
    }
    ev->accept();
    return QStyledItemDelegate::eventFilter(obj, ev);
}
