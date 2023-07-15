
#include "regex.h"
#include <QRegularExpressionMatch>
#include <QDebug>
void Regex::test() {
    QString a = "this is 00:01:03";
    QRegularExpression x("(\\d{2}:\\d{2}:\\d{2})");

    a.replace(x, "<a href='positions://to?#\\1'>\\1</a>");
    qDebug()<< "result: a = " << a;

}

