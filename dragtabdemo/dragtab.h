#ifndef CTABWIDGET_H
#define CTABWIDGET_H
#include <qtabbar.h>
#include <qtabwidget.h>

class myTabBar:public QTabBar
{
    Q_OBJECT

public:
    myTabBar(QWidget *parent):QTabBar(parent){}
    ~myTabBar() = default;

protected:
    void mouseMoveEvent (QMouseEvent *e);

signals:
    void starDragTab(int index);
};

class myTabWidget:public QTabWidget
{
    Q_OBJECT

public:
    myTabWidget(QWidget *parent = NULL);
    ~myTabWidget(){}

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void starDrag(int index);

private:
    myTabBar *m_pTabBar;
};

#endif // CTABWIDGET_H

