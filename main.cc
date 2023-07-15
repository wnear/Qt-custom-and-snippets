#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QDebug>

int listrar()
{
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
    for (auto s: text.split("\n")){
        auto l = s.trimmed();
        if(l.startsWith("Details")){
            isList = true;
            continue;
        }
        if(isList){
            auto fnPattern = QStringLiteral("Name: ");
            if (l.startsWith(fnPattern)){
                fn = l.mid(fnPattern.size());
                files.push_back(fn);
            }
        }
    }
    for(auto f: files){

    }

    return 0;

}


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    QObject::connect(&w, &QMainWindow::iconSizeChanged,&w, [](){} );
    return app.exec();
}

