#pragma  once
#include <QMainWindow>
#include <QDebug>

class MainWindow: public QMainWindow
{
public:
    MainWindow();
    void thread_test1();
    void thread_test2();
    ~MainWindow(){}

private:

};

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



