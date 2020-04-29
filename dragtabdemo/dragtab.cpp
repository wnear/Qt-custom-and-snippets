
#include "dragtab.h"
#include <QMouseEvent>
#include <qevent.h>
#include <qdrag.h>
#include<QMimeData>
#include <QApplication>
#include <QObjectUserData>
#include <QDebug>
#include <QScreen>
#include <QToolTip>

void myTabBar::mouseMoveEvent(QMouseEvent *e)
{
    QString x("hello");
    QToolTip::showText(e->globalPos(), x, this);

    if(!tabRect(this->currentIndex()).contains(e->pos())) {
        emit starDragTab(this->currentIndex());
    }

    return QTabBar::mouseMoveEvent(e);
}

myTabWidget::myTabWidget(QWidget *parent/* = NULL*/):QTabWidget(parent)
{
    m_pTabBar = new myTabBar(this);
    setTabBar(m_pTabBar);
    connect(m_pTabBar,SIGNAL(starDragTab(int)),this,SLOT(starDrag(int)));
    this->setAcceptDrops(true);
}


void myTabWidget::starDrag(int index)
{
    QPixmap pix;
    pix = QGuiApplication::primaryScreen()->grabWindow(this->winId());

    QMimeData *mimeData = new QMimeData;
//    dynamic_cast<QObjectUserData>(this->widget(index))
    mimeData->setUserData(0, (QObjectUserData *)(this->widget(index)));
    this->removeTab(index);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pix.scaled(QSize(200,200)));
    drag->exec();
}


void myTabWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
    event->proposedAction();

    QTabWidget::dragEnterEvent(event);
}

void myTabWidget::dropEvent(QDropEvent *event)
{
    static int moved = 0;
    event->dropAction();
    event->possibleActions();
    event->proposedAction();
    qDebug()<<event->mimeData()->formats();
    QWidget *p = (QWidget *)event->mimeData()->userData(0);
    QObject *pp = event->source();
//    qDebug()<<event->mimeData()->text();
    this->insertTab(this->tabBar()->tabAt(event->pos()), p, QString("edit_n%1").arg(moved++));
    return;
}
