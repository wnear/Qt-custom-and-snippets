#include "textbrowser.h"

#include <QDebug>
#include <QTextBrowser>
#include <QTextCursor>
#include <QVBoxLayout>

TextBrowser::TextBrowser(QWidget *parent) : QWidget(parent) {
    this->setLayout(new QHBoxLayout);

    auto browser = new QTextBrowser(this);
    auto cursor = browser->textCursor();
    cursor.beginEditBlock();

    QTextCharFormat normalFormat = cursor.charFormat();
    normalFormat.setFontPointSize(10);

    QTextCharFormat titleFormat = normalFormat;
    titleFormat.setFontPointSize(normalFormat.fontPointSize()+2);
    qDebug()<<normalFormat.fontPointSize();
    titleFormat.setFontWeight(QFont::Bold);
    // highlightedFormat.setBackground(Qt::yellow);


    cursor.insertText("hello\n", titleFormat);
    cursor.insertText("world", normalFormat);
    cursor.endEditBlock();

    this->layout()->addWidget(browser);
}

