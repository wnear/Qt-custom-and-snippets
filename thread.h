#pragma once
#include <QObject>

class ThreadOjbect : public QObject
{
    Q_OBJECT

public:
    ThreadOjbect(QObject *parent = nullptr);
    //~ThreadOjbect(){}
public slots:
    void demorun();
    void reftest_run(const QString &x);
private:

};


class ThreadTest {
    void thread_test1();
    void thread_test2();

};


