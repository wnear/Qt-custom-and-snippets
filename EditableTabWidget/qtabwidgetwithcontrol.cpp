#include "qtabwidgetwithcontrol.h"
#include <QTabBar>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
#include <QToolButton>
#include <QTextEdit>
#include <QMenu>
#include <QDebug>

class QTabWidgetWithControlPrivate
{
public:
    QTabBar *tabs;
    QStackedWidget *stack;
    QMenu *menu;
    QToolButton *menu_btn;
};


QTabWidgetWithControl::QTabWidgetWithControl(QWidget *parent) : QWidget(parent)
{
    p = new QTabWidgetWithControlPrivate;

    QWidget *main = this;
    QVBoxLayout *mainlay = new QVBoxLayout;
    main->setLayout(mainlay);

    auto *bar_lay = new QHBoxLayout;
    mainlay->addLayout(bar_lay);
    auto *tabbar = new QTabBar;
    p->tabs = tabbar;
    tabbar->setContentsMargins(0,0,0,0);
    auto *_btn_menu = new QToolButton;
    p->menu_btn = _btn_menu;
    _btn_menu->setIcon(QIcon::fromTheme("application-menu"));
    _btn_menu->setStyleSheet("QToolButton{border:none;}");


//    _btn_menu->setB
    auto *_btn_close = new QToolButton;
    _btn_close->setIcon(QIcon::fromTheme("view-close"));
    _btn_close->setStyleSheet("QToolButton{border:none;}");

    bar_lay->setContentsMargins(0,0,0,0);
    bar_lay->addWidget(tabbar);
    bar_lay->addStretch(1);
    bar_lay->addWidget(_btn_menu);
    bar_lay->addWidget(_btn_close);


    auto *stacked = new QStackedWidget;
    p->stack = stacked;
    mainlay->addWidget(stacked);

    stacked->setContentsMargins(0,0,0,0);
    mainlay->setSpacing(0);
    main->setContentsMargins(0,0,0,0);
    main->setLayout(mainlay);
    connect(p->tabs, &QTabBar::currentChanged, p->stack, &QStackedWidget::setCurrentIndex);
    connect(_btn_menu, &QToolButton::clicked, [this](){
        qDebug()<<"triggered btn_menu";
        p->menu_btn->showMenu();
    });
    connect(_btn_close, &QToolButton::clicked, [this](){
        QString target = p->tabs->tabText(p->tabs->currentIndex());
        for(auto *x: p->menu_btn->menu()->actions())
            if(x->text() == target)
                x->setChecked(false);
    });
}

QTabWidgetWithControl::~QTabWidgetWithControl()
{
    delete p;
}

int QTabWidgetWithControl::addTab(QWidget *page, const QString &label)
{
    auto _idx = p->tabs->addTab(label);
    p->stack->addWidget(page);

    this->setCurrentIndex(_idx);
    return _idx;
}

int QTabWidgetWithControl::insertTab(int index, QWidget *page, const QString &label)
{
    auto _idx= p->tabs->insertTab(index, label);
    p->stack->insertWidget(index, page);
    return _idx;
}

void QTabWidgetWithControl::removeTab(int index)
{
    p->tabs->removeTab(index);
    p->stack->removeWidget(p->stack->widget(index));
}

void QTabWidgetWithControl::removeTab(QString label)
{
    for(auto i = 0; i< p->tabs->count(); i++){
        if(p->tabs->tabText(i) == label){
            this->removeTab(i);
            return;
        }
    }
    return;
}

int QTabWidgetWithControl::currentIndex() const
{
    return p->tabs->currentIndex();
}

QWidget *QTabWidgetWithControl::widget(int index) const
{
    return p->stack->widget(index);
}

QWidget *QTabWidgetWithControl::makeTestWidget(QString content)
{
    auto *j = new QTextEdit;
    j->setReadOnly(true);
    j->setText(content);

    return j;
}

void QTabWidgetWithControl::setupMenuAndActions(WidgetGenerator::NameToGenerator_Type &generatorMap)
{
    auto *m = new QMenu;
    for(auto x: generatorMap.keys()){
        auto *ac = new QAction(x);
        ac->setCheckable(true);
        connect(ac, &QAction::toggled, [this, &generatorMap, x](bool status){
            if(status)
                this->addTab(generatorMap[x](), x);
            else
                this->removeTab(x);
        });
        m->addAction(ac);
    }

    p->menu_btn->setMenu(m);
    p->menu_btn->setPopupMode(QToolButton::InstantPopup);
    p->menu_btn->setArrowType(Qt::NoArrow);
}

QMenu *QTabWidgetWithControl::menu()
{
    return p->menu;
}

void QTabWidgetWithControl::setCurrentIndex(int index)
{
    p->tabs->setCurrentIndex(index);
    p->stack->setCurrentIndex(index);
}



