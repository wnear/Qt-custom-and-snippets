#ifndef WIDGETGENERATOR_H
#define WIDGETGENERATOR_H

#include <QWidget>
#include <functional>
#include <QMap>


class WidgetGenerator
{
public:
    WidgetGenerator();
    ~WidgetGenerator()=default;

    using generator_t=std::function<QWidget *()>;
    using NameToGenerator_Type = QMap<QString, generator_t>;

    QWidget *makeAce();
    QWidget *makeBeta();
    QWidget *makeGamma();

    QStringList wgtLabelsAvailable(){
        return m_map.keys();
    }

    NameToGenerator_Type m_map;
};

#endif // WIDGETGENERATOR_H
