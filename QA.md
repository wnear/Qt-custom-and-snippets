1. Q: How to remove the border from a QWidget like QPushbutton?

A: use `setStyleSheet` to set as `border:none;`

Qss reference:
[Qt Style Sheets Examples](https://doc.qt.io/qt-5/stylesheet-examples.html)
[Qt Style Sheets Reference](https://doc.qt.io/qt-5/stylesheet-reference.html)

2. Q: right way to use external library

A: use `INCLUDEPATH += library_header_path` and `LIBS += -Lbinarydir -llibname`.
