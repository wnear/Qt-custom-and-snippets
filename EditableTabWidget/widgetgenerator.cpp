#include "widgetgenerator.h"

#include <QTextEdit>
#include <QLabel>

WidgetGenerator::WidgetGenerator()
{
    m_map.insert("ace", std::bind(&WidgetGenerator::makeAce, this));
    m_map.insert("beta", std::bind(&WidgetGenerator::makeBeta, this));
    m_map.insert("gamma", std::bind(&WidgetGenerator::makeBeta, this));
}

QWidget *WidgetGenerator::makeAce()
{
    auto *x = new QLabel;
    x->setText("ace panel");
    return x;
}

QWidget *WidgetGenerator::makeBeta()
{
    auto *x = new QTextEdit;
    x->setText("beta panel");
    return x;
}

QWidget *WidgetGenerator::makeGamma()
{
    auto *x = new QTextEdit;
    x->setText("Gamma paenl");
    return x;
}
