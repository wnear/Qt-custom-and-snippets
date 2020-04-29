#ifndef PLAINTEXTWITHDROP_H
#define PLAINTEXTWITHDROP_H
#include <QPlainTextEdit>
#include <QWidget>

class plaintextwithdrop: public QPlainTextEdit
{
    Q_OBJECT
public:
    plaintextwithdrop(QWidget *parent = NULL){}
protected:
    void dropEvent(QDropEvent *event);
};

#endif // PLAINTEXTWITHDROP_H
