#ifndef QTABWIDGETWITHCONTROL_H
#define QTABWIDGETWITHCONTROL_H

#include <QWidget>
#include "widgetgenerator.h"

class QMenu;
class QTabWidgetWithControlPrivate;

class QTabWidgetWithControl : public QWidget
{
    Q_OBJECT
public:
    explicit QTabWidgetWithControl(QWidget *parent = nullptr);
    ~QTabWidgetWithControl();

    int	addTab(QWidget *page, const QString &label);
    int	insertTab(int index, QWidget *page, const QString &label);
    void removeTab(int index);
    void removeTab(QString label);
    int currentIndex() const;

    QWidget *widget(int index) const;
    QWidget *makeTestWidget(QString content);

    void setupMenuAndActions(WidgetGenerator::NameToGenerator_Type &generatorMap);

    QMenu *menu();
signals:
    void currentChanged(int index);
public slots:
    void setCurrentIndex(int index);
private:
    QTabWidgetWithControlPrivate *p;
};

#endif // QTABWIDGETWITHCONTROL_H
