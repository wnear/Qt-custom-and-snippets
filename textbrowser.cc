#include "textbrowser.h"

#include <QDebug>
#include <QTextBrowser>
#include <QTextCursor>
#include <QVBoxLayout>

#include <QRegularExpression>

TextBrowser::TextBrowser(QWidget *parent) : QWidget(parent) {
    this->setLayout(new QHBoxLayout);

    auto *browser = new QTextBrowser(this);
    auto cursor = browser->textCursor();
    cursor.beginEditBlock();

    QTextCharFormat normalFormat = cursor.charFormat();
    normalFormat.setFontPointSize(10);

    QTextCharFormat titleFormat = normalFormat;
    titleFormat.setFontPointSize(normalFormat.fontPointSize() + 2);
    qDebug() << normalFormat.fontPointSize();
    titleFormat.setFontWeight(QFont::Bold);
    // highlightedFormat.setBackground(Qt::yellow);

    cursor.insertText("hello\n", titleFormat);
    cursor.insertText("world\n", normalFormat);

    QString text_demo = "this is 00:01:03";

    QRegularExpression time_pattern("(\\d{2}:\\d{2}:\\d{2})");
    const QString replacement = "<a href='positions://to?#\\1'>\\1</a>";

    text_demo.replace(time_pattern, replacement);
    qDebug() << "repalce result:" << text_demo;

    cursor.insertHtml(text_demo);
    cursor.endEditBlock();

    this->layout()->addWidget(browser);
    browser->setOpenLinks(false);
    browser->setOpenExternalLinks(false);
    connect(browser, &QTextBrowser::anchorClicked, this, [](const QUrl &url) {
        qDebug() << "scheme:" << url.scheme();
        qDebug() << "host:" << url.host();
        qDebug() << "fragment:" << url.fragment();
    });
}
