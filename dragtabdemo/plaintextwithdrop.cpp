#include "plaintextwithdrop.h"
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QObjectUserData>
#include <QObject>

void plaintextwithdrop::dropEvent(QDropEvent *event)
{
    qDebug()<<"drop event";
//    event->
    qDebug()<< event->mimeData()->text();
    return QPlainTextEdit::dropEvent(event);

}
