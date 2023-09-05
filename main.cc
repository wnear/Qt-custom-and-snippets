#include "mainwindow.h"
#include "struct.h"
#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <iostream>

int listrar() {
    QProcess a;
    a.start("unrar", {"vt", "/home/bill/Documents/a.cbr"});
    auto res = a.waitForFinished(300000);
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
                files.push_back(fn);
            }
        }
    }
    for (auto f : files) {
    }

    return 0;
}

void testconf() {
#ifdef PROGRAMX
    std::cout << "has defined PROGRAMX";
#else
    std::cout << "not has defined PROGRAMX";
#endif
    std::cout << std::endl;
#ifdef PROGRAM_VERSION

    std::cout << "version:" << PROGRAM_VERSION;
#else
    std::cout << "version not specified";
#endif
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    testconf();
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    QObject::connect(&w, &QMainWindow::iconSizeChanged, &w, []() {});
    return app.exec();
}
