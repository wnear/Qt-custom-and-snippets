
#include "thread.h"
#include <QDebug>
#include <QThread>
#include <QTimer>

ThreadOjbect::ThreadOjbect(QObject *parent) : QObject(parent) {}

void ThreadOjbect::demorun() {
    for (int i = 0; i < 3; i++) {
        qDebug() << QThread::currentThread() << "running" << i
                 << "objname:" << objectName();
        this->thread()->msleep(100);
    }
}

void ThreadOjbect::reftest_run(const QString &x) {
    for (int i = 0; i < 3; i++) {
        qDebug() << QThread::currentThread() << x;
        this->thread()->msleep(100);
    }
}

void ThreadTest::thread_test1() {
    // test how to run obj::methos in its thread context.
    auto thread = new QThread;

    auto obj = new ThreadOjbect;
    obj->setObjectName("obj a");

    auto obj_b = new ThreadOjbect;
    obj_b->setObjectName("obj b");

    obj_b->moveToThread(thread);
    obj->moveToThread(thread);

    thread->start();
    obj->demorun();

    // 1. call.
    QString a = "hello";
    QMetaObject::invokeMethod(obj, "reftest_run", Q_ARG(QString, a));
    a = "world";
    const int test = 2;
    switch (test) {
        case 0:
            obj->demorun();
            break;
        case 1:
            QMetaObject::invokeMethod(obj, "demorun");
            break;
        case 2:
            QTimer::singleShot(0, obj, &ThreadOjbect::demorun);
            QTimer::singleShot(0, obj_b, &ThreadOjbect::demorun);
            break;
        default:
            break;
    }

    // QTimer detail usage.
    auto timer_thread = new QThread;
    auto timer_obj = new QObject;
    timer_obj->moveToThread(timer_thread);
    timer_thread->start();
    QTimer::singleShot(0, timer_obj, [obj]() {
        auto thread = obj->thread();
        while (1) {
            if (thread->isRunning()) {
                qDebug() << QThread::currentThread() << "doing watching: "
                         << "running";
            } else {
                qDebug() << QThread::currentThread() << "doing watching: "
                         << "not running";
                break;
            }
            QThread::currentThread()->msleep(100);
        }
    });

    QTimer::singleShot(0, obj_b, [thread]() {
        qDebug() << QThread::currentThread() << "doing quit";
        thread->quit();
    });
    qDebug() << __PRETTY_FUNCTION__ << " Ending";
    obj->deleteLater();
}
