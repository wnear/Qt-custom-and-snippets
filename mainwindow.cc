#include "mainwindow.h"
#include "viewdelegate.h"

#include <QListView>
#include <QStringListModel>
#include <QMutex>
#include <QMutexLocker>
#include <QThread>
#include <QTimer>
#include <QDebug>

#include <QLabel>
#include <QProcess>
#include <QPixmap>
#include <QMenu>

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

QMutex lock;

auto changelambda() {
    QMutexLocker x(&lock);
    return []() {
        qDebug() << "changelambda";
        QThread::currentThread()->sleep(3);
    };
}

QStringList listdir() {
    QProcess a;
    a.start("unrar", {"vt", "/home/bill/Documents/b.cbr"});
    auto res = a.waitForFinished(300000);
    qDebug() << "finished: " << res;
    QByteArray s;
    QString text;
    s = a.readAllStandardOutput();
    text.append(s);

    QStringList files;
    QString fn;
    bool isList{false};
    for (auto s : text.split("\n")) {
        auto l = s.trimmed();
        if (l.startsWith("Details")) {
            isList = true;
            continue;
        }
        if (isList) {
            auto fnPattern = QStringLiteral("Name: ");
            if (l.startsWith(fnPattern)) {
                fn = l.mid(fnPattern.size());
                qDebug() << fn;
                files.push_back(fn);
            }
        }
    }
    return files;
}

QPixmap getPicture(QString filename) {
    QPixmap img;
    QProcess a;
    qDebug() << filename;
    // a.start("unrar", {"p", "-inul", "-@", "--", "/home/bill/Documents/b.cbr",
    // filename});
    auto res = a.waitForFinished();
    auto out = a.readAllStandardOutput();
    res = img.loadFromData(out);
    if (res == false) {
    }

    return img;
}

MainWindow::MainWindow() : QMainWindow(nullptr) {
    qDebug() << __FILE__ << __LINE__;
    qDebug() << this->thread();
    auto view = new QListView(this);
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    auto model = new QStringListModel(this);
    model->setStringList({"hello", "world", "number 2", "number 1"});
    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view, &QWidget::customContextMenuRequested, [this, view](auto &&pos) {
        auto menu = new QMenu;
        menu->addAction("test");
        menu->addAction("knew", [this, view]() {
            auto selectionmodel = view->selectionModel();
            auto is = selectionmodel->selectedIndexes();
            //sort indexes with  x.row() from big to small.
            std::sort(is.begin(), is.end(),
                      [](auto &&l, auto &&r) { return l.row() > r.row(); });
            auto model = view->model();
            for (auto idx : is) {
                model->removeRow(idx.row());
            }
        });

        menu->exec(mapToGlobal(pos));
    });
    // view->setItemDelegate(delegate);
    // view->installEventFilter(delegate);
    // view->hide();

    // auto label = new QLabel(this);
    // auto files = listdir();

    // auto img = getPicture(files[0]);
    // label->setPixmap(img);
    this->setCentralWidget(view);

    // this->thread_test1();
    // this->thread_test2();
    // auto demo = changelambda();
    // demo();
    // demo();
}

void MainWindow::thread_test2() {
    QString a = "world";
    QString b = "random";
}

void MainWindow::thread_test1() {
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
